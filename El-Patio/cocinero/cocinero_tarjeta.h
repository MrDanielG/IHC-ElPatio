#ifndef COCINERO_TARJETA_H
#define COCINERO_TARJETA_H

#include <QWidget>
#include <models/pedido.h>

class cocinero_pedidos;
namespace Ui {
class cocinero_tarjeta;
}

class cocinero_tarjeta : public QWidget
{
    Q_OBJECT

public:
    explicit cocinero_tarjeta(Pedido _pedido, cocinero_pedidos *parent = nullptr);
    ~cocinero_tarjeta();

private slots:
    void on_btnInfoPedido_clicked();

private:
    Ui::cocinero_tarjeta *ui;
    cocinero_pedidos *padre;
    Pedido pedido;
};

#endif // COCINERO_TARJETA_H
