#ifndef ADMIN_LANDPAGE_H
#define ADMIN_LANDPAGE_H

#include <QWidget>

class admin_gestion_usuarios;
class administrador_crud_platillos;
class admin_reportes;
//Falta reservaciones

namespace Ui {
class admin_landpage;
}

class admin_landpage : public QWidget
{
    Q_OBJECT

public:
    explicit admin_landpage(QString _idAdmin, QWidget *parent = nullptr);
    ~admin_landpage();

private:
    Ui::admin_landpage *ui;
    QString idAdmin;

    //Paginas de Admin
    admin_gestion_usuarios *gestionUsuarios;
    administrador_crud_platillos *crudPlatillos;
    admin_reportes *reportes;

};

#endif // ADMIN_LANDPAGE_H
