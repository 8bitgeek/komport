/********************************************************************************
** Form generated from reading UI file 'komport.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KOMPORT_H
#define UI_KOMPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Komport
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Komport)
    {
        if (Komport->objectName().isEmpty())
            Komport->setObjectName(QString::fromUtf8("Komport"));
        Komport->resize(574, 338);
        centralWidget = new QWidget(Komport);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Komport->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Komport);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 574, 19));
        Komport->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Komport);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Komport->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Komport);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Komport->setStatusBar(statusBar);

        retranslateUi(Komport);

        QMetaObject::connectSlotsByName(Komport);
    } // setupUi

    void retranslateUi(QMainWindow *Komport)
    {
        Komport->setWindowTitle(QCoreApplication::translate("Komport", "Komport", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Komport: public Ui_Komport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KOMPORT_H
