#ifndef ADMIN_LANDPAGE_H
#define ADMIN_LANDPAGE_H

#include <QWidget>

class MainWindow;
class admin_gestion_usuarios;
class administrador_crud_platillos;
class admin_reportes;
class admin_reservaciones;

namespace Ui {
class admin_landpage;
}

class admin_landpage : public QWidget
{
    Q_OBJECT

public:
    explicit admin_landpage(QWidget *parent = nullptr);
    void setIdAdmin(QString);
    ~admin_landpage();

private slots:
    void on_btnPlatillos_clicked();

    void on_btnUsuarios_clicked();

    void on_btnReportes_clicked();

    void on_btnCerrarSesion_clicked();

    void on_btnInicio_clicked();

    void on_btnReservas_clicked();

private:
    Ui::admin_landpage *ui;
    QString idAdmin;
    MainWindow *padre;

    //Paginas de Admin
    admin_gestion_usuarios *gestionUsuarios;
    administrador_crud_platillos *crudPlatillos;
    admin_reportes *reportes;
    admin_reservaciones *reservaciones;

};

#endif // ADMIN_LANDPAGE_H
