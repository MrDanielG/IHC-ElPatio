#ifndef MESERO_TARJETA_TRANSFERIR_H
#define MESERO_TARJETA_TRANSFERIR_H

#include <QWidget>
#include <QSqlDatabase>

class mesero_transferir_platillo;

namespace Ui {
class mesero_tarjeta_transferir;
}

class mesero_tarjeta_transferir : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_transferir(QWidget *parent = nullptr);
    explicit mesero_tarjeta_transferir(int, int, QWidget *parent = nullptr);
    void llenarTarjeta();
    void setPadre(mesero_transferir_platillo *);
    void mover_transferir();
    void quitar_transferir();
    QString get_idPedido();
    ~mesero_tarjeta_transferir();

private slots:
    void on_btn_cambiar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::mesero_tarjeta_transferir *ui;
    QString id;
    QString id_pedido;
    QString nombrePlatillo;
    QString precioPlatillo;
    QString foto;
    int posicion_lista;
    //conexion BD
    QSqlDatabase mDatabase;
    mesero_transferir_platillo *padre;
};

#endif // MESERO_TARJETA_TRANSFERIR_H
