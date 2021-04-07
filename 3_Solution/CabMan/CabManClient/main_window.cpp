#include "main_window.h"

main_window::main_window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void main_window::on_exit_toolbar_triggered()
{
	QApplication::quit();
}