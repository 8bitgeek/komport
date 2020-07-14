/*
Serial port settings form
*/

/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *hboxLayout;
    QPushButton *buttonHelp;
    QSpacerItem *Horizontal_Spacing2;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;
    QTabWidget *tabWidget;
    QWidget *TerminalTab;
    QGridLayout *gridLayout1;
    QLabel *label_3;
    QSpinBox *ColumnsSpinBox;
    QSpinBox *RowsSpinBox;
    QLabel *label;
    QSpacerItem *spacer3;
    QLabel *label_2;
    QSpacerItem *spacer2;
    QPushButton *ForegroundColorButton;
    QLabel *label_4;
    QPushButton *BackgroundColorButton;
    QGroupBox *groupBox3;
    QGridLayout *gridLayout2;
    QComboBox *EmulationComboBox;
    QCheckBox *LocalEchoCheckBox;
    QCheckBox *VisualBellCheckBox;
    QWidget *DeviceTab;
    QGridLayout *gridLayout3;
    QGridLayout *gridLayout4;
    QSpacerItem *spacer4;
    QComboBox *BaudRateComboBox;
    QGroupBox *groupBox4;
    QGridLayout *gridLayout5;
    QGridLayout *gridLayout6;
    QLabel *textLabel4_2;
    QComboBox *ParityComboBox;
    QLabel *textLabel2_3;
    QComboBox *DataBitsComboBox;
    QLabel *textLabel3;
    QComboBox *StopBitsComboBox;
    QSpacerItem *spacer5;
    QSpacerItem *spacer6;
    QLabel *textLabel1;
    QLabel *BaudRateLabel;
    QLabel *textLabel4;
    QComboBox *DeviceComboBox;
    QSpacerItem *spacer7;
    QComboBox *FlowControlComboBox;
    QWidget *LogTab;
    QGridLayout *gridLayout_6;
    QTextBrowser *log;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(496, 314);
        SettingsDialog->setSizeGripEnabled(true);
        gridLayout = new QGridLayout(SettingsDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(11, 11, 11, 11);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        buttonHelp = new QPushButton(SettingsDialog);
        buttonHelp->setObjectName(QString::fromUtf8("buttonHelp"));
        buttonHelp->setAutoDefault(true);

        hboxLayout->addWidget(buttonHelp);

        Horizontal_Spacing2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(Horizontal_Spacing2);

        buttonOk = new QPushButton(SettingsDialog);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);

        hboxLayout->addWidget(buttonOk);

        buttonCancel = new QPushButton(SettingsDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout->addWidget(buttonCancel);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 2);

        tabWidget = new QTabWidget(SettingsDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        TerminalTab = new QWidget();
        TerminalTab->setObjectName(QString::fromUtf8("TerminalTab"));
        gridLayout1 = new QGridLayout(TerminalTab);
        gridLayout1->setSpacing(6);
        gridLayout1->setContentsMargins(11, 11, 11, 11);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        label_3 = new QLabel(TerminalTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout1->addWidget(label_3, 1, 1, 1, 2);

        ColumnsSpinBox = new QSpinBox(TerminalTab);
        ColumnsSpinBox->setObjectName(QString::fromUtf8("ColumnsSpinBox"));
        ColumnsSpinBox->setMinimum(16);
        ColumnsSpinBox->setMaximum(132);
        ColumnsSpinBox->setValue(80);

        gridLayout1->addWidget(ColumnsSpinBox, 0, 2, 1, 2);

        RowsSpinBox = new QSpinBox(TerminalTab);
        RowsSpinBox->setObjectName(QString::fromUtf8("RowsSpinBox"));
        RowsSpinBox->setMinimum(2);
        RowsSpinBox->setMaximum(64);
        RowsSpinBox->setValue(25);

        gridLayout1->addWidget(RowsSpinBox, 0, 5, 1, 1);

        label = new QLabel(TerminalTab);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout1->addWidget(label, 0, 1, 1, 1);

        spacer3 = new QSpacerItem(20, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacer3, 3, 3, 1, 1);

        label_2 = new QLabel(TerminalTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout1->addWidget(label_2, 0, 4, 1, 1);

        spacer2 = new QSpacerItem(203, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(spacer2, 2, 2, 1, 4);

        ForegroundColorButton = new QPushButton(TerminalTab);
        ForegroundColorButton->setObjectName(QString::fromUtf8("ForegroundColorButton"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 255, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 255, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(63, 255, 63, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 127, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 170, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        ForegroundColorButton->setPalette(palette);

        gridLayout1->addWidget(ForegroundColorButton, 1, 5, 1, 1);

        label_4 = new QLabel(TerminalTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout1->addWidget(label_4, 1, 4, 1, 1);

        BackgroundColorButton = new QPushButton(TerminalTab);
        BackgroundColorButton->setObjectName(QString::fromUtf8("BackgroundColorButton"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        BackgroundColorButton->setPalette(palette1);

        gridLayout1->addWidget(BackgroundColorButton, 1, 3, 1, 1);

        groupBox3 = new QGroupBox(TerminalTab);
        groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
        gridLayout2 = new QGridLayout(groupBox3);
        gridLayout2->setSpacing(6);
        gridLayout2->setContentsMargins(11, 11, 11, 11);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        EmulationComboBox = new QComboBox(groupBox3);
        EmulationComboBox->addItem(QString());
        EmulationComboBox->addItem(QString());
        EmulationComboBox->setObjectName(QString::fromUtf8("EmulationComboBox"));

        gridLayout2->addWidget(EmulationComboBox, 0, 0, 1, 1);

        LocalEchoCheckBox = new QCheckBox(groupBox3);
        LocalEchoCheckBox->setObjectName(QString::fromUtf8("LocalEchoCheckBox"));
        LocalEchoCheckBox->setEnabled(true);

        gridLayout2->addWidget(LocalEchoCheckBox, 2, 0, 1, 1);

        VisualBellCheckBox = new QCheckBox(groupBox3);
        VisualBellCheckBox->setObjectName(QString::fromUtf8("VisualBellCheckBox"));
        VisualBellCheckBox->setEnabled(true);
        VisualBellCheckBox->setChecked(true);

        gridLayout2->addWidget(VisualBellCheckBox, 1, 0, 1, 1);


        gridLayout1->addWidget(groupBox3, 0, 0, 3, 1);

        tabWidget->addTab(TerminalTab, QString());
        DeviceTab = new QWidget();
        DeviceTab->setObjectName(QString::fromUtf8("DeviceTab"));
        gridLayout3 = new QGridLayout(DeviceTab);
        gridLayout3->setSpacing(6);
        gridLayout3->setContentsMargins(11, 11, 11, 11);
        gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
        gridLayout4 = new QGridLayout();
        gridLayout4->setSpacing(6);
        gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
        spacer4 = new QSpacerItem(281, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacer4, 1, 3, 1, 2);

        BaudRateComboBox = new QComboBox(DeviceTab);
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->addItem(QString());
        BaudRateComboBox->setObjectName(QString::fromUtf8("BaudRateComboBox"));

        gridLayout4->addWidget(BaudRateComboBox, 1, 1, 1, 2);

        groupBox4 = new QGroupBox(DeviceTab);
        groupBox4->setObjectName(QString::fromUtf8("groupBox4"));
        gridLayout5 = new QGridLayout(groupBox4);
        gridLayout5->setSpacing(6);
        gridLayout5->setContentsMargins(11, 11, 11, 11);
        gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
        gridLayout6 = new QGridLayout();
        gridLayout6->setSpacing(6);
        gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
        textLabel4_2 = new QLabel(groupBox4);
        textLabel4_2->setObjectName(QString::fromUtf8("textLabel4_2"));
        textLabel4_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel4_2->setWordWrap(false);

        gridLayout6->addWidget(textLabel4_2, 2, 0, 1, 1);

        ParityComboBox = new QComboBox(groupBox4);
        ParityComboBox->addItem(QString());
        ParityComboBox->addItem(QString());
        ParityComboBox->addItem(QString());
        ParityComboBox->setObjectName(QString::fromUtf8("ParityComboBox"));

        gridLayout6->addWidget(ParityComboBox, 2, 1, 1, 2);

        textLabel2_3 = new QLabel(groupBox4);
        textLabel2_3->setObjectName(QString::fromUtf8("textLabel2_3"));
        textLabel2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_3->setWordWrap(false);

        gridLayout6->addWidget(textLabel2_3, 0, 0, 1, 2);

        DataBitsComboBox = new QComboBox(groupBox4);
        DataBitsComboBox->addItem(QString());
        DataBitsComboBox->addItem(QString());
        DataBitsComboBox->addItem(QString());
        DataBitsComboBox->addItem(QString());
        DataBitsComboBox->setObjectName(QString::fromUtf8("DataBitsComboBox"));

        gridLayout6->addWidget(DataBitsComboBox, 0, 2, 1, 1);

        textLabel3 = new QLabel(groupBox4);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel3->setWordWrap(false);

        gridLayout6->addWidget(textLabel3, 1, 0, 1, 2);

        StopBitsComboBox = new QComboBox(groupBox4);
        StopBitsComboBox->addItem(QString());
        StopBitsComboBox->addItem(QString());
        StopBitsComboBox->addItem(QString());
        StopBitsComboBox->setObjectName(QString::fromUtf8("StopBitsComboBox"));

        gridLayout6->addWidget(StopBitsComboBox, 1, 2, 1, 1);


        gridLayout5->addLayout(gridLayout6, 0, 0, 1, 1);


        gridLayout4->addWidget(groupBox4, 2, 2, 2, 1);

        spacer5 = new QSpacerItem(101, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout4->addItem(spacer5, 2, 0, 1, 2);

        spacer6 = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout4->addItem(spacer6, 3, 4, 2, 1);

        textLabel1 = new QLabel(DeviceTab);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1->setWordWrap(false);

        gridLayout4->addWidget(textLabel1, 0, 0, 1, 1);

        BaudRateLabel = new QLabel(DeviceTab);
        BaudRateLabel->setObjectName(QString::fromUtf8("BaudRateLabel"));
        BaudRateLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        BaudRateLabel->setWordWrap(false);

        gridLayout4->addWidget(BaudRateLabel, 1, 0, 1, 1);

        textLabel4 = new QLabel(DeviceTab);
        textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
        textLabel4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel4->setWordWrap(false);

        gridLayout4->addWidget(textLabel4, 0, 3, 1, 1);

        DeviceComboBox = new QComboBox(DeviceTab);
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->setObjectName(QString::fromUtf8("DeviceComboBox"));
        DeviceComboBox->setEditable(true);

        gridLayout4->addWidget(DeviceComboBox, 0, 1, 1, 2);

        spacer7 = new QSpacerItem(20, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout4->addItem(spacer7, 4, 2, 1, 1);

        FlowControlComboBox = new QComboBox(DeviceTab);
        FlowControlComboBox->addItem(QString());
        FlowControlComboBox->addItem(QString());
        FlowControlComboBox->addItem(QString());
        FlowControlComboBox->setObjectName(QString::fromUtf8("FlowControlComboBox"));

        gridLayout4->addWidget(FlowControlComboBox, 0, 4, 1, 1);


        gridLayout3->addLayout(gridLayout4, 0, 0, 1, 1);

        tabWidget->addTab(DeviceTab, QString());
        LogTab = new QWidget();
        LogTab->setObjectName(QString::fromUtf8("LogTab"));
        gridLayout_6 = new QGridLayout(LogTab);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        log = new QTextBrowser(LogTab);
        log->setObjectName(QString::fromUtf8("log"));
        log->setLineWrapMode(QTextEdit::NoWrap);

        gridLayout_6->addWidget(log, 0, 0, 1, 1);

        tabWidget->addTab(LogTab, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        QWidget::setTabOrder(tabWidget, EmulationComboBox);
        QWidget::setTabOrder(EmulationComboBox, VisualBellCheckBox);
        QWidget::setTabOrder(VisualBellCheckBox, LocalEchoCheckBox);
        QWidget::setTabOrder(LocalEchoCheckBox, ColumnsSpinBox);
        QWidget::setTabOrder(ColumnsSpinBox, RowsSpinBox);
        QWidget::setTabOrder(RowsSpinBox, BackgroundColorButton);
        QWidget::setTabOrder(BackgroundColorButton, ForegroundColorButton);
        QWidget::setTabOrder(ForegroundColorButton, DeviceComboBox);
        QWidget::setTabOrder(DeviceComboBox, BaudRateComboBox);
        QWidget::setTabOrder(BaudRateComboBox, DataBitsComboBox);
        QWidget::setTabOrder(DataBitsComboBox, StopBitsComboBox);
        QWidget::setTabOrder(StopBitsComboBox, ParityComboBox);
        QWidget::setTabOrder(ParityComboBox, FlowControlComboBox);
        QWidget::setTabOrder(FlowControlComboBox, buttonHelp);
        QWidget::setTabOrder(buttonHelp, buttonOk);
        QWidget::setTabOrder(buttonOk, buttonCancel);

        retranslateUi(SettingsDialog);
        QObject::connect(buttonOk, SIGNAL(clicked()), SettingsDialog, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), SettingsDialog, SLOT(reject()));

        buttonOk->setDefault(true);
        tabWidget->setCurrentIndex(0);
        BaudRateComboBox->setCurrentIndex(11);
        DataBitsComboBox->setCurrentIndex(3);
        FlowControlComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Settings", nullptr));
        buttonHelp->setText(QCoreApplication::translate("SettingsDialog", "&Help", nullptr));
#if QT_CONFIG(shortcut)
        buttonHelp->setShortcut(QCoreApplication::translate("SettingsDialog", "F1", nullptr));
#endif // QT_CONFIG(shortcut)
        buttonOk->setText(QCoreApplication::translate("SettingsDialog", "&OK", nullptr));
#if QT_CONFIG(shortcut)
        buttonOk->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        buttonCancel->setText(QCoreApplication::translate("SettingsDialog", "&Cancel", nullptr));
#if QT_CONFIG(shortcut)
        buttonCancel->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        label_3->setText(QCoreApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Background:</p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        ColumnsSpinBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Specify the number of character columns.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        ColumnsSpinBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Specify the number of character columns.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        RowsSpinBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Specify the number of character rows.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        RowsSpinBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Specify the number of character rows.", nullptr));
#endif // QT_CONFIG(statustip)
        label->setText(QCoreApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Cols:</p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Rows:</p></body></html>", nullptr));
        ForegroundColorButton->setText(QString());
        label_4->setText(QCoreApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Foreground:</p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        BackgroundColorButton->setToolTip(QCoreApplication::translate("SettingsDialog", "Change the character background color.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        BackgroundColorButton->setStatusTip(QCoreApplication::translate("SettingsDialog", "Change the character background color.", nullptr));
#endif // QT_CONFIG(statustip)
        BackgroundColorButton->setText(QString());
        groupBox3->setTitle(QCoreApplication::translate("SettingsDialog", "Emulation", nullptr));
        EmulationComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "ANSI", nullptr));
        EmulationComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "VT102", nullptr));

#if QT_CONFIG(tooltip)
        EmulationComboBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Selects the terminal emulation.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        EmulationComboBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Selects the terminal emulation.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(tooltip)
        LocalEchoCheckBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Echo characters typed to the screen.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        LocalEchoCheckBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Echo characters typed to the screen.", nullptr));
#endif // QT_CONFIG(statustip)
        LocalEchoCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Local Echo", nullptr));
#if QT_CONFIG(tooltip)
        VisualBellCheckBox->setToolTip(QCoreApplication::translate("SettingsDialog", "The visual bell will flash the emulation window instead of ringing the terminal bell.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        VisualBellCheckBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "The visual bell will flash the emulation window instead of ringing the terminal bell.", nullptr));
#endif // QT_CONFIG(statustip)
        VisualBellCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Visual Bell", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TerminalTab), QCoreApplication::translate("SettingsDialog", "Terminal", nullptr));
        BaudRateComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "50", nullptr));
        BaudRateComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "75", nullptr));
        BaudRateComboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "110", nullptr));
        BaudRateComboBox->setItemText(3, QCoreApplication::translate("SettingsDialog", "134", nullptr));
        BaudRateComboBox->setItemText(4, QCoreApplication::translate("SettingsDialog", "150", nullptr));
        BaudRateComboBox->setItemText(5, QCoreApplication::translate("SettingsDialog", "300", nullptr));
        BaudRateComboBox->setItemText(6, QCoreApplication::translate("SettingsDialog", "600", nullptr));
        BaudRateComboBox->setItemText(7, QCoreApplication::translate("SettingsDialog", "1200", nullptr));
        BaudRateComboBox->setItemText(8, QCoreApplication::translate("SettingsDialog", "1800", nullptr));
        BaudRateComboBox->setItemText(9, QCoreApplication::translate("SettingsDialog", "2400", nullptr));
        BaudRateComboBox->setItemText(10, QCoreApplication::translate("SettingsDialog", "4800", nullptr));
        BaudRateComboBox->setItemText(11, QCoreApplication::translate("SettingsDialog", "9600", nullptr));
        BaudRateComboBox->setItemText(12, QCoreApplication::translate("SettingsDialog", "19200", nullptr));
        BaudRateComboBox->setItemText(13, QCoreApplication::translate("SettingsDialog", "38400", nullptr));
        BaudRateComboBox->setItemText(14, QCoreApplication::translate("SettingsDialog", "57600", nullptr));
        BaudRateComboBox->setItemText(15, QCoreApplication::translate("SettingsDialog", "115200", nullptr));
        BaudRateComboBox->setItemText(16, QCoreApplication::translate("SettingsDialog", "230400", nullptr));

#if QT_CONFIG(tooltip)
        BaudRateComboBox->setToolTip(QCoreApplication::translate("SettingsDialog", "SPecify the baud raet (bps).", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        BaudRateComboBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "SPecify the baud raet (bps).", nullptr));
#endif // QT_CONFIG(statustip)
        groupBox4->setTitle(QCoreApplication::translate("SettingsDialog", "Framing", nullptr));
        textLabel4_2->setText(QCoreApplication::translate("SettingsDialog", "Parity:", nullptr));
        ParityComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "NONE", nullptr));
        ParityComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "EVEN", nullptr));
        ParityComboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "ODD", nullptr));

#if QT_CONFIG(tooltip)
        ParityComboBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Specify the character framing parity.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        ParityComboBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Specify the character framing parity.", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel2_3->setText(QCoreApplication::translate("SettingsDialog", "Data bits:", nullptr));
        DataBitsComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "5", nullptr));
        DataBitsComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "6", nullptr));
        DataBitsComboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "7", nullptr));
        DataBitsComboBox->setItemText(3, QCoreApplication::translate("SettingsDialog", "8", nullptr));

