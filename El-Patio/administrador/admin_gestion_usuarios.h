#ifndef ADMIN_GESTION_USUARIOS_H
#define ADMIN_GESTION_USUARIOS_H

#include <QWidget>
#include <QSqlDatabase>
namespace Ui {
class admin_gestion_usuarios;
}

class admin_gestion_usuarios : public QWidget
{
    Q_OBJECT

public:
    explicit admin_gestion_usuarios(QWidget *parent = nullptr);
    ~admin_gestion_usuarios();
    void conexionBD();
    void actualizarCatalogo();
    void limiparCatalogo();
    void userSideBar(QString);

private slots:
    void on_btnCrearUsuario_clicked();

private:
    Ui::admin_gestion_usuarios *ui;
    QSqlDatabase mDatabase;
};

#endif // ADMIN_GESTION_USUARIOS_H
