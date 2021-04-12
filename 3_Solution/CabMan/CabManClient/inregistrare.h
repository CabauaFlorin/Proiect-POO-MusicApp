#pragma once

#include <QWidget>
#include "ui_inregistrare.h"
#include "login.h"


class start;
class inregistrare : public QWidget
{
	Q_OBJECT

public:
	inregistrare(QWidget* parent = Q_NULLPTR);
	~inregistrare() {}

private:
	Ui::inregistrare ui;
	start* start_window;
	CabManClient* login_window;

private slots:
	void on_back_button_clicked();
	void on_register_button_clicked();
};