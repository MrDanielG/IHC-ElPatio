#ifndef ALMACENISTA_CREAR_INSUMO_H
#define ALMACENISTA_CREAR_INSUMO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class almacenista_crear_insumo;
}

class almacenista_crear_insumo : public QDialog
{
    Q_OBJECT

public:
    explicit almacenista_crear_insumo(QWidget *parent = nullptr);
    ~almacenista_crear_insumo();

private slots:
    void on_btnSecundaio_clicked();

    void on_btnPrimario_clicked();

    void on_btnPerecedero_clicked();

    void on_btnNoPerecedero_clicked();

private:
    Ui::almacenista_crear_insumo *ui;
    QSqlDatabase mDatabase;
};

#endif // ALMACENISTA_CREAR_INSUMO_H
