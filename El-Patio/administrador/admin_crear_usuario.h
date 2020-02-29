#ifndef ADMIN_CREAR_USUARIO_H
#define ADMIN_CREAR_USUARIO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class admin_crear_usuario;
}

class admin_crear_usuario : public QDialog
{
    Q_OBJECT

public:
    explicit admin_crear_usuario(QWidget *parent = nullptr);
    void validarInputs();
    void conexionBD();
    ~admin_crear_usuario();

private slots:
    void on_btnCancelar_clicked();

    void on_btnCrearUsuario_clicked();

    void on_nombre_textChanged(const QString &arg1);

    void on_paterno_textChanged(const QString &arg1);

    void on_materno_textChanged(const QString &arg1);

private:
    Ui::admin_crear_usuario *ui;
    QSqlDatabase mDatabase;
};

#endif // ADMIN_CREAR_USUARIO_H
