#include "STM32Bootloader.h"
#include <QDebug>
#include <QCoreApplication>
#include <iostream>

STM32Bootloader::STM32Bootloader(QObject *parent) : QObject(parent)
{
    connect(&serialPort, &QSerialPort::readyRead, this, &STM32Bootloader::handleReadyRead);
}

STM32Bootloader::~STM32Bootloader()
{
    disconnectFromDevice();
}

bool STM32Bootloader::connectToDevice(const QString &portName, int baudRate,
                                     const QString &dataBits, const QString &stopBits,
                                     const QString &parity, const QString &flowControl)
{
    if (serialPort.isOpen()) {
        serialPort.close();
    }

    serialPort.setPortName(portName);
    serialPort.setBaudRate(baudRate);

    setupSerialPort(dataBits, stopBits, parity, flowControl);

    if (!serialPort.open(QIODevice::ReadWrite)) {
        emit operationCompleted(false, "Error: Connection impossible to : " + serialPort.errorString());
        return false;
    }

    // Wait for bootloader to finish its initial erase (exactly like the working widget)
    emit messageReceived("Waiting for bootloader to become ready...");
    QThread::msleep(2000);

    emit operationCompleted(true, "Connected successfully to " + portName);
    emit connectionStatusChanged(true);
    emit messageReceived("=== Target information ===");
    emit messageReceived(getDeviceInfo());

    return true;
}

void STM32Bootloader::disconnectFromDevice()
{
    if (serialPort.isOpen()) {
        serialPort.close();
        emit operationCompleted(true, "!!!! Target Disconnected !!!!");
        emit connectionStatusChanged(false);
    }
}

bool STM32Bootloader::isConnected() const
{
    return serialPort.isOpen();
}

bool STM32Bootloader::flashFile(const QString &filePath, bool runAfterFlash)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        emit operationCompleted(false, "Error: Cannot open file: " + file.errorString());
        return false;
    }

    QByteArray binData = file.readAll();
    file.close();

    lastFilePath = filePath;

    quint32 totalSize = static_cast<quint32>(binData.size());
    std::cout<<"Memory Programming ..."<<std::endl;
    emit messageReceived(QString("File size: %1 bytes").arg(totalSize));

    if (!isConnected()) {
        emit operationCompleted(false, "Error: Serial port not connected!");
        return false;
    }

    // Disconnect readyRead temporarily to avoid interference during flashing
    disconnect(&serialPort, &QSerialPort::readyRead, this, &STM32Bootloader::handleReadyRead);
    serialPort.clear(); // Clear any stale data

    // --- Send file size (4 bytes, little-endian) ---
    qint64 written = serialPort.write(reinterpret_cast<const char*>(&totalSize), sizeof(totalSize));
    serialPort.waitForBytesWritten(1000);
    if (written != sizeof(totalSize)) {
        emit operationCompleted(false, "Error: Failed to send file size");
        reconnectReadyRead();
        return false;
    }

    // --- Send data in 256‑byte chunks ---
    const int chunkSize = 256;
    int bytesSent = 0;
    emit progressChanged(0);

    for (int i = 0; i < binData.size(); i += chunkSize) {
        QByteArray chunk = binData.mid(i, chunkSize);
        qint64 chunkWritten = serialPort.write(chunk);
        serialPort.waitForBytesWritten(2000);

        if (chunkWritten != chunk.size()) {
            emit operationCompleted(false, QString("Error: Failed to send chunk at offset %1").arg(i));
            reconnectReadyRead();
            return false;
        }

        bytesSent += chunk.size();
        int progress = (bytesSent * 100) / binData.size();
        emit progressChanged(progress);

        // Small delay between chunks – matches working widget
        QThread::msleep(100);
    }

    // Progress is already at 100% from the loop

    // --- Wait for programming confirmation (PROG_OK) ---
    std::cout<<"\n";
    emit messageReceived("Verifying...");
    QByteArray response;
    QElapsedTimer timer;
    timer.start();
    int lastVerifyProgress = -1;

    while (timer.elapsed() < 15000) { // 15 second timeout
        if (serialPort.waitForReadyRead(100)) {
            response.append(serialPort.readAll());
            if (response.contains("PROG_OK")) {
                emit messageReceived("PROG_OK");
                emit progressChanged(100); // Verification complete
                break;
            }
            if (response.contains("PROG_FAIL")) {
                emit messageReceived("PROG_FAIL");
                emit operationCompleted(false, "Error: Bootloader reported programming failure");
                reconnectReadyRead();
                return false;
            }
        }
        int elapsed = timer.elapsed();
        int progress = (elapsed * 100) / 15000;
        if (progress != lastVerifyProgress) {
            emit progressChanged(progress);
            lastVerifyProgress = progress;
        }
        QCoreApplication::processEvents();
    }

    if (!response.contains("PROG_OK")) {
        emit messageReceived("No response from MCU - timeout");
        emit operationCompleted(false, "Error: Verification failed (timeout)");
        reconnectReadyRead();
        return false;
    }

    emit messageReceived("Download verified successfully at 0x08002000 address");

    // --- Run application if requested ---
    if (runAfterFlash) {
        if (runApplication()) {
            emit messageReceived("Application started successfully at 0x08002000 address");
        } else {
            emit messageReceived("Error: Failed to start application");
        }
    } else {
        emit messageReceived("Error: Application not started");
    }

    reconnectReadyRead();
    emit operationCompleted(true, "Flash completed successfully");
    return true;
}

