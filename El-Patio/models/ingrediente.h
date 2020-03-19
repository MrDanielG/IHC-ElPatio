#ifndef INGREDIENTE_H
#define INGREDIENTE_H
#include <QString>

class Ingrediente
{
public:
    Ingrediente();
    QString idIngrediente;
    QString nombreIngrediente;
    bool operator == (Ingrediente I);
};

#endif // INGREDIENTE_H
