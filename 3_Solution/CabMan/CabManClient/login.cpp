#include "ClientBackend.h"
#include "login.h"
#include "stdafx.h"
#include <qmessagebox.h>

CabManClient::CabManClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void CabManClient::on_login_button_clicked()
{
    //QString username = ui.username_edit->text();
    //QString password = ui.parola_edit->text();

    //if (username == "test" && password == "test")
    //{
    //    QMessageBox::information(this, "Login", "V-ati autentificat cu succes!");
    //}
    //else
    //{
    //    QMessageBox::warning(this, "Login", "Username-ul si parola sunt incorecte!");
    //}

    ClientBackend& cb = ClientBackend::getInstance();
    cb.Incoming().clear();
    cb.PingServer();

    while (cb.Incoming().empty())
    {
        // wait;
    }

    if (!cb.Incoming().empty())
    {
        auto msg = cb.Incoming().pop_front().msg;
        if (msg.header.id == CustomMsgTypes::ServerPing)
        {
            std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
            std::chrono::system_clock::time_point timeThen;
            msg >> timeThen;
            std::chrono::duration<double> duration(timeNow - timeThen);
            std::string pinginplm = std::to_string(duration.count());
            ui.username_edit->setText(QString(pinginplm.c_str()));
        }
    }

    


}