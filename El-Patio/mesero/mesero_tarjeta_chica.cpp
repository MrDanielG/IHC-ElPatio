#include "mesero_tarjeta_chica.h"
#include "ui_mesero_tarjeta_chica.h"
#include "mesero/mesero_menu_comandas.h"
#include "mesero/mesero_editar_platillo.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

mesero_tarjeta_chica::mesero_tarjeta_chica(QString id, QString nombrePlatillo, QString precioPlatillo, QString foto, int cantidad, mesero_menu_comandas *parent) :
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_chica)
{
    ui->setupUi(this);

    this->id = id;
    this->nombrePlatillo = nombrePlatillo;
    this->precioPlatillo = precioPlatillo;
    this->foto = foto;
    this->cantidad = cantidad;
    this->padre = parent;
    llenarTarjeta();
}

mesero_tarjeta_chica::mesero_tarjeta_chica(int id_platillo, QWidget *parent):
    QWidget(parent),
    ui(new Ui::mesero_tarjeta_chica)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
       if(!mDatabase.isOpen()){
           qDebug() << "ERROR, tarjeta platillo";
       }else {
           qDebug() << "conexion exitosa desde tarjeta_platillo";
       }

    this->id = QString::number(id_platillo);

    QSqlQuery datos_platillo(mDatabase);
    QString query_datos_platillo = "select * from platillo where id_platillo = " + this->id + ";";

    datos_platillo.exec(query_datos_platillo);
    datos_platillo.next();

    this->nombrePlatillo = datos_platillo.record().value("nombre").toString();
    this->precioPlatillo = datos_platillo.record().value("precio").toString();
    this->foto = datos_platillo.record().value("foto").toString();
    this->cantidad = 1;

    llenarTarjeta();
}

mesero_tarjeta_chica::~mesero_tarjeta_chica()
{
    delete ui;
}

void mesero_tarjeta_chica::llenarTarjeta()
{
    ui->nombrePlatillo->setText(this->nombrePlatillo);
    ui->precioPlatillo->setText("$ " + this->precioPlatillo);
    ui->cantidad->setText(QString::number(this->cantidad));
}

float mesero_tarjeta_chica::get_precio()
{
    return this->precioPlatillo.toFloat();
}

void mesero_tarjeta_chica::on_btnMenosPlatillo_clicked()
{
    this->cantidad--;
    if(cantidad == 0){
        ui->btnMenosPlatillo->setEnabled(false);
    }
    llenarTarjeta();

    Platillo plato(this->id, this->nombrePlatillo, this->precioPlatillo, this->foto, this->cantidad);

    this->padre->actualizarSideBar(plato, 0);
}

void mesero_tarjeta_chica::on_btnMasPlatillo_clicked()
{
    this->cantidad++;
    if(cantidad>0){
        ui->btnMenosPlatillo->setEnabled(true);
    }
    llenarTarjeta();

    Platillo plato(this->id, this->nombrePlatillo, this->precioPlatillo, this->foto, this->cantidad);

    this->padre->actualizarSideBar(plato, 1);
}

void mesero_tarjeta_chica::on_btnEditPlatillo_clicked()
{
    mesero_editar_platillo editarPlatillo;
    editarPlatillo.exec();
    this->listaExtras = editarPlatillo.getExtras();

    //Agregar a SideBar los Extras
    qDebug()<<"Cerrar Ventana";

    for (int var = 0; var < this->listaExtras.size(); ++var) {
        qDebug()<<this->listaExtras[var].nombre;
        qDebug()<<this->listaExtras[var].cantidad;
    }
}
