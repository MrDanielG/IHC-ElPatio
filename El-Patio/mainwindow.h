#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class mesero_menu_comandas;
class almacenista_menu;
class mesero_transferir_platillo;
class admin_gestion_usuarios;
class DividirCuenta;
class administrador_crud_platillos;
class admin_reservaciones;
class admin_reportes;
class login;
class admin_landpage;
class cocinero_landpage;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void cambiar_pagina(int);
    void pasar_id_mesa(int);
    ~MainWindow();
    void cambiarStacked_indice(int);
    void pasar_is_comanda(int);
    void setAdmin(QString);
    void setCocina(QString, bool);

private:
    Ui::MainWindow *ui;
    //conexion BD
    QSqlDatabase mDatabase;

    //paginas de los usuarios
    mesero_menu_comandas *menuComandas;
    almacenista_menu *menuAlmacenista;
    mesero_transferir_platillo *transferirPlatillo;
    admin_gestion_usuarios *gestionUsuarios;
    DividirCuenta *cuentas;
    administrador_crud_platillos *crudPlatillos;
    admin_reservaciones *reservaciones;
    admin_reportes *    reportes;
    login *inicioSesion;
    admin_landpage *adminLandpage;
    cocinero_landpage *cocinaLandpage;
};

#endif // MAINWINDOW_H
