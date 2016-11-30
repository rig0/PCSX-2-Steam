#include "pcsx2steam.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PCSX2Steam w;
    w.show();

    return a.exec();
}
