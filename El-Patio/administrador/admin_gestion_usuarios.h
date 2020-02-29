#ifndef ADMIN_GESTION_USUARIOS_H
#define ADMIN_GESTION_USUARIOS_H

#include <QWidget>
#include <QSqlDatabase>

class QPushButton;

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
    void actualizarCatalogo(QString tipoUsuario);
    void clicked_button(QPushButton *boton);
    void limiparCatalogo();
    void userSideBar(QString);

private slots:
    void on_btnCrearUsuario_clicked();

    void on_btnEditarUsuario_clicked();

    void on_btnMeseros_clicked();

    void on_btnTodo_clicked();

    void on_btnAlmacenista_clicked();

    void on_btnCocinero_clicked();

    void on_btnAdministrador_clicked();

    void on_btnBarista_clicked();

private:
    Ui::admin_gestion_usuarios *ui;
    QSqlDatabase mDatabase;

    QString claveUsuario;
    QString auxTipoUsuario;
};

#endif // ADMIN_GESTION_USUARIOS_H
