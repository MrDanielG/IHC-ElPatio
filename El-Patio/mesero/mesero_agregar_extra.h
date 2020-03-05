#ifndef MESERO_AGREGAR_EXTRA_H
#define MESERO_AGREGAR_EXTRA_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class mesero_agregar_extra;
}

class mesero_agregar_extra : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_agregar_extra(QWidget *parent = nullptr);
    ~mesero_agregar_extra();
    void actualizarCatalogo();
    void limiparCatalogo();

private slots:

private:
    Ui::mesero_agregar_extra *ui;
    QSqlDatabase mDatabase;
};

#endif // MESERO_AGREGAR_EXTRA_H
