#pragma once

#include <QtWidgets/QWidget>
#include "ui_login.h"
#include "main_window.h"

class CabManClient : public QWidget
{
    Q_OBJECT

public:
    CabManClient(QWidget *parent = Q_NULLPTR);

private:
    Ui::login_window ui;
    main_window* main_menu;
    
private slots:
    void on_ping_button_clicked();
    void on_login_button_clicked();
};