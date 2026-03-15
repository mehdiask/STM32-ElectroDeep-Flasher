#ifndef STM32BOOTLOADER_H
#define STM32BOOTLOADER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFile>
#include <QThread>
#include <QStringList>
#include <QElapsedTimer>

class STM32Bootloader : public QObject
{
    Q_OBJECT

public:
    explicit STM32Bootloader(QObject *parent = nullptr);
    ~STM32Bootloader();

    bool connectToDevice(const QString &portName, int baudRate,
                        const QString &dataBits = "8",
                        const QString &stopBits = "1 Bit",
                        const QString &parity = "No Parity",
                        const QString &flowControl = "No Flow Control");

    void disconnectFromDevice();
    bool isConnected() const;

    bool flashFile(const QString &filePath, bool runAfterFlash = false);
    bool verifyFlash();
    bool runApplication();
    void reconnectReadyRead();

    static QStringList getAvailablePorts();
    static QStringList getSupportedBaudRates();
    static QStringList getDataBitsOptions();
    static QStringList getStopBitsOptions();
    static QStringList getParityOptions();
    static QStringList getFlowControlOptions();

    QString getDeviceInfo() const;

signals:
    void progressChanged(int percentage);
    void messageReceived(const QString &message);
    void operationCompleted(bool success, const QString &message);
    void connectionStatusChanged(bool connected);

private slots:
    void handleReadyRead();

private:
    QSerialPort serialPort;
    QString buffer;
    QString lastFilePath;

    bool sendCommand(const QByteArray &command);
    bool waitForAck(int timeoutMs = 3000);
    bool waitForResponse(const QString &expectedResponse, int timeoutMs = 3000);
    bool enterBootloaderMode();
    bool sendFileSize(quint32 size);
    bool sendDataChunk(const QByteArray &data, int chunkNumber);
    void setupSerialPort(const QString &dataBits, const QString &stopBits,
                        const QString &parity, const QString &flowControl);
};

#endif // STM32BOOTLOADER_H
