#include "ClientBackend.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "login.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientBackend& cb = ClientBackend::getInstance();
    CabManClient w;
    w.show();
    return a.exec();
}