#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "../Core/STM32Bootloader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_Connect_clicked();
    void on_pushButton_Disconnect_clicked();
    void on_pushButton_Refresh_clicked();
    void on_pushButton_Clear_clicked();
    void on_pushButton_flashRun_clicked();
    void on_pushButton_Browse_clicked();

    void onProgressChanged(int percentage);
    void onMessageReceived(const QString &message);
    void onOperationCompleted(bool success, const QString &message);
    void onConnectionStatusChanged(bool connected);

private:
    Ui::Widget *ui;
    STM32Bootloader *m_bootloader;
    QString m_filePath;

    void updateConnectionButtons(bool connected);
    void setupComboBoxes();
};

#endif // WIDGET_H
