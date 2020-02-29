#ifndef DIVIDIRCUENTA_H
#define DIVIDIRCUENTA_H

#include <QWidget>
#include <QSqlDatabase>
#include <QTableWidget>
#include <QLabel>

namespace Ui {
class DividirCuenta;
}

class DividirCuenta : public QWidget
{
    Q_OBJECT

public:
    explicit DividirCuenta(QWidget *parent = nullptr);
    ~DividirCuenta();
    void setIdComanda(QString idC);
    void llenaCuentaPrincipal(QString query, QString query2);
    void setIdMesero();
    void setQuery(QString query);

public slots:
    void Dividir();

private slots:
    void on_btnAceptar_clicked();

    void on_btnCancelar_clicked();

private:
    Ui::DividirCuenta *ui;
    QSqlDatabase mDatabase;
    QString idComanda;
    QTableWidget * cuentas[4];
    QLabel * total[4];
    int numeroCuenta = 1;
};

#endif // DIVIDIRCUENTA_H
