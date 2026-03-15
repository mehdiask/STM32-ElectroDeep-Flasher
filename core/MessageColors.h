#ifndef MESSAGECOLORS_H
#define MESSAGECOLORS_H

#include <QString>

class MessageColors
{
public:
    enum MessageType {
        Info,
        Success,
        Warning,
        Error
    };

    static MessageType classifyMessage(const QString &message);

    static QString colorMessageForGUI(const QString &message, MessageType type);
    static QString colorMessageForCLI(const QString &message, MessageType type);
};

#endif // MESSAGECOLORS_H