#include "C:\Users\MEHDI ASKRI\Desktop\Qt-projects\STM32_UART_Bootloader_Flasher\core\STM32Bootloader.h"
#include "C:\Users\MEHDI ASKRI\Desktop\Qt-projects\STM32_UART_Bootloader_Flasher\core\MessageColors.h"
#include <QCoreApplication>
#include <QRegularExpression>
#include <QDebug>
#include <iostream>
#include <QStringList>
#ifdef Q_OS_WIN
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

void showHelp()
{
    std::cout << "STM32 UART Bootloader Command Line Interface\n"
              << "Usage: cli_app [options]\n\n"
              << "Options:\n"
              << "  -c, --connect <port>       Connect to device on specified port\n"
              << "  -b, --baudrate <rate>      Baud rate (default: 115200)\n"
              << "  -f, --flash <file>         Flash binary file\n"
              << "  -r, --run                   Run application after flashing\n"
              << "  -v, --verify                 Verify flash\n"
              << "  -d, --disconnect             Disconnect from device\n"
              << "  -l, --list                   List available COM ports\n"
              << "  -h, --help                    Show this help\n"
              << "      --version                 Show version\n";
}

void showVersion()
{
    std::cout << "version 1.0.0\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName("STM32 CLI Flasher");
    app.setApplicationVersion("1.0.0");

#ifdef Q_OS_WIN
    // Enable ANSI escape codes in Windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif

    std::cout << "--------------------------------------------\n";
    std::cout << "   STM32 ElectroDeep CLI Flasher v1.0.0\n";
    std::cout << "--------------------------------------------\n";

    // Store parsed options
    QString connectPort;
    int baudRate = 115200;          // default
    QString flashFile;
    bool runAfterFlash = false;
    bool verifyFlash = false;
    bool disconnect = false;
    bool listPorts = false;
    bool showHelpFlag = false;
    bool showVersionFlag = false;

    // Regex patterns
    QRegularExpression longOptWithEq("^--([a-zA-Z-]+)=(.*)$");
    QRegularExpression longOpt("^--([a-zA-Z-]+)$");
    QRegularExpression shortOpt("^-([a-zA-Z])$");

    QStringList args = app.arguments();
    // Debug: print all arguments
    //std::cerr << "Arguments received:" << std::endl;
    //for (const QString &a : args) {
    //    std::cerr << "  [" << a.toStdString() << "]" << std::endl;
    //}

    for (int i = 1; i < args.size(); ++i) {
        QString arg = args[i];

        // --option=value
        QRegularExpressionMatch match = longOptWithEq.match(arg);
        if (match.hasMatch()) {
            QString opt = match.captured(1);
            QString val = match.captured(2);
            if (opt == "connect" || opt == "c") {
                connectPort = val;
            } else if (opt == "baudrate" || opt == "b") {
                baudRate = val.toInt();
            } else if (opt == "flash" || opt == "f") {
                flashFile = val;
            } else {
                std::cerr << "Unknown option: " << arg.toStdString() << std::endl;
                return 1;
            }
            continue;
        }

        // --option (no '=')
        match = longOpt.match(arg);
        if (match.hasMatch()) {
            QString opt = match.captured(1);
            if (opt == "help" || opt == "h") {
                showHelpFlag = true;
            } else if (opt == "version") {
                showVersionFlag = true;
            } else if (opt == "run" || opt == "r") {
                runAfterFlash = true;
            } else if (opt == "verify" || opt == "v") {
                verifyFlash = true;
            } else if (opt == "disconnect" || opt == "d") {
                disconnect = true;
            } else if (opt == "list" || opt == "l") {
                listPorts = true;
            } else if (opt == "connect" || opt == "c" ||
                       opt == "baudrate" || opt == "b" ||
                       opt == "flash" || opt == "f") {
                // These require a value; check next argument
                if (i + 1 >= args.size()) {
                    std::cerr << "Option " << arg.toStdString() << " requires a value." << std::endl;
                    return 1;
                }
                QString value = args[++i];
                if (opt == "connect" || opt == "c") {
                    connectPort = value;
                } else if (opt == "baudrate" || opt == "b") {
                    baudRate = value.toInt();
                } else if (opt == "flash" || opt == "f") {
                    flashFile = value;
                }
            } else {
                std::cerr << "Unknown option: " << arg.toStdString() << std::endl;
                return 1;
            }
            continue;
        }

        // Short options like -c
        match = shortOpt.match(arg);
        if (match.hasMatch()) {
            QString opt = match.captured(1);
            if (opt == "h") {
                showHelpFlag = true;
            } else if (opt == "r") {
                runAfterFlash = true;
            } else if (opt == "v") {
                verifyFlash = true;
            } else if (opt == "d") {
                disconnect = true;
            } else if (opt == "l") {
                listPorts = true;
            } else if (opt == "c" || opt == "b" || opt == "f") {
                if (i + 1 >= args.size()) {
                    std::cerr << "Option -" << opt.toStdString() << " requires a value." << std::endl;
                    return 1;
                }
                QString value = args[++i];
                if (opt == "c") {
                    connectPort = value;
                } else if (opt == "b") {
                    baudRate = value.toInt();
                } else if (opt == "f") {
                    flashFile = value;
                }
            } else {
                std::cerr << "Unknown option: -" << opt.toStdString() << std::endl;
                return 1;
            }
            continue;
        }

        std::cerr << "Invalid argument: " << arg.toStdString() << std::endl;
        return 1;
    }

    // Debug: print parsed values
    std::cerr << "UART configuration:" << std::endl;
    std::cerr << "  connectPort = " << connectPort.toStdString() << std::endl;
    std::cerr << "  baudRate = " << baudRate << std::endl;
    std::cerr << "  flashFile = " << flashFile.toStdString() << std::endl;
    std::cerr << "  runAfterFlash = " << runAfterFlash << std::endl;
    std::cerr << "  verifyFlash = " << verifyFlash << std::endl;
    std::cerr << "  disconnect = " << disconnect << std::endl;
    std::cerr << "  listPorts = " << listPorts << std::endl;

    // Handle help and version first
    if (showHelpFlag) {
        showHelp();
        return 0;
    }
    if (showVersionFlag) {
        showVersion();
        return 0;
    }

    STM32Bootloader bootloader;

    // Connect signals for CLI output
    QObject::connect(&bootloader, &STM32Bootloader::messageReceived,
                     [](const QString &msg) {
                         MessageColors::MessageType type = MessageColors::classifyMessage(msg);
                         QString colored = MessageColors::colorMessageForCLI(msg, type);
                         std::cout << colored.toStdString() << std::endl;
                     });

    QObject::connect(&bootloader, &STM32Bootloader::operationCompleted,
                     [&app](bool success, const QString &msg) {
                         QString fullMsg = (success ? "✓ " : "✗ ") + msg;
                         MessageColors::MessageType type = MessageColors::classifyMessage(fullMsg);
                         QString colored = MessageColors::colorMessageForCLI(fullMsg, type);
                         std::cout << colored.toStdString() << std::endl;
                         if (!success && !msg.contains("Disconnected")) {
                             app.exit(1);
                         }
                     });

    // List ports
    if (listPorts) {
        auto ports = STM32Bootloader::getAvailablePorts();
        std::cout << "Available COM ports:" << std::endl;
        for (const auto &port : ports) {
            std::cout << "  " << port.toStdString() << std::endl;
        }
        return 0;
    }

    // Connect to device if requested
    if (!connectPort.isEmpty()) {
        if (!bootloader.connectToDevice(connectPort, baudRate)) {
            return 1;
        }
        std::cout << "Connected successfully to " << connectPort.toStdString() << std::endl;
    }

    // Flash file if requested
    if (!flashFile.isEmpty()) {
        if (!bootloader.isConnected()) {
            std::cerr << "Error: Not connected to device. Use --connect first." << std::endl;
            return 1;
        }
        if (!bootloader.flashFile(flashFile, runAfterFlash)) {
            return 1;
        }
        std::cout << "Flash successful!" << std::endl;
    } else if (runAfterFlash) {
        std::cerr << "Warning: --run specified but no --flash file given." << std::endl;
    }

    // Verify flash if requested
    if (verifyFlash) {
        if (!bootloader.isConnected()) {
            std::cerr << "Error: Not connected to device." << std::endl;
            return 1;
        }
        if (!bootloader.verifyFlash()) {
            return 1;
        }
        std::cout << "Verification successful!" << std::endl;
    }

    // Disconnect if requested
    if (disconnect) {
        bootloader.disconnectFromDevice();
    }

    // If no options provided, show help
    if (argc == 1) {
        showHelp();
        return 0;
    }

    return app.exec();
}
