#include "mesero_cambiar_cuenta_mesa.h"
#include "ui_mesero_cambiar_cuenta_mesa.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

mesero_cambiar_cuenta_mesa::mesero_cambiar_cuenta_mesa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mesero_cambiar_cuenta_mesa)
{
    ui->setupUi(this);

    ui->CodigoADM->setEchoMode(QLineEdit::Password);
    QString script = "select numero_mesa from mesa";
    QSqlQuery query(QSqlDatabase::database("Connection"));
    query.prepare(script);
    query.exec();
    while(query.next())
    {
        QString valor = query.value(0).toString();
        ui->cb_Mesas1->addItem(valor);

    }
}

void mesero_cambiar_cuenta_mesa::setNumeroMesa(int NMesa)
{
    Mesa = NMesa;
}

mesero_cambiar_cuenta_mesa::~mesero_cambiar_cuenta_mesa()
{
    delete ui;
}

void mesero_cambiar_cuenta_mesa::on_btnSecundaio_clicked()
{
    close();
}

void mesero_cambiar_cuenta_mesa::on_btnPrimario_clicked()
{
    QString script = "select estado from mesa where numero_mesa = " + ui->cb_Mesas1->currentText();
    qDebug() << script;
    QSqlQuery query(QSqlDatabase::database("Connection"));
    query.prepare(script);
    query.exec();
    query.next();
    if(query.value(0) != "Ocupada"){
        if(QMessageBox::question(this, tr("Mesa libre"), tr("La mesa seleccionada se marcará como ocupada, ¿Desea continuar?"))==QMessageBox::Yes){

        }
    }
}

