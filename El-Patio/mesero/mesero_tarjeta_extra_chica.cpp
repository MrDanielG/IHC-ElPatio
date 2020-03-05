#include "mesero_tarjeta_extra_chica.h"
#include "ui_mesero_tarjeta_extra_chica.h"

mesero_tarjeta_extra_chica::mesero_tarjeta_extra_chica(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_extra_chica)
{
    ui->setupUi(this);
}

mesero_tarjeta_extra_chica::~mesero_tarjeta_extra_chica()
{
    delete ui;
}
