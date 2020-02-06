#ifndef PLATILLO_H
#define PLATILLO_H
#include "QString"

class Platillo
{
private:


public:
    Platillo(QString, QString, QString, QString, int);
    QString id;
    QString nombrePlatillo;
    QString precioPlatillo;
    QString foto;
    int cantidad = 0;
    void setCantidad(int nueva);
    bool operator ==(Platillo P);
};

#endif // PLATILLO_H
