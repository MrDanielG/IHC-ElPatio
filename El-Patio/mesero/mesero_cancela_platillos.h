#ifndef MESERO_CANCELA_PLATILLOS_H
#define MESERO_CANCELA_PLATILLOS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

class MainWindow;
class mesero_tarjeta_cancelar;

namespace Ui {
class mesero_cancela_platillos;
}

class mesero_cancela_platillos : public QDialog
{
    Q_OBJECT

public:
    explicit mesero_cancela_platillos(QWidget *parent = nullptr);
    void conexionBD();
    void set_idComanda(QString _idComanda);
    void actualizarDatos();
    void limpiar_gridListaPlatillos();
    ~mesero_cancela_platillos();

private slots:
    void on_btnCancelarPlatillos_clicked();

    void on_btnCancelar_clicked();

    void on_cBox_CancelarComanda_stateChanged(int arg1);

private:
    Ui::mesero_cancela_platillos *ui;
    QSqlDatabase mDatabase;


    QString idComanda;
    QList<mesero_tarjeta_cancelar*> lista_platillos_comanda;
};

#endif // MESERO_CANCELA_PLATILLOS_H
