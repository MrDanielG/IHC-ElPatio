#include "pedido.h"

Pedido::Pedido()
{

}

Pedido::Pedido(QString _idPedido, QString _idComanda, QString _nombrePlatillo, QString _comentario, QString _estado)
{
    this->idPedido = _idPedido;
    this->idComanda = _idComanda;
    this->nombrePlatillo = _nombrePlatillo;
    this->comentario = _comentario;
    this->estado = _estado;
}
