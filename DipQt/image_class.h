#pragma once

#include <QImage>
#include <QPainter>
#include <QTransform>

class ImageClass
{
public:
    ImageClass();
    ~ImageClass();
    void ReadImage(QString filename);
    const QImage* GetImagePointer();
    void ImageToArray();
    void PutImgData();
    
    void Negative();
    void DrawGaryHistogram(QPainter* painter, int w, int h, int style = 0);
    void FilpUp();
    void FilpLeft();
    void CenterMirror();
    void CalculateHistogram();

private:
    uchar* image_array_;
    QImage image_;

    long width_, height_;
    long pixels_, size_;
    long f_width_;
    long c_width_,c_size_;
    long* cpos_;

    long m_hist_[256];
    long r_hist_[256];
    long g_hist_[256];
    long b_hist_[256];
    double entropy_, average_, sigma_;
    uchar max_grey_, min_grey_;

    QTransform mat_hist_;
};
