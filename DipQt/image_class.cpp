#include "image_class.h"
#include <QTransform>
#include <cmath>

ImageClass::ImageClass()
{
    image_array_ = NULL;
}

ImageClass::~ImageClass()
{

}


void ImageClass::ReadImage(QString filename)
{
    image_.load(filename);
    if (image_.format()==QImage::Format_RGB32)
        image_ = image_.convertToFormat(QImage::Format_RGB888);
    ImageToArray();
}

const QImage* ImageClass::GetImagePointer()
{
    return &image_;
}

void ImageClass::ImageToArray()
{
    width_ = image_.width();
    height_ = image_.height();

    if (image_array_ != NULL)
        free(image_array_);

    if (image_.format() == QImage::Format_Indexed8)
    {
        f_width_ = ((width_ + 3) / 4) * 4;
        size_ = f_width_ * height_;
        pixels_ = width_ * height_;
        image_array_ = (uchar*)malloc(size_);
        memcpy(image_array_, image_.bits(), size_);
    }
    else if (image_.format() == QImage::Format_RGB888)
    {
        c_width_ = ((width_ * 3 + 3) / 4) * 4;
        c_size_ = c_width_ * height_;
        pixels_ = width_ * height_;
        image_array_ = (uchar*)malloc(c_size_);
        memcpy(image_array_, image_.bits(), c_size_);
        auto aaa = image_.bits();
        cpos_ = (long*)malloc(height_*sizeof(long));
        for (int i = 0; i < height_; i++)
        {
            cpos_[i] = i * c_width_;
        }
    }

}

void ImageClass::PutImgData()
{
    if (image_.format()==QImage::Format_Indexed8)
        memcpy(image_.bits(), image_array_, size_);
    else if (image_.format()==QImage::Format_RGB888)
        memcpy(image_.bits(), image_array_, c_size_);
}

void ImageClass::Negative()
{
    long pos;
    if (image_.format() == QImage::Format_Indexed8)
    {
        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
            {
                pos = i * f_width_ + j;
                image_array_[pos] = 255 - image_array_[pos];
            }
        }
    }
    else if (image_.format() == QImage::Format_RGB888)
    {
        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
            {
                pos = cpos_[i] + j * 3;
                image_array_[pos] = 255 - image_array_[pos];
                image_array_[pos + 1] = 255 - image_array_[pos + 1];
                image_array_[pos + 2] = 255 - image_array_[pos + 2];
            }
        }
    }
    
    PutImgData(); 
}

void ImageClass::CalculateHistogram()
{
    long pos;
    if (image_.format() == QImage::Format_Indexed8)
    {
        for (int i = 0; i < 256; i++)
            m_hist_[i] = 0;
        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
            {
                pos = i * f_width_ + j;
                m_hist_[image_array_[pos]]++;
            }
        }

        //calculate avg grey
        average_ = 0.0;
        for (int i = 0; i < 256; i++)
        {
            average_ += m_hist_[i] * i;
        }
        average_ /= pixels_;

        //calculate sigma
        sigma_ = 0.0;
        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
            {
                pos = i * f_width_ + j;
                sigma_ += (average_ - image_array_[pos]) * (average_ - image_array_[pos]);
            }
        }
        sigma_ = sqrt(sigma_ / pixels_);

        //max grey
        for (int i = 255; i > -1; i++)
        {
            if (m_hist_[i] != 0)
            {
                max_grey_ = i;
                break;
            }
        }

        //min grey
        for (int i = 0; i < 256; i++)
        {
            if (m_hist_[i] != 0)
            {
                min_grey_ = i;
                break;
            }
        }

        //entropy
        entropy_ = 0.0;
        for (int i = 0; i < 256; i++)
        {
            if (m_hist_[i] != 0)
            {
                double p = m_hist_[i] * 1.0 / pixels_;
                entropy_ += p * log2(p);
            }
        }
        entropy_ = -entropy_;
    }
    else if (image_.format() == QImage::Format_RGB888)
    {
        for (int i = 0; i < 256; i++)
        {
            m_hist_[i] = 0;
            r_hist_[i] = 0;
            g_hist_[i] = 0;
            b_hist_[i] = 0;
        }
        
        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
            {
                pos = cpos_[i] + j * 3;
                uchar grey = image_array_[pos] * 0.114 + image_array_[pos + 1] * 0.587 + image_array_[pos + 2] * 0.299;
                m_hist_[grey] += 1;
                r_hist_[pos] += 1;
                g_hist_[pos + 1] += 1;
                b_hist_[pos + 2] += 1;
            }
        }
    }

}

