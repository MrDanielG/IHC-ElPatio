#include "mesero_tarjeta_extra_chica.h"
#include "ui_mesero_tarjeta_extra_chica.h"
#include "mesero/mesero_editar_platillo.h"

mesero_tarjeta_extra_chica::mesero_tarjeta_extra_chica(mesero_editar_platillo *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_extra_chica)
{
    ui->setupUi(this);

    this->padre = parent;
}

mesero_tarjeta_extra_chica::~mesero_tarjeta_extra_chica()
{
    delete ui;
}
