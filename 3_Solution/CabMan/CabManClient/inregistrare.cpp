#include "inregistrare.h"
#include "start.h"
#include <qmessagebox.h>
#include "ClientBackend.h"
#include <qtimer.h>

inregistrare::inregistrare(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void inregistrare::on_back_button_clicked()
{
	hide();
	start_window = new start;
	start_window->show();
}

void inregistrare::on_register_button_clicked()
{
	QMessageBox* msgBox = new QMessageBox;
	QString mail = ui.mail_edit->text();
	QString username= ui.username_edit->text();
	QString parola = ui.parola_edit->text();

	if (!mail.isEmpty() && !username.isEmpty() && !parola.isEmpty() && parola.size() >= 6)
	{
		ClientBackend& cb = ClientBackend::getInstance();
		cb.Incoming().clear();
		cb.RegisterRequest(mail, username, parola);

		while (cb.Incoming().empty())
		{
			// wait
			if (!cb.IsConnected())
			{
				msgBox->setText("Server down! Restart the app! Error.");
				msgBox->show();
				QTimer::singleShot(2500, msgBox, SLOT(close()));
			}
		}
		
		if (!cb.Incoming().empty())
		{
			auto msg = cb.Incoming().pop_front().msg;
			if (msg.header.id == olc::net::CustomMsgTypes::ServerRegisterResponse)
			{
				char responseFromServer[100];
				msg >> responseFromServer;
				if (strcmp(responseFromServer, "SuccessRegister") == 0)
				{
					QMessageBox::information(this, "Register", "V-ati inregistrat cu succes!");
					hide();
					login_window = new CabManClient;
					login_window->show();
				}
				else if (strcmp(responseFromServer, "UserAlready") == -1)
				{
					QMessageBox::warning(this, "Register", "Utilizatorul exista deja in baza de date!");
				}
				else
				{
					QMessageBox::warning(this, "Register", "Nu am putut inregistra utilizatorul! Va rugam incercati din nou!");
				}
			}
		}
	}
	else
	{
		QMessageBox::warning(this, "RegisterFault", "Datele au fost introduse in mod eronat sau nu au fost introduse!");
	}
}