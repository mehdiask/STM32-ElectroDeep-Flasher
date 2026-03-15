#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set application info
    a.setApplicationName("STM32 ElectroDeep Flasher");
    a.setApplicationVersion("1.0.0");
    a.setOrganizationName("ElectroDeep");

    Widget w;
    w.show();

    return a.exec();
}
