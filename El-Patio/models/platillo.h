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
};

#endif // PLATILLO_H