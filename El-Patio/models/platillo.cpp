#include "platillo.h"


Platillo::Platillo(QString _id, QString _nombrePlatillo, QString _precioPlatillo, QString _foto, int _cantidad)
{
    this->id = _id;
    this->nombrePlatillo = _nombrePlatillo;
    this->precioPlatillo = _precioPlatillo;
    this->foto = _foto;
    this->cantidad = _cantidad;
}
