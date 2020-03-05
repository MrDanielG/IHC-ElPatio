#include "mesero_agregar_extra.h"
#include "ui_mesero_agregar_extra.h"
#include "QDebug"
#include "QSqlQuery"
mesero_agregar_extra::mesero_agregar_extra(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_agregar_extra)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: AGREGAR EXTRA";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: AGREGAR EXTRA";
    }

//    ui->comboBox_2->hide();
//    ui->btnMasExtra_2->hide();
//    ui->comboBox_3->hide();

//    llenarComboBox();
}

mesero_agregar_extra::~mesero_agregar_extra()
{
    delete ui;
}

//void mesero_agregar_extra::llenarComboBox()
//{
//    QSqlQuery queryComplementos(mDatabase);
//    queryComplementos.prepare("SELECT * FROM PLATILLO"); //Query provisional
//    queryComplementos.exec();

//    int i = 0;
//    while(queryComplementos.next()){
//        i++;
//        QString nombreExtra = queryComplementos.value(0).toString();
//        ui->comboBox->insertItem(i, nombreExtra);
//        ui->comboBox_2->insertItem(i, nombreExtra);
//        ui->comboBox_3->insertItem(i, nombreExtra);
//    }
//}

//void mesero_agregar_extra::on_btnMasExtra_clicked()
//{
//    ui->comboBox_2->show();
//    ui->btnMasExtra_2->show();
//}

//void mesero_agregar_extra::on_btnMasExtra_2_clicked()
//{
//    ui->comboBox_3->show();
//}
