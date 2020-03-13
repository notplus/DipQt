#include "dip_qt.h"
#include "qfiledialog.h"
#include "qmessagebox.h"

DipQt::DipQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    paint_widget_ = new PaintWidget();
    this->setCentralWidget(paint_widget_);

    histogram_widget_ = new HistogramWidget();

    connect(ui.action_open, &QAction::triggered, this, &DipQt::OpenImage);
    connect(ui.action_negative, &QAction::triggered, this, &DipQt::Negative);
    connect(ui.action_gray_histogram, &QAction::triggered, this, &DipQt::GaryHistogram);
    connect(ui.action_flip_up, &QAction::triggered, this, &DipQt::FilpUp);
    connect(ui.action_flip_left, &QAction::triggered, this, &DipQt::FilpLeft);
    connect(ui.action_center_mirror, &QAction::triggered, this, &DipQt::CenterMirror);
}

void DipQt::OpenImage()
{
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open Image"), ".", tr("Image File (*.jpg *.png *.bmp)"));
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(filename));
            return;
        }
    }
    image_class_.ReadImage(filename);
    paint_widget_->SetImage(image_class_.GetImagePointer());
}

void DipQt::Negative()
{
    image_class_.Negative();
    paint_widget_->SetImage(image_class_.GetImagePointer());
}

void DipQt::GaryHistogram()
{
    image_class_.CalculateHistogram();

    paint_widget_->SetImage(image_class_.GetImagePointer());
    histogram_widget_->SetImgClass(&image_class_);
    histogram_widget_->show();
}

void DipQt::FilpUp()
{
    image_class_.FilpUp();
    paint_widget_->SetImage(image_class_.GetImagePointer());
}

void DipQt::FilpLeft()
{
    image_class_.FilpLeft();
    paint_widget_->SetImage(image_class_.GetImagePointer());
}

void DipQt::CenterMirror()
{
    image_class_.CenterMirror();
    paint_widget_->SetImage(image_class_.GetImagePointer());
}
