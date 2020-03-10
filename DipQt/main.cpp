#include "DipQt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DipQt w;
    w.show();
    return a.exec();
}
