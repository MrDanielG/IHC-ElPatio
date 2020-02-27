#include "admin_crear_usuario.h"
#include "ui_admin_crear_usuario.h"
#include "QMessageBox"
#include "QDebug"
admin_crear_usuario::admin_crear_usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_crear_usuario)
{
    ui->setupUi(this);
    conexionBD();
    ui->btnCrearUsuario->setDisabled(true);
}

void admin_crear_usuario::validarInputs()
{
    if(ui->nombre->text().isEmpty() ||
       ui->paterno->text().isEmpty() ||
       ui->materno->text().isEmpty() ){

        ui->btnCrearUsuario->setDisabled(true);
    } else {
        ui->btnCrearUsuario->setDisabled(false);
    }
}

void admin_crear_usuario::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos, esto es: CREAR USUARIO";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta, esto es: CREAR USUARIO";
    }
}

admin_crear_usuario::~admin_crear_usuario()
{
    delete ui;
}

void admin_crear_usuario::on_btnCancelar_clicked()
{
    this->close();
}

void admin_crear_usuario::on_btnCrearUsuario_clicked()
{
    QString nombre = ui->nombre->text();
    QString paterno = ui->paterno->text();
    QString materno = ui->materno->text();
    QString clave = QString::number( ui->claveUsuario->value() );
    QString tipo;

    if(ui->rbMesero->isChecked()){
        tipo = "2"; //Equivalente a Mesero
    } else if (ui->rbCocinero->isChecked()) {
        tipo = "3"; //Equivalente a Cocinero
    } else if (ui->rbBarista->isChecked()) {
        tipo = "4"; //Equivalente a Barista
    } else if (ui->rbAlmacenista->isChecked()) {
        tipo = "5"; //Equivalente a Almacenista
    }

    if(QMessageBox::question(this, tr("Crear Usuario"),
                             tr("¿Está seguro que desea crear un Usuario con estos Datos?"))==QMessageBox::Yes){

        QSqlQuery crearUsuario(mDatabase);
        crearUsuario.prepare("INSERT INTO `usuario`(`clave`,`apellido_paterno`, `apellido_materno`, `nombre`, `Tipo_id_tipo`) "
                             "VALUES ("+clave+",'"+paterno+"','"+materno+"','"+nombre+"',"+tipo+")");

        if(crearUsuario.exec()){
            QMessageBox::information(this, tr("Crear Usuario "), tr("Usuario Creado Correctamente"));
        } else {
            QMessageBox::information(this, tr("Error "), tr("Error al crear Usuario"));
        }

        this->close();
    } else {
         //QMessageBox::information(this, tr("Crear Usuario Cancelado"), tr("Nuevo Usuario Cancelado"));
         this->close();
    }
}

void admin_crear_usuario::on_nombre_textChanged(const QString &arg1)
{
    validarInputs();
}

void admin_crear_usuario::on_paterno_textChanged(const QString &arg1)
{
    validarInputs();
}

void admin_crear_usuario::on_materno_textChanged(const QString &arg1)
{
    validarInputs();
}
