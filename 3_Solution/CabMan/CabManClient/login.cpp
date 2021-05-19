#include "ClientBackend.h"
#include "login.h"
#include "stdafx.h"
#include <qmessagebox.h>
#include <qtimer.h>


CabManClient::CabManClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

//void CabManClient::on_ping_button_clicked()
//{
//    ClientBackend& cb = ClientBackend::getInstance();
//    cb.Incoming().clear();
//    cb.PingServer();
//
//    while (cb.Incoming().empty())
//    {
//        // wait;
//    }
//
//    if (!cb.Incoming().empty())
//    {
//        auto msg = cb.Incoming().pop_front().msg;
//        if (msg.header.id == olc::net::CustomMsgTypes::ServerPing)
//        {
//            std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
//            std::chrono::system_clock::time_point timeThen;
//            msg >> timeThen;
//            std::chrono::duration<double> duration(timeNow - timeThen);
//            std::string pinging = std::to_string(duration.count());
//            ui.ping_edit->setText(QString(pinging.c_str()));
//        }
//    }
//}

void CabManClient::on_login_button_clicked()
{
    QMessageBox* msgBox = new QMessageBox;
    QString username = ui.username_edit->text();
    QString password = ui.parola_edit->text();

    if (username == "" || password == "")
    {
        msgBox->setText("Va rugam sa completati toate datele!");
        msgBox->show();
        QTimer::singleShot(2500, msgBox, SLOT(close()));
    }

    ClientBackend& cb = ClientBackend::getInstance();
    cb.Incoming().clear();
    cb.LoginRequest(username, password);
    while (cb.Incoming().empty())
    {
        // do wait for response;
        if (!cb.IsConnected())
        {
            msgBox->setText("Server down! Restart the app.");
            msgBox->show();
            QTimer::singleShot(2500, msgBox, SLOT(close()));
        }
    }
    // server has responded.
    if (!cb.Incoming().empty())
    {
        auto msg = cb.Incoming().pop_front().msg;
        if (msg.header.id == olc::net::CustomMsgTypes::ServerLoginResponse)
        {
            char responseFromServer[100];
            msg >> responseFromServer;
            if (strcmp(responseFromServer, "SuccessLogin")==0)
            {
                // permit access to app!
                QMessageBox::information(this, "Login", "V-ati autentificat cu succes!");
                hide();
                main_menu = new main_window;
                main_menu->show();
            }
            else
            {
                QMessageBox::warning(this, "Login", "Username-ul si parola sunt incorecte!");
            }
        }
    }
}