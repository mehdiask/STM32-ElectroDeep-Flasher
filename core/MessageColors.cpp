#include "MessageColors.h"

MessageColors::MessageType MessageColors::classifyMessage(const QString &message)
{
    if (message.contains("success", Qt::CaseInsensitive) ||
        message.contains("ok", Qt::CaseInsensitive) ||
        message.startsWith("✓")) {
        return Success;
    }
    if (message.contains("fail", Qt::CaseInsensitive) ||
        message.contains("error", Qt::CaseInsensitive) ||
        message.contains("timeout", Qt::CaseInsensitive) ||
        message.startsWith("✗")) {
        return Error;
    }
    if (message.contains("warning", Qt::CaseInsensitive)) {
        return Warning;
    }
    return Info;
}

QString MessageColors::colorMessageForGUI(const QString &message, MessageType type)
{
    switch (type) {
    case Info:
        return message;
    case Success:
        return QString("<font color='green'>%1</font>").arg(message);
    case Warning:
        return QString("<font color='yellow'>%1</font>").arg(message);
    case Error:
        return QString("<font color='red'>%1</font>").arg(message);
    }
    return message;
}

QString MessageColors::colorMessageForCLI(const QString &message, MessageType type)
{
    switch (type) {
    case Info:
        return message;
    case Success:
        return QString("\033[32m%1\033[0m").arg(message); // green
    case Warning:
        return QString("\033[33m%1\033[0m").arg(message); // yellow
    case Error:
        return QString("\033[31m%1\033[0m").arg(message); // red
    }
    return message;
}