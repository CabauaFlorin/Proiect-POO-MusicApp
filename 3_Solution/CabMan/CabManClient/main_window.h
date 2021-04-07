#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_main_window.h"

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget *parent = Q_NULLPTR);
	~main_window() {}

private:
	Ui::MainWindow ui;

private slots:
	void on_exit_toolbar_triggered();
};
