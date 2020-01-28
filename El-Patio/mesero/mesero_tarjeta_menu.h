#ifndef MESERO_TARJETA_MENU_H
#define MESERO_TARJETA_MENU_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

class mesero_menu_comandas;
namespace Ui {
class mesero_tarjeta_menu;
}

class mesero_tarjeta_menu : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_tarjeta_menu(QString, QString, QString, QString, mesero_menu_comandas *parent = nullptr);
    ~mesero_tarjeta_menu();
    void llenarTarjeta();
    void actualizarTarjeta();

private slots:
    void on_btnMasPlatillo_clicked();

private:
    Ui::mesero_tarjeta_menu *ui;
    QSqlDatabase mDatabase;
    QString id;
    QString nombrePlatillo;
    QString precioPlatillo;
    QString foto;
    mesero_menu_comandas *padre;
};

#endif // MESERO_TARJETA_MENU_H
