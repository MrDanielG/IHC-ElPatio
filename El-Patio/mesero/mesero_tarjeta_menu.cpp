#include "mesero_tarjeta_menu.h"
#include "ui_mesero_tarjeta_menu.h"
#include "QPixmap"
#include "QMessageBox"
#include "QDebug"
#include "mesero/mesero_menu_comandas.h"
#include "models/platillo.h"
mesero_tarjeta_menu::mesero_tarjeta_menu(QString id, QString nombrePlatillo, QString precioPlatillo, QString foto, mesero_menu_comandas *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_menu)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug() << "ERROR en TARJETA MENU";
    }else{
        qDebug() << "base de datos sigue conectada en TARJETA MENU";
    }

    this->id = id;
    this->nombrePlatillo = nombrePlatillo;
    this->precioPlatillo = precioPlatillo;
    this->foto = foto;
    this->padre = parent;

    llenarTarjeta();
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
    ui->cantPlatillo->setText(QString::number(this->cantidad));
}

void mesero_tarjeta_menu::on_btnMasPlatillo_clicked()
{
    this->cantidad++;
    llenarTarjeta();

    Platillo plato(this->id, this->nombrePlatillo, this->precioPlatillo, this->foto, this->cantidad);

    this->padre->agregarSideBar(plato);
}
