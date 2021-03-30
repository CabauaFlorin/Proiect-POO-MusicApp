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
    QString username = ui.username_edit->text();
    QString password = ui.parola_edit->text();

    if (username == "test" && password == "test")
    {
        QMessageBox::information(this, "Login", "V-ati autentificat cu succes!");
    }
    else
    {
        QMessageBox::warning(this, "Login", "Username-ul si parola sunt incorecte!");
    }
}