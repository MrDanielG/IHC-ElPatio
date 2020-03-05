#ifndef MESERO_EDITAR_PLATILLO_H
#define MESERO_EDITAR_PLATILLO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <mesero/mesero_agregar_extra.h>
#include <models/extra.h>
namespace Ui {
class mesero_editar_platillo;
}

class mesero_editar_platillo : public QDialog
{
    Q_OBJECT

public:
    explicit mesero_editar_platillo(QWidget *parent = nullptr);
    ~mesero_editar_platillo();
    void conexionBD();
    void actualizarCatalogo();
    void limiparCatalogo();

private:
    Ui::mesero_editar_platillo *ui;
    QSqlDatabase mDatabase;

    QList<extra> listaExtras;





    //mesero_agregar_extra agregarExtra;
};

#endif // MESERO_EDITAR_PLATILLO_H
