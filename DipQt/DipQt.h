#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DipQt.h"

class DipQt : public QMainWindow
{
    Q_OBJECT

public:
    DipQt(QWidget *parent = Q_NULLPTR);

private:
    Ui::DipQtClass ui;
};
