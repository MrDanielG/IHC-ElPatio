#ifndef ALMACENISTA_CREAR_INSUMO_H
#define ALMACENISTA_CREAR_INSUMO_H

#include <QDialog>

namespace Ui {
class almacenista_crear_insumo;
}

class almacenista_crear_insumo : public QDialog
{
    Q_OBJECT

public:
    explicit almacenista_crear_insumo(QWidget *parent = nullptr);
    ~almacenista_crear_insumo();

private:
    Ui::almacenista_crear_insumo *ui;
};

#endif // ALMACENISTA_CREAR_INSUMO_H
