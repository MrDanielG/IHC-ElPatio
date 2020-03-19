#ifndef PLATILLO_H
#define PLATILLO_H
#include <QString>
#include <QList>
#include <models/extra.h>

class Platillo
{
private:


public:
    Platillo();
    Platillo(QString, QString, QString, QString, int);
    QString id;
    QString nombrePlatillo;
    QString precioPlatillo;
    QString foto;
    QString categoria;
    QString estado;

    int cantidad = 0;
    QList<extra> listaExtras;

    void setCantidad(int nueva);
    bool operator ==(Platillo P);
};

#endif // PLATILLO_H
