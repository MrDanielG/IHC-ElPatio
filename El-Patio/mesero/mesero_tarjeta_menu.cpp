#include "mesero_tarjeta_menu.h"
#include "ui_mesero_tarjeta_menu.h"

mesero_tarjeta_menu::mesero_tarjeta_menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_menu)
{
    ui->setupUi(this);
}

mesero_tarjeta_menu::~mesero_tarjeta_menu()
{
    delete ui;
}
