#include "mesero_tarjeta_menu.h"
#include "ui_mesero_tarjeta_menu.h"

mesero_tarjeta_menu::mesero_tarjeta_menu(QString id, QString nombrePlatillo, QString precioPlatillo, QString foto, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_menu)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
}

mesero_tarjeta_menu::~mesero_tarjeta_menu()
{
    delete ui;
}

void mesero_tarjeta_menu::llenarTarjeta()
{
    QPixmap img(this->foto);
    ui->nombrePlatillo->setText(this->nombrePlatillo);
    ui->precioPlatillo->setText(this->precioPlatillo);
    ui->imgPlatillo->setPixmap(img);
}
