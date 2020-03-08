#include "mesero_cancela_platillos.h"
#include "ui_mesero_cancela_platillos.h"
#include "mesero_tarjeta_cancelar.h"
#include "mesero/confirmartransferencia.h"

#include <QDebug>
#include <QMessageBox>

mesero_cancela_platillos::mesero_cancela_platillos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mesero_cancela_platillos)
{
    ui->setupUi(this);
    conexionBD();
}

void mesero_cancela_platillos::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
     if (!mDatabase.isOpen()){
         qDebug() << "ERROR con Base de Datos, esto es: CANCELA PLATILLO";
         return;
     }
     else{
         qDebug() << "Base de datos continua abierta, esto es: CANCELA PLATILLO";
     }
}

void mesero_cancela_platillos::set_idComanda(QString _idComanda)
{
    idComanda = _idComanda;
    actualizarDatos();
}

void mesero_cancela_platillos::actualizarDatos()
{
    limpiar_gridListaPlatillos();
    QSqlQuery datosComando(mDatabase);
    QSqlQuery datosMesero(mDatabase);
    QSqlQuery datosPlatillos(mDatabase);
    QSqlQuery datosPedido(mDatabase);

    //datos comanda
    QString query_datosComanda = "SELECT * FROM comanda WHERE id_comanda = " + idComanda + ";";
    if(datosComando.exec(query_datosComanda))
        qDebug() << "datosComando [ejecutado] " + query_datosComanda;
    else
        qDebug() << "datosComando [no_ejecutado]";
    datosComando.next();

    ui->lb_numMesa->setText(datosComando.value("Mesa_numero_mesa").toString());
    ui->lb_numComanda->setText(datosComando.value("id_comanda").toString());

    //obtengo los datos del empleado
    QString claveMesero = datosComando.value("Usuario_clave").toString();
    QString query_datosMesero =
            "select clave, concat(nombre, ' ', apellido_paterno, ' ', apellido_materno) as nombre "
            "from usuario where clave = " + claveMesero + ";";

    if(datosMesero.exec(query_datosMesero))
        qDebug() << "query_datosMesero [ejecutado] "  + query_datosMesero;
    else
        qDebug() << "query_datosMesero [no_ejecutado] " + query_datosMesero;
    datosMesero.next();

    ui->lb_nomMesero->setText(datosMesero.value("nombre").toString());

    //lleno lista con tarjetas de los platillos respecto la comanda
    QString query_platillos =
            "select * from pedido "
            "where Comanda_id_comanda = " + idComanda;/* + " and estado = 'En proceso';";*/

    if(datosPedido.exec(query_platillos))
        qDebug() << "query_platillos [ejecutado]" + query_platillos;
    else
        qDebug() << "query_platillos [no_ejecutado]" ;

    while(datosPedido.next()){
        QString pedido          = datosPedido.value("id_Pedido").toString();

        QString query = "select * from platillo where id_platillo = "+datosPedido.value("Platillo_id_platillo").toString()+";";
        datosPlatillos.exec(query);
        datosPlatillos.next();

        QString nombrePlatillo  = datosPlatillos.value("nombre").toString();
        QString extra           = datosPedido.value("comentario").toString();
        QString precio          = datosPlatillos.value("precio").toString();

        qDebug() << pedido << nombrePlatillo << extra << precio  << datosPedido.value("estado").toString();

        mesero_tarjeta_cancelar *aux = new mesero_tarjeta_cancelar(pedido, nombrePlatillo, extra, precio, this, this );
        lista_platillos_comanda.append(aux);
    }

    int iterador = 0;
    int row = 0;
    int col = 0;
    while(iterador < lista_platillos_comanda.size())
    {
        row = iterador / 2;
        col = iterador % 2;
        ui->gridListaPlatillos->addWidget(lista_platillos_comanda.at(iterador), row, col );
        iterador++;
    }

}

void mesero_cancela_platillos::limpiar_gridListaPlatillos()
{
    int iterador = 0;
    while(iterador < lista_platillos_comanda.size())
    {
        ui->gridListaPlatillos->removeWidget(lista_platillos_comanda.at(iterador));
        lista_platillos_comanda.at(iterador)->~mesero_tarjeta_cancelar();
        iterador++;
    }
    this->lista_platillos_comanda.clear();
}

mesero_cancela_platillos::~mesero_cancela_platillos()
{
    delete ui;
}

void mesero_cancela_platillos::on_btnCancelarPlatillos_clicked()
{
    //obtener la clave del admin
    ConfirmarTransferencia confirmarCancelacion;
    confirmarCancelacion.setModal(true);
    confirmarCancelacion.exec();

    if(confirmarCancelacion.result())
    {
        QSqlQuery validor_ClaveAdmin(mDatabase);
        QString query_validorClaveAdmin = "select * from usuario "
                                          "where clave = "+confirmarCancelacion.get_claveAdmin()+" ;";
        validor_ClaveAdmin.exec(query_validorClaveAdmin);
        if (!validor_ClaveAdmin.next())
        {
            QMessageBox::warning(this, "Clave incorrecta", "la clave es incorrecta o no existe");
        }
        else
        {
            QSqlQuery cancelarPlatillos(mDatabase);
            QString query;

            int iterador = 0;
            while(iterador < lista_platillos_comanda.size())
            {
                mesero_tarjeta_cancelar *aux = lista_platillos_comanda.at(iterador);
                if(aux->getEstado())
                {
                    query = "update pedido set estado = 'Cancelado' "
                            "where Comanda_id_comanda = "+idComanda+" and id_pedido = "+aux->getPedido()+";";
                    cancelarPlatillos.exec(query);
                    cancelarPlatillos.next();
                }
                iterador++;
            }
            actualizarDatos();
            QMessageBox::information(this, "Cancelacion de Platillos", tr("Cancelacion de Platillos completada exitosamente.") );
        }
    }
}

void mesero_cancela_platillos::on_btnCancelar_clicked()
{
    if (QMessageBox::question(this, "Regresar a Menú", "¿Desea regresar al menú?")
            == QMessageBox::Yes)
        this->close();
}

void mesero_cancela_platillos::on_cBox_CancelarComanda_stateChanged(int arg1)
{
    if (arg1) {
        int iterador = 0;
        while (iterador < lista_platillos_comanda.size()) {
            lista_platillos_comanda.at(iterador)->estadoTarjeta(true);
            iterador++;
        }
    } else {
        int iterador = 0;
        while (iterador < lista_platillos_comanda.size()) {
            lista_platillos_comanda.at(iterador)->estadoTarjeta(false);
            iterador++;
        }
    }
}
