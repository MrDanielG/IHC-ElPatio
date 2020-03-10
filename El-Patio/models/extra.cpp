#include "extra.h"

extra::extra()
{

}

extra::extra(QString id, QString nombre, QString precio)
{
    this->idExtra = id;
    this->nombre = nombre;
    this->precio = precio;
}

extra::extra(QString id, QString nombre, QString precio, int cant)
{
    this->idExtra = id;
    this->nombre = nombre;
    this->precio = precio;
    this->cantidad = cant;
}

void extra::setCantidad(int nueva)
{
    double PreEx = precio.toDouble();
    double PrecioOriginal = PreEx/cantidad;
    PreEx += PrecioOriginal;
    precio = QString::number(PreEx);
    this->cantidad = nueva;
}

bool extra::operator == (extra E)
{
    if(this->nombre == E.nombre)
        return  true;
    else return  false;
}
