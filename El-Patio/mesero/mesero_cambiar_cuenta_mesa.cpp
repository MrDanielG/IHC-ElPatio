#include "mesero_cambiar_cuenta_mesa.h"
#include "ui_mesero_cambiar_cuenta_mesa.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>

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
    QString MesaCB = ui->cb_Mesas1->currentText();
    QString script = "select estado from mesa where numero_mesa = " + MesaCB;
    //qDebug() << script;
    QSqlQuery query(QSqlDatabase::database("Connection"));
    query.prepare(script);
    query.exec();
    query.next();
    if(query.value(0) == "Libre"){
        if(QMessageBox::question(this, tr("Mesa libre"), tr("La mesa seleccionada se marcará como ocupada, ¿Desea continuar?"))==QMessageBox::Yes){
            //qDebug() << "Poner a ocupada la mesa " + MesaCB;
            script = "UPDATE mesa set estado = 'Ocupada' where numero_mesa = " + MesaCB;
            transferir();
        }
        else QMessageBox::information(this, tr("Cancelado"), tr("Se ha cancelado la transferencia."));
    }
    else{ //Mesa ocupada
        QString Mensaje = "La cuenta completa será transferida "
                          "de la mesa "+ QString::number(Mesa) + " a la " + MesaCB + "\n¿Desea continuar?";
        if(QMessageBox::question(this, tr("Confirmar transferencia"), Mensaje) == QMessageBox::Yes){
            qDebug() << "Que sí, dice.";
            transferir();
        }
        else QMessageBox::information(this, tr("Cancelado"), tr("Se ha cancelado la transferencia."));
    }
}

void mesero_cambiar_cuenta_mesa::transferir()
{
    QString s = "select id_comanda from comanda where Mesa_numero_mesa = " + ui->cb_Mesas1->currentText();
    QSqlQuery q(QSqlDatabase::database("Connection"));
    QString idComandaNueva;
    q.prepare(s);
    q.exec();
    if(q.next()){
        idComandaNueva = q.value(0).toString();
    }
    else{
        QString qs = "insert into comanda(hora_apertura, numero_personas, Usuario_clave, Mesa_numero_mesa, comentario)"
            "values ('"+ QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "', 2, 100, "+ ui->cb_Mesas1->currentText() + ", 'Transferida')";
        //qDebug() << qs;
        q.prepare(qs);
        q.exec();
        q.finish();
        q.prepare(s);
        q.exec();
        q.next();
        idComandaNueva = q.value(0).toString();
    }
    QString MesaCB = ui->cb_Mesas1->currentText();
    QString script = "select id_comanda from comanda where Mesa_numero_mesa = " + QString::number(Mesa) + " and estado = 'Abierta'";
    //qDebug() << script;
    QSqlQuery query(QSqlDatabase::database("Connection")), query2(QSqlDatabase::database("Connection"));
    query.prepare(script);
    query.exec();
    if(query.next()){
        QString idComanda = query.value(0).toString();
        //qDebug() << idComanda;
        script = "UPDATE comanda set estado = 'Transferida' where id_comanda = " + idComanda;
        QString script2 = "UPDATE mesa set estado = 'Ocupada' where numero_mesa = " + QString::number(Mesa);
        query.finish();
        query.prepare(script);
        if (query.exec()){
            query.prepare(script2);
            if(query.exec()){
                script = "select id_Pedido from pedido where Comanda_id_comanda = " + idComanda;
                query.prepare(script);
                if(query.exec()){
                    while (query.next()){
                        script2 = "UPDATE pedido set Comanda_id_comanda = " + idComandaNueva + " where id_Pedido = " + query.value(0).toString();
                        query2.prepare(script2);
                        query2.exec();
                    }
                    QMessageBox::information(this, tr("Éxito"), tr("La transferencia de cuenta fue realizada con éxito"));
                }
            }
        }
    }
    else qDebug() << "alv";
}