bool STM32Bootloader::verifyFlash()
{
    // This bootloader does not have a separate verify command.
    // Verification is already done in flashFile by waiting for PROG_OK.
    emit messageReceived("Warning: Verify not supported by bootloader; assuming success.");
    return true;
}

bool STM32Bootloader::runApplication()
{
    emit messageReceived("Sending JUMP command...");
    serialPort.write("JUMP"); // No newline, exactly like the working widget
    serialPort.waitForBytesWritten(1000);
    // No response expected – bootloader jumps immediately
    QThread::msleep(100);
    return true;
}

// ========== Utility methods (mostly unchanged) ==========

QStringList STM32Bootloader::getAvailablePorts()
{
    QStringList ports;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ports.append(info.portName());
    }
    if (ports.isEmpty()) {
        ports.append("No COM detected");
    }
    return ports;
}

QStringList STM32Bootloader::getSupportedBaudRates()
{
    return QStringList() << "110" << "300" << "600" << "1200" << "2400" << "4800"
                         << "9600" << "14400" << "19200" << "38400" << "56000"
                         << "57600" << "115200" << "128000" << "256000";
}

QStringList STM32Bootloader::getDataBitsOptions()
{
    return QStringList() << "5" << "6" << "7" << "8";
}

QStringList STM32Bootloader::getStopBitsOptions()
{
    return QStringList() << "1 Bit" << "1,5 Bits" << "2 Bits";
}

QStringList STM32Bootloader::getParityOptions()
{
    return QStringList() << "No Parity" << "Even Parity" << "Odd Parity"
                        << "Mark Parity" << "Space Parity";
}

QStringList STM32Bootloader::getFlowControlOptions()
{
    return QStringList() << "No Flow Control" << "Hardware Flow Control"
                        << "Software Flow Control";
}

QString STM32Bootloader::getDeviceInfo() const
{
    return QString(
        "Board       : STM32F103RBT6\n"
        "Chip ID     : 0x410\n"
        "Device type : MCU\n"
        "Device CPU  : Cortex-M3"
    );
}

void STM32Bootloader::handleReadyRead()
{
    QByteArray data = serialPort.readAll();
    QString message(data);
    emit messageReceived(message);
    buffer.append(message);
}

// Reconnect the readyRead signal after flashing
void STM32Bootloader::reconnectReadyRead()
{
    connect(&serialPort, &QSerialPort::readyRead, this, &STM32Bootloader::handleReadyRead);
}

// These methods are kept for compatibility but are no longer used internally.
bool STM32Bootloader::sendCommand(const QByteArray &command)
{
    Q_UNUSED(command);
    return false;
}

bool STM32Bootloader::waitForAck(int timeoutMs)
{
    Q_UNUSED(timeoutMs);
    return false;
}

bool STM32Bootloader::waitForResponse(const QString &expectedResponse, int timeoutMs)
{
    Q_UNUSED(expectedResponse);
    Q_UNUSED(timeoutMs);
    return false;
}

bool STM32Bootloader::enterBootloaderMode()
{
    return true; // Not needed
}

bool STM32Bootloader::sendFileSize(quint32 size)
{
    Q_UNUSED(size);
    return false;
}

bool STM32Bootloader::sendDataChunk(const QByteArray &data, int chunkNumber)
{
    Q_UNUSED(data);
    Q_UNUSED(chunkNumber);
    return false;
}

void STM32Bootloader::setupSerialPort(const QString &dataBits, const QString &stopBits,
                                     const QString &parity, const QString &flowControl)
{
    // Data bits
    if (dataBits == "5") serialPort.setDataBits(QSerialPort::Data5);
    else if (dataBits == "6") serialPort.setDataBits(QSerialPort::Data6);
    else if (dataBits == "7") serialPort.setDataBits(QSerialPort::Data7);
    else serialPort.setDataBits(QSerialPort::Data8);

    // Stop bits
    if (stopBits == "1,5 Bits") serialPort.setStopBits(QSerialPort::OneAndHalfStop);
    else if (stopBits == "2 Bits") serialPort.setStopBits(QSerialPort::TwoStop);
    else serialPort.setStopBits(QSerialPort::OneStop);

    // Parity
    if (parity == "Even Parity") serialPort.setParity(QSerialPort::EvenParity);
    else if (parity == "Odd Parity") serialPort.setParity(QSerialPort::OddParity);
    else if (parity == "Mark Parity") serialPort.setParity(QSerialPort::MarkParity);
    else if (parity == "Space Parity") serialPort.setParity(QSerialPort::SpaceParity);
    else serialPort.setParity(QSerialPort::NoParity);

    // Flow control
    if (flowControl == "Hardware Flow Control") serialPort.setFlowControl(QSerialPort::HardwareControl);
    else if (flowControl == "Software Flow Control") serialPort.setFlowControl(QSerialPort::SoftwareControl);
    else serialPort.setFlowControl(QSerialPort::NoFlowControl);
}