#if QT_CONFIG(tooltip)
        DataBitsComboBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Specify the number of data bits in a character frame.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        DataBitsComboBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Specify the number of data bits in a character frame.", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel3->setText(QCoreApplication::translate("SettingsDialog", "Stop bits:", nullptr));
        StopBitsComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "1", nullptr));
        StopBitsComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "1.5", nullptr));
        StopBitsComboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "2", nullptr));

#if QT_CONFIG(tooltip)
        StopBitsComboBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Specify the number of stop bits in a frame.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        StopBitsComboBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Specify the number of stop bits in a frame.", nullptr));
#endif // QT_CONFIG(statustip)
        textLabel1->setText(QCoreApplication::translate("SettingsDialog", "Device:", nullptr));
        BaudRateLabel->setText(QCoreApplication::translate("SettingsDialog", "Baud Rate:", nullptr));
        textLabel4->setText(QCoreApplication::translate("SettingsDialog", "Flow Control:", nullptr));
        DeviceComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "/dev/ttyUSB0", nullptr));
        DeviceComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "/dev/ttyUSB1", nullptr));
        DeviceComboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "/dev/ttyUSB2", nullptr));
        DeviceComboBox->setItemText(3, QCoreApplication::translate("SettingsDialog", "/dev/ttyUSB3", nullptr));
        DeviceComboBox->setItemText(4, QCoreApplication::translate("SettingsDialog", "/dev/ttyS0", nullptr));
        DeviceComboBox->setItemText(5, QCoreApplication::translate("SettingsDialog", "/dev/ttyS1", nullptr));
        DeviceComboBox->setItemText(6, QCoreApplication::translate("SettingsDialog", "/dev/ttyS2", nullptr));
        DeviceComboBox->setItemText(7, QCoreApplication::translate("SettingsDialog", "/dev/ttyS3", nullptr));

#if QT_CONFIG(tooltip)
        DeviceComboBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Specify the name of the serial device.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        DeviceComboBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Specify the name of the serial device.", nullptr));
#endif // QT_CONFIG(statustip)
        FlowControlComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "NONE", nullptr));
        FlowControlComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "XON/XOFF", nullptr));
        FlowControlComboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "RTS/CTS", nullptr));

#if QT_CONFIG(tooltip)
        FlowControlComboBox->setToolTip(QCoreApplication::translate("SettingsDialog", "Specify the flow control method.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        FlowControlComboBox->setStatusTip(QCoreApplication::translate("SettingsDialog", "Specify the flow control method.", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        FlowControlComboBox->setWhatsThis(QCoreApplication::translate("SettingsDialog", "Specify the flow control method.", nullptr));
#endif // QT_CONFIG(whatsthis)
        tabWidget->setTabText(tabWidget->indexOf(DeviceTab), QCoreApplication::translate("SettingsDialog", "Device", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(LogTab), QCoreApplication::translate("SettingsDialog", "Log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
