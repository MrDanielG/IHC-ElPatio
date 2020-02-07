#include "almacenista_crear_insumo.h"
#include "ui_almacenista_crear_insumo.h"
#include "QMessageBox"
#include "QDebug"
#include "QDate"
#include "QDateTime"

almacenista_crear_insumo::almacenista_crear_insumo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::almacenista_crear_insumo)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: CREAR INSUMO";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: CREAR INSUMO";
    }

    ui->titulo_4->hide();
    ui->spinBoxCaducar->hide();
    ui->btnNoPerecedero->setChecked(true);
}

almacenista_crear_insumo::~almacenista_crear_insumo()
{
    delete ui;
}

void almacenista_crear_insumo::on_btnSecundaio_clicked()
{
    this->close();
}

void almacenista_crear_insumo::on_btnPrimario_clicked()
{
    QMessageBox msgBox(QMessageBox::Question,"Agregar","¿Desea crear éste Insumo?",QMessageBox::Yes|QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,"Sí");
    msgBox.setButtonText(QMessageBox::No,"No");

    if(msgBox.exec()==QMessageBox::Yes){

        QString nombre = ui->nombreInsumo->text();
        QString presentacion = ui->tipoPresentacion->text();
        QString precio = QString::number(ui->doubleSpinBox->value());
        QString diasCaducidad = QString::number(ui->spinBoxCaducar->value());

        QSqlQuery query(mDatabase);

        if(ui->btnPerecedero->isChecked()){ //Es perecedero
            query.exec("INSERT INTO `insumo`(`nombre`, `precio_compra`, `existencias`, `presentacion`) VALUES ('"+nombre+"',"+precio+",0,'"+presentacion+"')");

            QSqlQuery queryID(mDatabase);
            queryID.exec("SELECT `id_insumo` FROM `insumo` WHERE `nombre` = '"+nombre+"' AND `precio_compra` = '"+precio+"' AND `presentacion` = '"+presentacion+"'");
            queryID.next();
            QString idInsumo = queryID.value(0).toString();

            QDate hoy = QDate::currentDate();
            QString hoyStr = hoy.toString("yyyy-MM-dd");
            qDebug()<<"HOY: " <<hoy;
            qDebug()<<"HOY STR: " <<hoyStr;

            QSqlQuery queryAddPerecedero(mDatabase);
            queryAddPerecedero.exec("INSERT INTO `ingrediente`(`id_insumo`, `fecha_almacenamiento`, `dias_caducidad`) VALUES ('"+idInsumo+"','"+hoyStr+"','"+diasCaducidad+"')");

        } else { //No es perecedero
            query.exec("INSERT INTO `insumo`(`nombre`, `precio_compra`, `existencias`, `presentacion`) VALUES ('"+nombre+"',"+precio+",0,'"+presentacion+"')");
        }

        QMessageBox::information(this, tr("Crear Insumo"),
                     tr("Se creo correctamente el Insumo"));
        this->close();
    } else {
        QMessageBox::information(this, tr("Crear Insumo"),
                     tr("No se creo el Insumo"));
        this->close();
    }
}

void almacenista_crear_insumo::on_btnPerecedero_clicked()
{
    ui->titulo_4->show();
    ui->spinBoxCaducar->show();
}

void almacenista_crear_insumo::on_btnNoPerecedero_clicked()
{
    ui->titulo_4->hide();
    ui->spinBoxCaducar->hide();
}
