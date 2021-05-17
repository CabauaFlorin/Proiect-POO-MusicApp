#include "ClientBackend.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "start.h"

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    QApplication a(argc, argv);

    ClientBackend& cb = ClientBackend::getInstance();
    start w;
    w.show();
    return a.exec();
}