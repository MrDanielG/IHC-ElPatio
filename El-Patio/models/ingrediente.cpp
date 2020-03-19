#include "ingrediente.h"

Ingrediente::Ingrediente()
{

}

bool Ingrediente::operator ==(Ingrediente I)
{
    if(this->nombreIngrediente == I.nombreIngrediente && this->idIngrediente == I.idIngrediente){
        return  true;
    } else return false;
}