void ImageClass::DrawGaryHistogram(QPainter* painter, int w, int h,int style)
{
    float sx, sy;
    float x1, y1, x2, y2, x0, y0;
    QPen pen(Qt::red);
    painter->setPen(pen);
    //w = 587, h = 247;

    if (image_.format() == QImage::Format_Indexed8)
    {
        long max_h = m_hist_[0];
        for (int i = 1; i < 256; i++)
        {
            if (max_h < m_hist_[i])
                max_h = m_hist_[i];
        }
        sx = w / 270.0;  // 设定宽度为270
        sy = h / (max_h * 1.2); // 高度放大20%
        painter->scale(sx,-sy); // 设置比例系数，纵向为负表示把竖轴的原点移到下面
        x0 = 5.0;
        y0 = -max_h * 1.1;   // 图形原点（0,0）上移10%
        painter->translate(x0, y0);
        mat_hist_ = painter->transform().inverted();  // 保留一个坐标逆变换的矩阵

        // 首先绘制坐标轴，纵横线
        x1 = -3;  // 横轴线起点于-3
        y1 = 0;   // 横轴线
        x2 = 260; // 横轴线终止于260 
        y2 = y1; // 横轴线为水平线
        painter->drawLine(x1, y1, x2, y2); // 绘制（x1, y1） - （x2, y2）
        x1 = 0; // 竖轴线
        y1 = max_h * 1.05;   // 竖轴线起始于下部5%至顶部5%（注意横轴线在离底部5%处）
        x2 = x1;
        y2 = -max_h * 0.025;
        painter->drawLine(x1, y1, x2, y2);
        x1 = 255; // 在横线255处画一条小短竖线
        y1 = max_h * 0.025;
        x2 = x1;
        y2 = -y1;
        painter->drawLine(x1, y1, x2, y2);
        for (float x1 = 50; x1 <= 200; x1+=50)
        {
            y1 = 0;
            x2 = x1;
            y2 = -max_h * 0.025;
            painter->drawLine(x1, y1, x2, y2);
        }
        painter->resetTransform(); // 为了输出文字标记，取消坐标变换

        QString txt; //Set format of string.
        for (float x1 = 0; x1 <= 200; x1+=50)
        {
            x2 = (x1 + x0) * sx;
            y2 = -(-max_h * 0.025 + y0) * sy;
            txt = QString::number(x1);
            painter->drawText(x2, y2, txt);
        }

        x1 = 255;
        x2 = (x1 + x0) * sx;
        y2 = -(-max_h * 0.025 + y0) * sy;
        txt = QString::number(x1);
        painter->drawText(x2,y2, txt);
        painter->scale(sx, -sy); // 设置比例系数，纵向为负表示把竖轴的原点移到下面
        painter->translate(x0, y0); // 设置坐标偏移

        pen = QPen(Qt::black,1);
        painter->setPen(pen);
        if (style == 0) //折线
        {
            x1 = 0;
            y1 = m_hist_[0];
            for (int i = 0; i < 255; i++)
            {
                x2 = i + 1;
                y2 = m_hist_[i + 1];
                painter->drawLine(x1, y1, x2, y2);
                x1 = x2;
                y1 = y2;
            }
        }
        else
        {
            QBrush brush(Qt::blue);
            painter->setBrush(brush);
            for (int i = 0; i < 256; i++)
            {
                x1 = i - 0.5;
                y1 = 0;
                x2 = i + 0.5;
                y2 = m_hist_[i];
                painter->fillRect(x1, y1, x2 - x1, y2 - y1, brush);
            }
        }
    }
}

void ImageClass::FilpUp()
{

}

void ImageClass::FilpLeft()
{

}

void ImageClass::CenterMirror()
{

}