#include "start.h"
#include "inregistrare.h"

start::start(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void start::on_register_button_clicked()
{
	hide();
	register_window = new inregistrare;
	register_window->show();
}

void start::on_log_in_button_clicked()
{
	hide();
	login_window = new CabManClient;
	login_window->show();
}