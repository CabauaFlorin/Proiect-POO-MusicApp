#pragma once

#include <QWidget>
#include "ui_start.h"
#include "login.h"
#include "inregistrare.h"

class start : public QWidget
{
	Q_OBJECT

public:
	start(QWidget *parent = Q_NULLPTR);
	~start() {}

private:
	Ui::start ui;
	CabManClient* login_window;
	inregistrare* register_window;
	
private slots:
	void on_register_button_clicked();
	void on_log_in_button_clicked();
};
