#include "admin_gestion_usuarios.h"
#include "ui_admin_gestion_usuarios.h"
#include "administrador/admin_tarjeta_usuario.h"
#include "administrador/admin_crear_usuario.h"
#include "admin_modificar_usuario.h"

#include "QMessageBox"
#include "QDebug"
#include "QSqlQuery"
#include <QPushButton>

admin_gestion_usuarios::admin_gestion_usuarios(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_gestion_usuarios)
{
    ui->setupUi(this);

    conexionBD();
    auxTipoUsuario = "todo";
    actualizarCatalogo(auxTipoUsuario);
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

void admin_gestion_usuarios::actualizarCatalogo(QString tipoUsuario)
{
    QSqlQuery infoUsuarios(mDatabase);
    QString query_usuario = "SELECT * FROM `usuario` INNER JOIN tipo ON usuario.Tipo_id_tipo = tipo.id_tipo";

    if(tipoUsuario != "todo" ){
        if (tipoUsuario == "administrador;"){
            query_usuario += " where id_tipo = 1;";
        } else if (tipoUsuario == "mesero"){
            query_usuario += " where id_tipo = 2;";
        } else if (tipoUsuario == "cocinero"){
            query_usuario += " where id_tipo = 3;";
        } else if (tipoUsuario == "barista"){
            query_usuario += " where id_tipo = 4;";
        } else if (tipoUsuario == "almacenista"){
            query_usuario += " where id_tipo = 4;";
        }
    }

    infoUsuarios.prepare(query_usuario);
    infoUsuarios.exec();
    limiparCatalogo();

    int i = 0;
    int row = 0;
    int col = 0;

    QString id;
    while (infoUsuarios.next())
    {
        id = infoUsuarios.value("clave").toString();
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

    userSideBar(id);
}

void admin_gestion_usuarios::clicked_button(QPushButton *boton)
{
    QString styleOld = "*{ border: none; color: #A6A9A5; } :hover{ color: #585858; }";
    QString styleNew = "*{ border: none; color: #A6A9A5; border-bottom: 3px solid #46B04A; } :hover{ color: #585858; }";
    ui->btnTodo->setStyleSheet(styleOld);
    ui->btnAdministrador->setStyleSheet(styleOld);
    ui->btnMeseros->setStyleSheet(styleOld);
    ui->btnCocinero->setStyleSheet(styleOld);
    ui->btnBarista->setStyleSheet(styleOld);
    ui->btnAlmacenista->setStyleSheet(styleOld);

    boton->setStyleSheet(styleNew);
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

void admin_gestion_usuarios::userSideBar(QString claveUsuario)
{
    // obtengo la clave del usuario
    this->claveUsuario = claveUsuario;

    QSqlQuery infoUsuario(mDatabase);
    infoUsuario.prepare("SELECT * FROM `usuario` INNER JOIN tipo ON usuario.Tipo_id_tipo = tipo.id_tipo WHERE usuario.clave = "+claveUsuario+"");
    infoUsuario.exec();

    infoUsuario.next();
    QString clave = infoUsuario.value("clave").toString();
    QString paterno = infoUsuario.value("apellido_paterno").toString();
    QString materno = infoUsuario.value("apellido_materno").toString();
    QString nombre = infoUsuario.value("nombre").toString();
    QString tipo = infoUsuario.value("nombre_tipo").toString();
    QString estado = infoUsuario.value("estado").toString();

    ui->nombreUsuario->setText(nombre + " " + paterno + " " + materno);
    ui->tipoUsuario->setText("Puesto: " + tipo);
    ui->claveUsuario->setText("Clave Usuario: " + clave);
    ui->lb_estadoUsuario->setText(estado);
    if(estado == "ACTIVO")
        ui->lb_estadoUsuario->setStyleSheet("color: #46B04A;");
    else
        ui->lb_estadoUsuario->setStyleSheet("color: #C56E68;");
}

void admin_gestion_usuarios::on_btnCrearUsuario_clicked()
{
    admin_crear_usuario crearUsuario;
    crearUsuario.exec();
    actualizarCatalogo(auxTipoUsuario);
}

void admin_gestion_usuarios::on_btnEditarUsuario_clicked()
{
    QSqlQuery infoUsuario(mDatabase);
    QString query_infoUsuario = "SELECT * FROM `usuario` "
                                " INNER JOIN tipo ON usuario.Tipo_id_tipo = tipo.id_tipo "
                                " WHERE usuario.clave = " + this->claveUsuario + ";";
    infoUsuario.prepare(query_infoUsuario);
    infoUsuario.exec();
    infoUsuario.next();

    QString clave   = infoUsuario.value("clave").toString();
    QString paterno = infoUsuario.value("apellido_paterno").toString();
    QString materno = infoUsuario.value("apellido_materno").toString();
    QString nombre  = infoUsuario.value("nombre").toString();
    QString tipo    = infoUsuario.value("nombre_tipo").toString();
    QString estado  = infoUsuario.value("estado").toString();

    admin_modificar_usuario modificarUsuario(clave, nombre, paterno, materno, tipo, estado, this);
    modificarUsuario.exec();
    userSideBar(clave);
    actualizarCatalogo(auxTipoUsuario);
}

void admin_gestion_usuarios::on_btnMeseros_clicked()
{
    auxTipoUsuario = "mesero";
    clicked_button(ui->btnMeseros);
    actualizarCatalogo(auxTipoUsuario);
}

void admin_gestion_usuarios::on_btnTodo_clicked()
{
    auxTipoUsuario = "todo";
    clicked_button(ui->btnTodo);
    actualizarCatalogo(auxTipoUsuario);
}

void admin_gestion_usuarios::on_btnAlmacenista_clicked()
{
    auxTipoUsuario = "almacenista";
    clicked_button(ui->btnAlmacenista);
    actualizarCatalogo(auxTipoUsuario);
}

void admin_gestion_usuarios::on_btnCocinero_clicked()
{
    auxTipoUsuario = "cocinero";
    clicked_button(ui->btnCocinero);
    actualizarCatalogo(auxTipoUsuario);
}

void admin_gestion_usuarios::on_btnAdministrador_clicked()
{
    auxTipoUsuario = "administrador";
    clicked_button(ui->btnAdministrador);
    actualizarCatalogo(auxTipoUsuario);
}

void admin_gestion_usuarios::on_btnBarista_clicked()
{
    auxTipoUsuario = "barista";
    clicked_button(ui->btnBarista);
    actualizarCatalogo(auxTipoUsuario);
}
