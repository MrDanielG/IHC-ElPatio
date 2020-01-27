#include "mesero_tarjeta_chica.h"
#include "ui_mesero_tarjeta_chica.h"

mesero_tarjeta_chica::mesero_tarjeta_chica(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_chica)
{
    ui->setupUi(this);
}

mesero_tarjeta_chica::~mesero_tarjeta_chica()
{
    delete ui;
}
