#include "platillo.h"


Platillo::Platillo()
{

}

Platillo::Platillo(QString _id, QString _nombrePlatillo, QString _precioPlatillo, QString _foto, int _cantidad)
{
    this->id = _id;
    this->nombrePlatillo = _nombrePlatillo;
    this->precioPlatillo = _precioPlatillo;
    this->foto = _foto;
    this->cantidad = _cantidad;
}

void Platillo::setCantidad(int nueva)
{
    double PrePla = precioPlatillo.toDouble();
    double PrecioOriginal = PrePla/cantidad;
    PrePla += PrecioOriginal;
    precioPlatillo = QString::number(PrePla);
    this->cantidad = nueva;
}

bool Platillo::operator == (Platillo P)
{
    if(this->nombrePlatillo == P.nombrePlatillo)
        return  true;
    else return  false;
}
