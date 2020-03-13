#include "paint_widget.h"
#include "qpainter.h"

PaintWidget::PaintWidget(QWidget* parent) :
    QWidget(parent)
{
    m_image_ = NULL;
}

void PaintWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    if (!m_image_==NULL)
    {
        painter.translate(offset_x_, offset_y_);
        painter.scale(m_scale_, m_scale_);
        painter.drawImage(0, 0, *m_image_);

    }
}

void PaintWidget::SetImage(const QImage* image)
{
    m_image_ = image;
    m_scale_ = 1;

    int window_width, window_height;
    int image_width, image_height;
    
    window_width = width();
    window_height = height();
    image_width = m_image_->width();
    image_height = m_image_->height();
    offset_x_ = (window_width - m_scale_ * image_width) / 2;
    offset_y_ = (window_height - m_scale_ * image_height) / 2;

    update();
}

void PaintWidget::wheelEvent(QWheelEvent* event)
{
    mouse_pos_.setX(event->x());
    mouse_pos_.setY(event->y());
    ChangeScale(event->delta());
}

void PaintWidget::ChangeScale(int delta)
{
    double pre_x = (mouse_pos_.x() - offset_x_) / m_scale_;
    double pre_y = (mouse_pos_.y() - offset_y_) / m_scale_;
    m_scale_ += m_scale_ * delta * 1.0 / 300;
    offset_x_ = mouse_pos_.x() - pre_x * m_scale_;
    offset_y_ = mouse_pos_.y() - pre_y * m_scale_;
    update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        offset_x_ += event->x() - mouse_pos_.x();
        offset_y_ += event->y() - mouse_pos_.y();
        mouse_pos_.setX(event->x());
        mouse_pos_.setY(event->y());
        update();
    }
}

void PaintWidget::mousePressEvent(QMouseEvent* event)
{
    mouse_pos_.setX(event->x());
    mouse_pos_.setY(event->y());
}

HistogramWidget::HistogramWidget(QWidget* parent)
{
    style_ = 0;
}

void HistogramWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    img_class_->DrawGaryHistogram(&painter, width(), height(),style_);
}

void HistogramWidget::SetImgClass(ImageClass* img_class)
{
    img_class_ = img_class;
    update();
}

void HistogramWidget::mousePressEvent(QMouseEvent* event)
{
    style_ = !style_;
    update();
}