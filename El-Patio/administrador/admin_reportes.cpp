#include "admin_reportes.h"
#include "ui_admin_reportes.h"

#include <QDebug>

admin_reportes::admin_reportes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_reportes)
{
    ui->setupUi(this);

    conexionBD();
    actualizarDatos();
}

void admin_reportes::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: REPORTES";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: REPORTES";
    }
}

void admin_reportes::actualizarDatos()
{
    QDate aux = QDate::currentDate();
    int dia = aux.day(), mes = aux.month()-1, anio = aux.year();
    QDate auxDate(anio, mes, dia);

    ui->de_fin->setDate(aux);
    ui->de_incio->setDate(auxDate);

}

void admin_reportes::clicked_button(QPushButton *boton)
{
    QString styleOld = "*{ border: none; color: #A6A9A5; margin-left: 10px; margin-right: 10px; } "
                       ":hover{ color: #585858;  margin-left: 10px; margin-right: 10px;  }";
    QString styleNew = "*{ border: none; color: #585858; border-bottom: 3px solid #46B04A; margin-left: 10px; margin-right: 10px; }";
    ui->btn_comandas->setStyleSheet(styleOld);
    ui->btn_transacciones->setStyleSheet(styleOld);
    ui->btn_ventas->setStyleSheet(styleOld);

    boton->setStyleSheet(styleNew);
}

admin_reportes::~admin_reportes()
{
    delete ui;
}

void admin_reportes::on_btn_ventas_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clicked_button(ui->btn_ventas);
}

void admin_reportes::on_btn_transacciones_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    clicked_button(ui->btn_transacciones);
}

void admin_reportes::on_btn_comandas_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    clicked_button(ui->btn_comandas);
}
