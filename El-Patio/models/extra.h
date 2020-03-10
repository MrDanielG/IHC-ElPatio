#ifndef EXTRA_H
#define EXTRA_H
#include <QString>
class extra
{
public:
    extra();
    extra(QString, QString, QString);
    extra(QString, QString, QString, int);

    QString idExtra;
    QString nombre;
    QString precio;
    QString idPlato;
    int cantidad = 0;

    void setCantidad(int nueva);
    bool operator == (extra E);
};

#endif // EXTRA_H
