#include "mesero_menu_comandas.h"
#include "ui_mesero_menu_comandas.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlQuery"

mesero_menu_comandas::mesero_menu_comandas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mesero_menu_comandas)
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

    QSqlQuery infoPlatillo(mDatabase);
    infoPlatillo.prepare("SELECT * from persona INNER JOIN usuario ON persona.id_usuario = usuario.id_usuario");
    infoPlatillo.exec();
}

mesero_menu_comandas::~mesero_menu_comandas()
{
    delete ui;
}
