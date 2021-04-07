#include "inregistrare.h"

inregistrare::inregistrare(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void inregistrare::on_back_button_clicked()
{
	hide();
}

void inregistrare::on_register_button_clicked()
{
	QString mail = ui.mail_edit->text();
	QString username= ui.username_edit->text();
	QString parola = ui.parola_edit->text();
	if (!mail.isEmpty() && !username.isEmpty() && !parola.isEmpty() && parola.size()>=6)
	{
		hide();
		login_window = new CabManClient;
		login_window->show();
	}
}