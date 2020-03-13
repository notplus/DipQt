/********************************************************************************
** Form generated from reading UI file 'DipQtJTsbhj.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DIPQTJTSBHJ_H
#define DIPQTJTSBHJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DipQtClass
{
public:
    QAction *action_open;
    QAction *action_negative;
    QAction *action_flip_up;
    QAction *action_center_mirror;
    QAction *action_flip_left;
    QAction *action_gray_histogram;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu_file;
    QMenu *menu_edit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DipQtClass)
    {
        if (DipQtClass->objectName().isEmpty())
            DipQtClass->setObjectName(QString::fromUtf8("DipQtClass"));
        DipQtClass->resize(966, 641);
        action_open = new QAction(DipQtClass);
        action_open->setObjectName(QString::fromUtf8("action_open"));
        action_negative = new QAction(DipQtClass);
        action_negative->setObjectName(QString::fromUtf8("action_negative"));
        action_flip_up = new QAction(DipQtClass);
        action_flip_up->setObjectName(QString::fromUtf8("action_flip_up"));
        action_center_mirror = new QAction(DipQtClass);
        action_center_mirror->setObjectName(QString::fromUtf8("action_center_mirror"));
        action_flip_left = new QAction(DipQtClass);
        action_flip_left->setObjectName(QString::fromUtf8("action_flip_left"));
        action_gray_histogram = new QAction(DipQtClass);
        action_gray_histogram->setObjectName(QString::fromUtf8("action_gray_histogram"));
        centralWidget = new QWidget(DipQtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        DipQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DipQtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 966, 23));
        menu_file = new QMenu(menuBar);
        menu_file->setObjectName(QString::fromUtf8("menu_file"));
        menu_edit = new QMenu(menuBar);
        menu_edit->setObjectName(QString::fromUtf8("menu_edit"));
        DipQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DipQtClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        DipQtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DipQtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        DipQtClass->setStatusBar(statusBar);

        menuBar->addAction(menu_file->menuAction());
        menuBar->addAction(menu_edit->menuAction());
        menu_file->addAction(action_open);
        menu_edit->addAction(action_negative);
        menu_edit->addAction(action_flip_up);
        menu_edit->addAction(action_center_mirror);
        menu_edit->addAction(action_flip_left);
        menu_edit->addAction(action_gray_histogram);

        retranslateUi(DipQtClass);

        QMetaObject::connectSlotsByName(DipQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *DipQtClass)
    {
        DipQtClass->setWindowTitle(QApplication::translate("DipQtClass", "DipQt", nullptr));
        action_open->setText(QApplication::translate("DipQtClass", "\346\211\223\345\274\200", nullptr));
        action_negative->setText(QApplication::translate("DipQtClass", "\350\264\237\347\211\207", nullptr));
        action_flip_up->setText(QApplication::translate("DipQtClass", "\344\270\212\344\270\213\347\277\273\350\275\254", nullptr));
        action_center_mirror->setText(QApplication::translate("DipQtClass", "\344\270\255\345\277\203\351\225\234\345\203\217", nullptr));
        action_flip_left->setText(QApplication::translate("DipQtClass", "\345\267\246\345\217\263\347\277\273\350\275\254", nullptr));
        action_gray_histogram->setText(QApplication::translate("DipQtClass", "\347\201\260\345\272\246\347\233\264\346\226\271\345\233\276", nullptr));
        menu_file->setTitle(QApplication::translate("DipQtClass", "\346\226\207\344\273\266", nullptr));
        menu_edit->setTitle(QApplication::translate("DipQtClass", "\347\274\226\350\276\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DipQtClass: public Ui_DipQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DIPQTJTSBHJ_H
