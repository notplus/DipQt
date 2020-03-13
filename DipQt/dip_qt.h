#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_dip_qt.h"
#include "paint_widget.h"
#include "image_class.h"

class DipQt : public QMainWindow
{
    Q_OBJECT

public:
    DipQt(QWidget *parent = Q_NULLPTR);

private:
    Ui::DipQtClass ui;
    PaintWidget* paint_widget_;
    ImageClass image_class_;
    HistogramWidget* histogram_widget_;

private slots:
    void OpenImage();
    void Negative();
    void GaryHistogram();
    void FilpUp();
    void FilpLeft();
    void CenterMirror();
};
