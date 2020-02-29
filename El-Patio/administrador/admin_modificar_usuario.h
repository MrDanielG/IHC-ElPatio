#ifndef ADMIN_MODIFICAR_USUARIO_H
#define ADMIN_MODIFICAR_USUARIO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

class admin_gestion_usuarios;

namespace Ui {
class admin_modificar_usuario;
}

class admin_modificar_usuario : public QDialog
{
    Q_OBJECT

public:
    explicit admin_modificar_usuario(QWidget *parent = nullptr);
    explicit admin_modificar_usuario(QString id, QString nombre, QString paterno,
                                     QString materno, QString tipo, QString estado,
                                     QWidget *parent = nullptr);
    void conexionBD();
    ~admin_modificar_usuario();
    void estadoUsuario(QString estado);

private slots:
    void on_btnCambiarEstado_clicked();

    void on_btnCancelar_clicked();

    void on_btnGuardarCambios_clicked();

private:
    Ui::admin_modificar_usuario *ui;
    QSqlDatabase mDatabase;
    admin_gestion_usuarios *padre;

    //clave de usuario
    QString clave;
};

#endif // ADMIN_MODIFICAR_USUARIO_H
