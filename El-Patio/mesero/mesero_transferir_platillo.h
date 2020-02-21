#ifndef MESERO_TRANSFERIR_PLATILLO_H
#define MESERO_TRANSFERIR_PLATILLO_H

#include <QWidget>
#include <QSqlDatabase>

class MainWindow;
class mesero_tarjeta_transferir;

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
    void mover_platillo(QString);
    void sacar_platillo(QString);
    void actualizar_grid();
    void actualizarDatos();
    void limpiarGRidListas();

private slots:
    void on_btnRegresarMenu_clicked();

    void on_btn_transferirPlatillos_clicked();

private:
    Ui::mesero_transferir_platillo *ui;
    QSqlDatabase mDatabase;
    MainWindow *mainWindow;

    int id_comanda;
    QList<mesero_tarjeta_transferir*> lista_platillos;
    QList<mesero_tarjeta_transferir*> copia_listaPlatillos;
    QList<mesero_tarjeta_transferir*> transferir_listPlatillos;
};

#endif // MESERO_TRANSFERIR_PLATILLO_H
