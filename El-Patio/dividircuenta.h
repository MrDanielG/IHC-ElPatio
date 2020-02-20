#ifndef DIVIDIRCUENTA_H
#define DIVIDIRCUENTA_H

#include <QWidget>
#include <QSqlDatabase>

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

private:
    Ui::DividirCuenta *ui;
    QSqlDatabase mDatabase;
    QString idComanda;
};

#endif // DIVIDIRCUENTA_H
