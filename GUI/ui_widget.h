/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton_Clear;
    QLabel *label_3DataBit;
    QComboBox *comboBox_1Port;
    QComboBox *comboBox_5Parity;
    QPushButton *pushButton_Refresh;
    QProgressBar *progressBar;
    QPushButton *pushButton_Disconnect;
    QPushButton *pushButton_Browse;
    QLineEdit *lineEditFilePath;
    QPushButton *pushButton_flashRun;
    QLabel *label_6FlowControl;
    QLabel *label_4StopBit;
    QComboBox *comboBox_3DataBit;
    QLabel *label_2BaudRate;
    QComboBox *comboBox_6FlowControl;
    QLabel *label_1Port;
    QPushButton *pushButton_Connect;
    QLabel *label_5Parity;
    QComboBox *comboBox_2BaudRate;
    QTextBrowser *LogMessages;
    QComboBox *comboBox_4StopBit;
    QRadioButton *CheckBoxRun;
    QFrame *line;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->setEnabled(true);
        Widget->resize(824, 406);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setAcceptDrops(false);
        Widget->setAutoFillBackground(false);
        Widget->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        pushButton_Clear = new QPushButton(Widget);
        pushButton_Clear->setObjectName(QString::fromUtf8("pushButton_Clear"));
        pushButton_Clear->setGeometry(QRect(750, 80, 41, 23));
        label_3DataBit = new QLabel(Widget);
        label_3DataBit->setObjectName(QString::fromUtf8("label_3DataBit"));
        label_3DataBit->setGeometry(QRect(40, 150, 47, 13));
        comboBox_1Port = new QComboBox(Widget);
        comboBox_1Port->setObjectName(QString::fromUtf8("comboBox_1Port"));
        comboBox_1Port->setGeometry(QRect(120, 90, 131, 21));
        comboBox_5Parity = new QComboBox(Widget);
        comboBox_5Parity->setObjectName(QString::fromUtf8("comboBox_5Parity"));
        comboBox_5Parity->setGeometry(QRect(120, 210, 131, 22));
        pushButton_Refresh = new QPushButton(Widget);
        pushButton_Refresh->setObjectName(QString::fromUtf8("pushButton_Refresh"));
        pushButton_Refresh->setGeometry(QRect(260, 90, 71, 23));
        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 310, 751, 24));
        progressBar->setValue(24);
        pushButton_Disconnect = new QPushButton(Widget);
        pushButton_Disconnect->setObjectName(QString::fromUtf8("pushButton_Disconnect"));
        pushButton_Disconnect->setGeometry(QRect(160, 50, 91, 23));
        pushButton_Browse = new QPushButton(Widget);
        pushButton_Browse->setObjectName(QString::fromUtf8("pushButton_Browse"));
        pushButton_Browse->setGeometry(QRect(720, 50, 75, 23));
        lineEditFilePath = new QLineEdit(Widget);
        lineEditFilePath->setObjectName(QString::fromUtf8("lineEditFilePath"));
        lineEditFilePath->setGeometry(QRect(350, 50, 361, 20));
        pushButton_flashRun = new QPushButton(Widget);
        pushButton_flashRun->setObjectName(QString::fromUtf8("pushButton_flashRun"));
        pushButton_flashRun->setGeometry(QRect(350, 80, 91, 23));
        label_6FlowControl = new QLabel(Widget);
        label_6FlowControl->setObjectName(QString::fromUtf8("label_6FlowControl"));
        label_6FlowControl->setGeometry(QRect(40, 240, 61, 16));
        label_4StopBit = new QLabel(Widget);
        label_4StopBit->setObjectName(QString::fromUtf8("label_4StopBit"));
        label_4StopBit->setGeometry(QRect(40, 180, 51, 16));
        comboBox_3DataBit = new QComboBox(Widget);
        comboBox_3DataBit->setObjectName(QString::fromUtf8("comboBox_3DataBit"));
        comboBox_3DataBit->setGeometry(QRect(120, 150, 131, 22));
        label_2BaudRate = new QLabel(Widget);
        label_2BaudRate->setObjectName(QString::fromUtf8("label_2BaudRate"));
        label_2BaudRate->setGeometry(QRect(40, 120, 51, 16));
        comboBox_6FlowControl = new QComboBox(Widget);
        comboBox_6FlowControl->setObjectName(QString::fromUtf8("comboBox_6FlowControl"));
        comboBox_6FlowControl->setGeometry(QRect(120, 240, 131, 22));
        label_1Port = new QLabel(Widget);
        label_1Port->setObjectName(QString::fromUtf8("label_1Port"));
        label_1Port->setGeometry(QRect(40, 90, 47, 13));
        pushButton_Connect = new QPushButton(Widget);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));
        pushButton_Connect->setGeometry(QRect(40, 50, 101, 23));
        label_5Parity = new QLabel(Widget);
        label_5Parity->setObjectName(QString::fromUtf8("label_5Parity"));
        label_5Parity->setGeometry(QRect(40, 210, 47, 13));
        comboBox_2BaudRate = new QComboBox(Widget);
        comboBox_2BaudRate->setObjectName(QString::fromUtf8("comboBox_2BaudRate"));
        comboBox_2BaudRate->setGeometry(QRect(120, 120, 131, 22));
        LogMessages = new QTextBrowser(Widget);
        LogMessages->setObjectName(QString::fromUtf8("LogMessages"));
        LogMessages->setGeometry(QRect(350, 110, 441, 171));
        comboBox_4StopBit = new QComboBox(Widget);
        comboBox_4StopBit->setObjectName(QString::fromUtf8("comboBox_4StopBit"));
        comboBox_4StopBit->setGeometry(QRect(120, 180, 131, 22));
        CheckBoxRun = new QRadioButton(Widget);
        CheckBoxRun->setObjectName(QString::fromUtf8("CheckBoxRun"));
        CheckBoxRun->setGeometry(QRect(500, 80, 181, 21));
        line = new QFrame(Widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(330, 40, 20, 231));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton_Clear->setText(QApplication::translate("Widget", "Clear", nullptr));
        label_3DataBit->setText(QApplication::translate("Widget", "Data bit", nullptr));
        pushButton_Refresh->setText(QApplication::translate("Widget", "Refresh", nullptr));
        pushButton_Disconnect->setText(QApplication::translate("Widget", "Disconnect", nullptr));
        pushButton_Browse->setText(QApplication::translate("Widget", "Browse", nullptr));
        pushButton_flashRun->setText(QApplication::translate("Widget", "Start flashing", nullptr));
        label_6FlowControl->setText(QApplication::translate("Widget", "Flow control", nullptr));
        label_4StopBit->setText(QApplication::translate("Widget", "Stop bit", nullptr));
        label_2BaudRate->setText(QApplication::translate("Widget", "Baud rate", nullptr));
        label_1Port->setText(QApplication::translate("Widget", "Port", nullptr));
        pushButton_Connect->setText(QApplication::translate("Widget", "Connect", nullptr));
        label_5Parity->setText(QApplication::translate("Widget", "Parity", nullptr));
        CheckBoxRun->setText(QApplication::translate("Widget", "Run after flashing", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
