/********************************************************************************
** Form generated from reading UI file 'QtWidgetsTest.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSTEST_H
#define UI_QTWIDGETSTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsTestClass)
    {
        if (QtWidgetsTestClass->objectName().isEmpty())
            QtWidgetsTestClass->setObjectName(QString::fromUtf8("QtWidgetsTestClass"));
        QtWidgetsTestClass->resize(600, 400);
        menuBar = new QMenuBar(QtWidgetsTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QtWidgetsTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtWidgetsTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtWidgetsTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtWidgetsTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtWidgetsTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtWidgetsTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtWidgetsTestClass->setStatusBar(statusBar);

        retranslateUi(QtWidgetsTestClass);

        QMetaObject::connectSlotsByName(QtWidgetsTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsTestClass)
    {
        QtWidgetsTestClass->setWindowTitle(QCoreApplication::translate("QtWidgetsTestClass", "QtWidgetsTest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsTestClass: public Ui_QtWidgetsTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSTEST_H
