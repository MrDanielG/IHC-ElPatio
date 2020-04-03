#ifndef PEDIDO_H
#define PEDIDO_H
#include "QString"

class Pedido
{
public:
    Pedido();
    Pedido(QString _idPedido, QString _idComanda, QString _nombrePlatillo, QString _comentario, QString _estado);
    QString idPedido;
    QString idComanda;
    QString nombrePlatillo;
    QString comentario;
    QString estado;
};

#endif // PEDIDO_H
