#ifndef MESERO_MENU_COMANDAS_H
#define MESERO_MENU_COMANDAS_H

#include <QWidget>
#include <QSqlDatabase>
#include "models/platillo.h"

class mesero_tarjeta_chica;
class MainWindow;

namespace Ui {
class mesero_menu_comandas;
}

class mesero_menu_comandas : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_menu_comandas(QWidget *parent = nullptr);
    ~mesero_menu_comandas();
    void actualizarCatalogo();
    void limiparCatalogo();
    void actualizarSideBar(Platillo, int);
    void limpiarSideBar();
    void actualizarSB();

private slots:
    void on_btnMandarCocina_clicked();
    void setMainWindow(MainWindow *);
    void set_id_mesa(int);
    void limpiar_grid4();
    void on_btnBebidas_2_clicked();
    void on_btnPlatillos_2_clicked();

private:
    Ui::mesero_menu_comandas *ui;
    QSqlDatabase mDatabase;
    QList<Platillo> pedidoPlatillos;

    //datos_comanda
    int clave_mesero;
    int numero_mesa;
    int numero_comanda;

    //lista de la comanda
    QList<mesero_tarjeta_chica*> lista_platillos;

    MainWindow *mainwindow;
};

#endif // MESERO_MENU_COMANDAS_H
