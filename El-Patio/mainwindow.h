#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
//#include "mesero/mesero_menu_comandas.h"

class mesero_menu_comandas;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void cambiar_pagina(int);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase mDatabase;
    mesero_menu_comandas *menuComandas;
};

#endif // MAINWINDOW_H
