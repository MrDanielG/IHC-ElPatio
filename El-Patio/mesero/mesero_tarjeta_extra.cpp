#include "mesero_tarjeta_extra.h"
#include "ui_mesero_tarjeta_extra.h"

mesero_tarjeta_extra::mesero_tarjeta_extra(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_extra)
{
    ui->setupUi(this);
}

mesero_tarjeta_extra::~mesero_tarjeta_extra()
{
    delete ui;
}
