#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>


class mesero_menu_comandas;
class almacenista_menu;

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

private:
    Ui::MainWindow *ui;
    //conexion BD
    QSqlDatabase mDatabase;

    //paginas de los usuarios
    mesero_menu_comandas *menuComandas;
    almacenista_menu *menuAlmacenista;

};

#endif // MAINWINDOW_H
