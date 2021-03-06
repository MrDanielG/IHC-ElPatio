#ifndef MESERO_TARJETA_CHICA_H
#define MESERO_TARJETA_CHICA_H

#include <QWidget>
#include <QSqlDatabase>
#include <models/extra.h>
#include <models/platillo.h>

class mesero_menu_comandas;
namespace Ui {
class mesero_tarjeta_chica;
}

class mesero_tarjeta_chica : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_chica(Platillo, mesero_menu_comandas *parent = nullptr);
    explicit mesero_tarjeta_chica(int, QWidget *parent = nullptr);
    ~mesero_tarjeta_chica();
    void llenarTarjeta();
    float get_precio();

private slots:
    void on_btnMenosPlatillo_clicked();

    void on_btnMasPlatillo_clicked();

    void on_btnEditPlatillo_clicked();

private:
    Ui::mesero_tarjeta_chica *ui;
    QSqlDatabase mDatabase;
    mesero_menu_comandas *padre;
    QList<extra> listaExtras;

    Platillo platillo;
};

#endif // MESERO_TARJETA_CHICA_H
