#include "inregistrare.h"
#include "start.h"
#include <qmessagebox.h>
#include "ClientBackend.h"
#include <SQLManager.h>

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
	ClientBackend& cb = ClientBackend::getInstance();
	QString mail = ui.mail_edit->text();
	QString username= ui.username_edit->text();
	QString parola = ui.parola_edit->text();

	if (!mail.isEmpty() && !username.isEmpty() && !parola.isEmpty() && parola.size() >= 6)
	{
		cb.Incoming().clear();
		cb.Register(mail, username, parola);

		while (cb.Incoming().empty())
		{
			// wait
		}
		
		if (!cb.Incoming().empty())
		{
			auto msg = cb.Incoming().pop_front().msg;
			if (msg.header.id == CustomMsgTypes::ServerMessage)
			{
				//SQLManager::getInstance()->insert_data(mail.toStdString(), username.toStdString(), parola.toStdString());
				hide();
				login_window = new CabManClient;
				login_window->show();
			}
			
		}
	}
	else
	{
		QMessageBox::warning(this, "RegisterFault", "Datele au fost introduse in mod eronat sau nu au fost introduse!");
	}
}