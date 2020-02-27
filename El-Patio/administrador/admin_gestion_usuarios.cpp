#include "admin_gestion_usuarios.h"
#include "ui_admin_gestion_usuarios.h"
#include "administrador/admin_tarjeta_usuario.h"
#include "administrador/admin_crear_usuario.h"
#include "QMessageBox"
#include "QDebug"
#include "QSqlQuery"
admin_gestion_usuarios::admin_gestion_usuarios(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_gestion_usuarios)
{
    ui->setupUi(this);

    conexionBD();
    actualizarCatalogo();
}

admin_gestion_usuarios::~admin_gestion_usuarios()
{
    delete ui;
}

void admin_gestion_usuarios::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: GESTION USUARIOS";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: GESTION USUARIOS";
    }
}

void admin_gestion_usuarios::actualizarCatalogo()
{
    QSqlQuery infoUsuarios(mDatabase);
    infoUsuarios.prepare("SELECT * FROM `usuario` INNER JOIN tipo ON usuario.Tipo_id_tipo = tipo.id_tipo");
    infoUsuarios.exec();
    limiparCatalogo();

    int i = 0;
    int row = 0;
    int col = 0;

    while (infoUsuarios.next())
    {
        QString id = infoUsuarios.value("clave").toString();
        QString paterno = infoUsuarios.value("apellido_paterno").toString();
        QString materno = infoUsuarios.value("apellido_materno").toString();
        QString nombre = infoUsuarios.value("nombre").toString();
        QString tipo = infoUsuarios.value("nombre_tipo").toString();

        //El numero de columnas en las que se dividira el grid
        row = i / 2;
        col = i % 2;

        admin_tarjeta_usuario *tarjeta =
                new admin_tarjeta_usuario(id, nombre, paterno, materno, tipo, this);
        i++;
        ui->gridUsuarios->addWidget(tarjeta, row, col);
    }
}

void admin_gestion_usuarios::limiparCatalogo()
{
    while (QLayoutItem *item = ui->gridUsuarios->takeAt(0))
    {
        Q_ASSERT(!item->layout());
        delete item->widget();
        delete item;
    }
}

void admin_gestion_usuarios::on_btnCrearUsuario_clicked()
{
    admin_crear_usuario crearUsuario;
    crearUsuario.exec();
    actualizarCatalogo();
}
