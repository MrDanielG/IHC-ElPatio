#ifndef MESERO_TARJETA_CANCELAR_H
#define MESERO_TARJETA_CANCELAR_H

#include <QWidget>

class mesero_cancela_platillos;

namespace Ui {
class mesero_tarjeta_cancelar;
}

class mesero_tarjeta_cancelar : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_cancelar(QWidget *parent = nullptr);
    explicit mesero_tarjeta_cancelar(QString _pedido, QString _nombrePlatillo, QString _extra, QString _precio, mesero_cancela_platillos *_padre, QWidget *parent = nullptr);
    void estadoTarjeta(bool estado);
    bool getEstado();
    QString getPedido();
    ~mesero_tarjeta_cancelar();

private slots:
    void on_btn_cambiar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::mesero_tarjeta_cancelar *ui;

    mesero_cancela_platillos *padre;

    QString pedido;
    QString nombrePlatillo;
    QString extra;
    QString precio;
    bool cancelada;
};

#endif // MESERO_TARJETA_CANCELAR_H
