#include "agregar_propina_cuenta.h"
#include "ui_agregar_propina_cuenta.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QDateTime>

agregar_propina_cuenta::agregar_propina_cuenta(QStringList totales, QString idC, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::agregar_propina_cuenta)
{
    ui->setupUi(this);
    ui->OtroSelected->setHidden(true);
    setWindowTitle("Agregar propina");
    ui->btnPrimario_2->setDisabled(true);
    mDatabase = QSqlDatabase::database("Connection");
    while (!totales.isEmpty()) {
        totalesDiv.append(totales.first());
        qDebug() << "Totales div= "<< totalesDiv.last();
        totales.pop_front();
    }
    idComanda = idC;
}

agregar_propina_cuenta::~agregar_propina_cuenta()
{
    delete ui;
}

void agregar_propina_cuenta::on_otroMonto_clicked()
{
    ui->OtroSelected->setHidden(false);
    ui->btnPrimario_2->setDisabled(true);
}

void agregar_propina_cuenta::on_diezPorciento_clicked()
{
    ui->OtroSelected->setHidden(true);
    ui->btnPrimario_2->setDisabled(false);
    ui->montoPropina->setText("");
    propina = 0.1;
}

void agregar_propina_cuenta::on_quincePorciento_clicked()
{
    ui->OtroSelected->setHidden(true);
    ui->btnPrimario_2->setDisabled(false);
    ui->montoPropina->setText("");
    propina = 0.15;
}

void agregar_propina_cuenta::on_veintePorciento_clicked()
{
    ui->OtroSelected->setHidden(true);
    ui->btnPrimario_2->setDisabled(false);
    ui->montoPropina->setText("");
    propina = 0.2;
}

void agregar_propina_cuenta::on_btnSecundaio_2_clicked()
{
    ui->montoPropina->setText("");
    close();
}

void agregar_propina_cuenta::on_btnPrimario_2_clicked()
{
    if(ui->otroMonto->isChecked() && ui->montoPropina->text().isEmpty()){
        QMessageBox::warning(this, tr("Error"), tr("Por favor, ingrese un monto en pesos para la propina"));
    }
    else{
        qDebug() << propina;
        //TODO: Manejo de propinas, ¿Se guarda en la base? Revisar.
        QString montoPropina = calculaPropina();
        QSqlQuery query(mDatabase);
        QString fecha = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        while (!totalesDiv.isEmpty()) {
            QString total = totalesDiv.first();
            //qDebug() << "total " << total;

            //TODO: Agregar idComanda aquí
            QString script = "INSERT INTO `ticket`(`fecha`, `iva`, `metodo`, `total`, `Comanda_id_comanda`) "
                             "VALUE ('" + fecha +"', 0.16, 'Efectivo', "+ total + ", "+ idComanda +")";
            query.prepare(script);
            //qDebug() << "Script: " << script;
            if(query.exec()){
                totalesDiv.pop_front();
                QMessageBox::information(this, tr("Éxito"), tr("El pago se ha registrado correctamente"));
            }
            else{
                //qDebug() << "ñoooo";
            }
        }
        close();
    }
}

void agregar_propina_cuenta::on_montoPropina_textChanged(const QString &arg1)
{
    ui->btnPrimario_2->setDisabled(false);
    propina = arg1.toDouble();
}

QString agregar_propina_cuenta::calculaPropina()
{
    return "he";
}

void agregar_propina_cuenta::on_sinPropina_clicked()
{
    ui->OtroSelected->setHidden(true);
    ui->btnPrimario_2->setDisabled(false);
    ui->montoPropina->setText("");
    propina = 0;
}
