#pragma once

#include <QtWidgets/QWidget>
#include "ui_login.h"

class CabManClient : public QWidget
{
    Q_OBJECT

public:
    CabManClient(QWidget *parent = Q_NULLPTR);

private:
    Ui::CabManClientClass ui;
private slots:
    void on_login_button_clicked();
};