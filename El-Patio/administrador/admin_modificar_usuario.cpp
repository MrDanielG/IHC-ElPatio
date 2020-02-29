#include "admin_modificar_usuario.h"
#include "ui_admin_modificar_usuario.h"
#include "admin_gestion_usuarios.h"

#include <QDebug>
#include <QMessageBox>

admin_modificar_usuario::admin_modificar_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_modificar_usuario)
{
    ui->setupUi(this);
//    ui->btnGuardarCambios->setDisabled(true);
    conexionBD();
}

admin_modificar_usuario::admin_modificar_usuario(QString id, QString nombre, QString paterno,
                                                 QString materno, QString tipo, QString estado,
                                                 QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_modificar_usuario)
{
    ui->setupUi(this);
//    ui->btnGuardarCambios->setDisabled(true);
    conexionBD();
    this->clave = id;

    ui->claveUsuario->setValue(id.toInt());
    ui->nombre->setText(nombre);
    ui->paterno->setText(paterno);
    ui->materno->setText(materno);
    if (tipo == "Administrador") {
        ui->rbAdministrador->setAcceptDrops(true);
    } else if (tipo == "Mesero") {
        ui->rbMesero->setChecked(true);
    } else if (tipo == "Cocinero") {
        ui->rbCocinero->setAcceptDrops(true);
    } else if (tipo == "Barista") {
        ui->rbBarista->setAcceptDrops(true);
    } else if (tipo == "Almacenista") {
        ui->rbAlmacenista->setAcceptDrops(true);
    }
    estadoUsuario(estado);
}


void admin_modificar_usuario::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: MODIFICAR USUARIO";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: MODIFICAR USUARIO";
    }
}

admin_modificar_usuario::~admin_modificar_usuario()
{
    delete ui;
}

void admin_modificar_usuario::estadoUsuario(QString estado)
{
    ui->lb_estado->setText(estado);
    if (estado == "ACTIVO") {
        QString estiloButton = "*{ color: #C56E68; border-radius: 10px; background-color: #ffffff; border: 1px solid #C56E68; border: none; padding: 5px; }";
        QString estiloLabel = "color: #46B04A;";
        ui->lb_estado->setStyleSheet(estiloLabel);
        ui->btnCambiarEstado->setStyleSheet(estiloButton);
        ui->btnCambiarEstado->setText("Cambiar a Inactivo");
    } else {
        QString estiloButton = "*{ color: white; border-radius: 10px; background-color: #46B04A; border: none; padding: 5px; }";
        QString estiloLabel = "color: #C56E68;";
        ui->lb_estado->setStyleSheet(estiloLabel);
        ui->btnCambiarEstado->setStyleSheet(estiloButton);
        ui->btnCambiarEstado->setText("Cambiar a Activo");
    }
}

void admin_modificar_usuario::on_btnCambiarEstado_clicked()
{
    QMessageBox::StandardButton respuesta = QMessageBox::question(this, tr("Estado Usario"),
                                   tr("¿Seguro quiere cambiar estado a usuario?"));

    if(respuesta == QMessageBox::Yes){

        QString estado;
        if(ui->lb_estado->text() == "ACTIVO")
            estado = "INACTIVO";
        else
            estado = "ACTIVO";

        QSqlQuery query_CamEstado(mDatabase);
        query_CamEstado.prepare("UPDATE usuario set estado = '"+estado+"' where (clave = "+this->clave+");");
        if(query_CamEstado.exec())
            QMessageBox::information(this, tr("Actualización Usuario"), tr("Estado del usuario cambiado exitosamente"));
        else
            QMessageBox::information(this, tr("Error"), tr("Error al cambiar estado"));
        this->close();
    }
}

void admin_modificar_usuario::on_btnCancelar_clicked()
{
    QMessageBox::StandardButton respuesta = QMessageBox::question(this, tr("Salir"),
                                   tr("¿Seguro que quiere cancelar la modificación del usuario?"));

    if(respuesta == QMessageBox::Yes)
        this->close();
}

void admin_modificar_usuario::on_btnGuardarCambios_clicked()
{
    QMessageBox::StandardButton respuesta = QMessageBox::question(this, tr("Datos Usario"),
                                   tr("¿Seguro quiere actualizar los datos del usuario?"));

    if(respuesta == QMessageBox::Yes){
        QString nombre = ui->nombre->text();
        QString paterno = ui->paterno->text();
        QString materno = ui->materno->text();
        QString clave = QString::number( ui->claveUsuario->value() );
        QString tipo;

        if(ui->rbAdministrador->isChecked()){
            tipo = "1"; //Equivalente a Mesero
        } else if (ui->rbMesero->isCheckable()) {
            tipo = "2";
        } else if (ui->rbCocinero->isChecked()) {
            tipo = "3"; //Equivalente a Cocinero
        } else if (ui->rbBarista->isChecked()) {
            tipo = "4"; //Equivalente a Barista
        } else if (ui->rbAlmacenista->isChecked()) {
            tipo = "5"; //Equivalente a Almacenista
        }

        QSqlQuery query_updateUsuario(mDatabase);
        query_updateUsuario.prepare("UPDATE usuario SET "
                                    "clave = "+clave+", "
                                    "apellido_paterno = '"+paterno+"', "
                                    "apellido_materno = '"+materno+"', "
                                    "nombre = '"+nombre+"', "
                                    "Tipo_id_tipo = '"+tipo+"' "
                                    "WHERE (`clave` = '"+this->clave+"');");
        if(query_updateUsuario.exec())
            QMessageBox::information(this, tr("Actualización usuario"), tr("Actualización de los datos completada exitosamente."));
        else
            QMessageBox::information(this, tr("Error"), tr("Error, no a compleado la actualización correctamente."));
        this->close();
    }
}
