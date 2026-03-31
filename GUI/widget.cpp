#include "widget.h"
#include "ui_widget.h"
#include "../core/MessageColors.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QAction>
#include <QPixmap>
#include <QTextCursor>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_bootloader(new STM32Bootloader(this))
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("STM32 ElectroDeep Flasher");
    setFixedSize(width(), height());
    QString appDir = QApplication::applicationDirPath();
    QString iconPath = appDir + "./images/Logo-ElectroDev-2.PNG";
    setWindowIcon(QIcon(iconPath));

    // Setup combo boxes
    setupComboBoxes();

    // Initialize UI state
    updateConnectionButtons(false);
    ui->progressBar->setValue(0);
    ui->progressBar->setTextVisible(true);
    ui->progressBar->setFormat("%p%");
    ui->progressBar->setStyleSheet(
        "QProgressBar {"
        "  border: 1px solid #aaa;"
        "  border-radius: 8px;"
        "  background-color: #f0f0f0;"
        "  color: #000000;"
        "  text-align: center;"
        "}"
        "QProgressBar::chunk {"
        "  border-radius: 8px;"
        "  background-color: #4caf50;"
        "}"
    );

    // Connect bootloader signals
    connect(m_bootloader, &STM32Bootloader::progressChanged,
            this, &Widget::onProgressChanged);
    connect(m_bootloader, &STM32Bootloader::messageReceived,
            this, &Widget::onMessageReceived);
    connect(m_bootloader, &STM32Bootloader::operationCompleted,
            this, &Widget::onOperationCompleted);
    connect(m_bootloader, &STM32Bootloader::connectionStatusChanged,
            this, &Widget::onConnectionStatusChanged);

    // Setup menu bar
    QVBoxLayout *layout = new QVBoxLayout(this);
    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *helpMenu = menuBar->addMenu("Help");
    QAction *aboutAction = helpMenu->addAction("About");
    QAction *exitAction = helpMenu->addAction("Exit");

    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QString appDir = QApplication::applicationDirPath();
        QString iconPath = appDir + "./images/Logo-ElectroDev.PNG";
        QPixmap logo(iconPath);

        QMessageBox msgBox(this);
        msgBox.setWindowTitle("About STM32 ElectroDeep Flasher");
        msgBox.setText("STM32 ElectroDeep Flasher Application v1.0.0\n\nDeveloped by ElectroDeep Organization");
        msgBox.setIconPixmap(logo.scaled(77, 81, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        msgBox.exec();
    });

    layout->setMenuBar(menuBar);
    setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setupComboBoxes()
{
    // Ports
    ui->comboBox_1Port->clear();
    ui->comboBox_1Port->addItems(STM32Bootloader::getAvailablePorts());

    // Baud rates
    ui->comboBox_2BaudRate->clear();
    ui->comboBox_2BaudRate->addItems(STM32Bootloader::getSupportedBaudRates());
    ui->comboBox_2BaudRate->setCurrentText("115200");

    // Data bits
    ui->comboBox_3DataBit->clear();
    ui->comboBox_3DataBit->addItems(STM32Bootloader::getDataBitsOptions());
    ui->comboBox_3DataBit->setCurrentText("8");

    // Stop bits
    ui->comboBox_4StopBit->clear();
    ui->comboBox_4StopBit->addItems(STM32Bootloader::getStopBitsOptions());

    // Parity
    ui->comboBox_5Parity->clear();
    ui->comboBox_5Parity->addItems(STM32Bootloader::getParityOptions());

    // Flow control
    ui->comboBox_6FlowControl->clear();
    ui->comboBox_6FlowControl->addItems(STM32Bootloader::getFlowControlOptions());
}

