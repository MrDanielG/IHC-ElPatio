#ifndef MESERO_MENU_COMANDAS_H
#define MESERO_MENU_COMANDAS_H

#include <QWidget>
#include <QSqlDatabase>
#include "models/platillo.h"

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
    void agregarSideBar(Platillo);
    void limpiarSideBar();

private slots:
    void on_btnMandarCocina_clicked();

private:
    Ui::mesero_menu_comandas *ui;
    QSqlDatabase mDatabase;
    QList<Platillo> pedidoPlatillos;
};

#endif // MESERO_MENU_COMANDAS_H
