#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QImage>
#include "image_class.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*);
    void SetImage(const QImage* image);
    void wheelEvent(QWheelEvent* event);
    void ChangeScale(int delta);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    const QImage* m_image_;
    double m_scale_;
    QPoint mouse_pos_;
    int offset_x_, offset_y_;
};

class HistogramWidget : public QWidget
{
    Q_OBJECT
public:
    HistogramWidget(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*);
    void SetImgClass(ImageClass* img_class);
    void mousePressEvent(QMouseEvent* event);

private:
    ImageClass* img_class_;
    int style_;
};