void Widget::on_pushButton_Connect_clicked()
{
    QString portName = ui->comboBox_1Port->currentText();
    int baudRate = ui->comboBox_2BaudRate->currentText().toInt();
    QString dataBits = ui->comboBox_3DataBit->currentText();
    QString stopBits = ui->comboBox_4StopBit->currentText();
    QString parity = ui->comboBox_5Parity->currentText();
    QString flowControl = ui->comboBox_6FlowControl->currentText();

    QString msg = "Attempting to connect...";
    MessageColors::MessageType type = MessageColors::classifyMessage(msg);
    QString colored = MessageColors::colorMessageForGUI(msg, type);
    ui->LogMessages->moveCursor(QTextCursor::End);
    ui->LogMessages->insertHtml(colored + "<br>");

    m_bootloader->connectToDevice(portName, baudRate, dataBits, stopBits, parity, flowControl);
}

void Widget::on_pushButton_Disconnect_clicked()
{
    m_bootloader->disconnectFromDevice();
}

void Widget::on_pushButton_Refresh_clicked()
{
    setupComboBoxes();
    QString msg = "Port list refreshed.";
    MessageColors::MessageType type = MessageColors::classifyMessage(msg);
    QString colored = MessageColors::colorMessageForGUI(msg, type);
    ui->LogMessages->moveCursor(QTextCursor::End);
    ui->LogMessages->insertHtml(colored + "<br>");
}

void Widget::on_pushButton_Clear_clicked()
{
    ui->LogMessages->clear();
}

void Widget::on_pushButton_flashRun_clicked()
{
    if (m_filePath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a file first.");
        return;
    }

    if (!m_bootloader->isConnected()) {
        QMessageBox::warning(this, "Error", "Not connected to device.");
        return;
    }

    bool runAfterFlash = ui->CheckBoxRun->isChecked();
    m_bootloader->flashFile(m_filePath, runAfterFlash);
}

void Widget::on_pushButton_Browse_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        "Select binary file", "", "Binary Files (*.bin);;All Files (*)");

    if (!filePath.isEmpty()) {
        m_filePath = filePath;
        ui->lineEditFilePath->setText(filePath);
        QString msg = "Selected file: " + filePath;
        MessageColors::MessageType type = MessageColors::classifyMessage(msg);
        QString colored = MessageColors::colorMessageForGUI(msg, type);
        ui->LogMessages->moveCursor(QTextCursor::End);
        ui->LogMessages->insertHtml(colored + "<br>");
    }
}

void Widget::onProgressChanged(int percentage)
{
    ui->progressBar->setValue(percentage);
}

void Widget::onMessageReceived(const QString &message)
{
    MessageColors::MessageType type = MessageColors::classifyMessage(message);
    QString colored = MessageColors::colorMessageForGUI(message, type);
    ui->LogMessages->moveCursor(QTextCursor::End);
    ui->LogMessages->insertHtml(colored + "<br>");
}

void Widget::onOperationCompleted(bool success, const QString &message)
{
    QString fullMsg = message;
    MessageColors::MessageType type = MessageColors::classifyMessage(fullMsg);
    QString colored = MessageColors::colorMessageForGUI(fullMsg, type);
    ui->LogMessages->moveCursor(QTextCursor::End);
    ui->LogMessages->insertHtml(colored + "<br>");

    if (!success && !message.contains("Disconnected")) {
        QMessageBox::warning(this, "Operation Failed", message);
    }
}

void Widget::onConnectionStatusChanged(bool connected)
{
    updateConnectionButtons(connected);
}

void Widget::updateConnectionButtons(bool connected)
{
    ui->pushButton_Connect->setEnabled(!connected);
    ui->pushButton_Disconnect->setEnabled(connected);
    ui->pushButton_flashRun->setEnabled(connected);
    ui->pushButton_Refresh->setEnabled(!connected);

    ui->comboBox_1Port->setEnabled(!connected);
    ui->comboBox_2BaudRate->setEnabled(!connected);
    ui->comboBox_3DataBit->setEnabled(!connected);
    ui->comboBox_4StopBit->setEnabled(!connected);
    ui->comboBox_5Parity->setEnabled(!connected);
    ui->comboBox_6FlowControl->setEnabled(!connected);
}
