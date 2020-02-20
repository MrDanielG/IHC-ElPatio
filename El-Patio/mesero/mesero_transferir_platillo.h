#ifndef MESERO_TRANSFERIR_PLATILLO_H
#define MESERO_TRANSFERIR_PLATILLO_H

#include <QWidget>
#include <QSqlDatabase>

class MainWindow;
class mesero_tarjeta_chica;

namespace Ui {
class mesero_transferir_platillo;
}

class mesero_transferir_platillo : public QWidget
{
    Q_OBJECT

public:
    explicit mesero_transferir_platillo(QWidget *parent = nullptr);
    ~mesero_transferir_platillo();
    void setMainWindow(MainWindow *);
    void set_idComanda(int _idComanda);
    void actualizarDatos();

private slots:
    void on_btnRegresarMenu_clicked();

private:
    Ui::mesero_transferir_platillo *ui;
    QSqlDatabase mDatabase;
    MainWindow *mainWindow;

    int id_comanda;
    QList<mesero_tarjeta_chica*> lista_platillos;
};

#endif // MESERO_TRANSFERIR_PLATILLO_H
