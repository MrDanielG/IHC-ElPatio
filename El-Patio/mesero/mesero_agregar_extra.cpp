#include "mesero_agregar_extra.h"
#include "ui_mesero_agregar_extra.h"
#include "QDebug"

mesero_agregar_extra::mesero_agregar_extra(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_agregar_extra)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: MENU COMANDAS";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: MENU COMANDAS";
    }

    ui->comboBox_2->hide();
    ui->btnMasExtra_2->hide();
    ui->comboBox_3->hide();
}

mesero_agregar_extra::~mesero_agregar_extra()
{
    delete ui;
}

void mesero_agregar_extra::on_btnMasExtra_clicked()
{
    ui->comboBox_2->show();
    ui->btnMasExtra_2->show();
}

void mesero_agregar_extra::on_btnMasExtra_2_clicked()
{
    ui->comboBox_3->show();
}

void mesero_agregar_extra::on_btnMandarCocina_2_clicked()
{

}
