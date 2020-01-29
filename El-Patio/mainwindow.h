#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "mesero/mesero_menu_comandas.h"
//#include "catalogomesas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void cambiarStacked_indice(int);

private:
    Ui::MainWindow *ui;
    QSqlDatabase mDatabase;
    mesero_menu_comandas menuComandas;
    //CatalogoMesas Mesas;

};

#endif // MAINWINDOW_H
