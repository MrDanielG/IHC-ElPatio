#ifndef MESERO_MENU_COMANDAS_H
#define MESERO_MENU_COMANDAS_H

#include <QWidget>
#include <QSqlDatabase>

class mesero_tarjeta_chica;

namespace Ui {
class mesero_menu_comandas;
}

class mesero_menu_comandas : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_menu_comandas(int _numero_mesa, QWidget *parent = nullptr);
    ~mesero_menu_comandas();

private slots:
    void on_btnBebidas_2_clicked();

private:
    Ui::mesero_menu_comandas *ui;
    QSqlDatabase mDatabase;

    //datos_comanda
    int clave_mesero;
    int numero_mesa;
    int numero_comanda;

    //lista de la comanda
    QList<mesero_tarjeta_chica*> lista_platillos;

};

#endif // MESERO_MENU_COMANDAS_H
