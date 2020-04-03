#ifndef COCINERO_PEDIDOS_H
#define COCINERO_PEDIDOS_H

#include <QWidget>
#include <QSqlDatabase>
#include <models/pedido.h>
namespace Ui {
class cocinero_pedidos;
}

class cocinero_pedidos : public QWidget
{
    Q_OBJECT

public:
    explicit cocinero_pedidos(QWidget *parent = nullptr);
    void conexionBD();
    void actualizarCatalogo();
    void limiparCatalogo();
    void sideBarInfo(Pedido _pedido);
    bool isCocinero;
    ~cocinero_pedidos();

private slots:
    void on_btnPedidoListo_clicked();

    void on_btnActualizar_clicked();

private:
    Ui::cocinero_pedidos *ui;
    QSqlDatabase mDatabase;
    Pedido pedidoAux;
};

#endif // COCINERO_PEDIDOS_H
