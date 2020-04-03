#include "admin_reservaciones.h"
#include "ui_admin_reservaciones.h"
#include "reservacionesagendadas.h"

#include <algorithm>
#include <QDialog>
#include <QDate>
#include <QTime>
#include <QStringListModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QInputDialog>
#include <QMessageBox>

admin_reservaciones::admin_reservaciones(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_reservaciones)
{
    ui->setupUi(this);

    QTime initHour(8,0,0);
    QTime endHour(13,0,0);

    // ocultar los números de semana
    ui->calendario->setVerticalHeaderFormat(CalendarWidget::NoVerticalHeader);

    // el día minimo para la cita es hoy si la hora es prudente
    (QTime::currentTime() > initHour && QTime::currentTime() < endHour) ?
                ui->calendario->setMinimumDate(QDate::currentDate())
                 : ui->calendario->setMinimumDate(QDate::currentDate().addDays(1));

    ui->calendario->setGridVisible(true);

    // Colores y etiqueta de los días marcados
    ui->calendario->setMarkColor(Qt::lightGray);
    ui->calendario->setMarkLabel("Lleno");
    //connect(ui->calendario, &CalendarWidget::clicked,
      //      this, &admin_reservaciones::setHours);

    ui->fechaReserva->setText(QDate::currentDate().toString("dd / MM / yyyy"));

    mDatabase = QSqlDatabase::database("Connection");
    if (!mDatabase.isOpen()){
        qDebug() << "ERROR con Base de Datos (Reservaciones)";
        return;
    }
    else{
        qDebug() << "Base de datos continua abierta (Reservaciones)";
    }

    llenaMesas();

    ui->currentDate->setText(QDate::currentDate().toString("ddd, dd MMMM yyyy"));

    connect(ui->calendario, &CalendarWidget::clicked,
                this, &admin_reservaciones::setDate);

    ui->timeEdit->setTime(QTime::currentTime());
}

void admin_reservaciones::setHours(const QDate &date)
{
    /*ui->btnCrearReserva->setEnabled(false);
    QStringList hoursList;
    if(ui->calendario->isMarked(date)
       || date.dayOfWeek() == Qt::Saturday
       || date.dayOfWeek() == Qt::Sunday )
    {
         horasModel->setStringList(hoursList);
         return;
    }

    QTime horaEntrada = medicoRecord.value("HoraEntrada").toTime();
    QTime horaSalida  = medicoRecord.value("HoraSalida").toTime();
    QTime horaComida  = medicoRecord.value("HoraComida").toTime();
    QSet<QTime> horasDisponible;
    QSet<QTime> horasOcupadas;

    if(date == QDate::currentDate())
    {
        auto horaActual = QTime::currentTime();
        int horasRedondeo = (horaActual.minute() > 29 ? 2 : 1);
        horaEntrada.setHMS(horaActual.hour() + horasRedondeo, 0, 0);
    }

    for(QTime hora = horaEntrada; hora < horaSalida; hora  = hora.addSecs(3600))
    {
        horasDisponible.insert(hora);
    }
    horasDisponible.remove(horaComida);

    // if(date==QDate::currentDate()){
    //     if(horaEntrada<=QTime::currentTime()){
    //         for(QTime hora = horaEntrada; hora < QTime::currentTime(); hora  = hora.addSecs(3600))
    //         {
    //             horasDisponible.remove(hora);
    //         }
    //     }
    // }

    QSqlQuery queryMedico(QSqlDatabase::database("Connection"));
    QString qMedico = "SELECT * FROM Evento WHERE cedula_medico = :idMedico AND fecha_evento = :fecha";

    queryMedico.prepare(qMedico);


    queryMedico.bindValue(":idMedico", idMedico.toInt());
    queryMedico.bindValue(":fecha", date);

    queryMedico.exec();
    while(queryMedico.next())
    {
        horasOcupadas.insert(queryMedico.value("hora_inicio").toTime());
    }

    horasDisponible -= horasOcupadas;

    QList<QTime> listaHoras = horasDisponible.toList();

    std::sort(listaHoras.begin(), listaHoras.end());

    for(auto &f : listaHoras)
    {
        hoursList << f.toString("hh:mm 'hrs.'");
    }
    horasModel->setStringList(hoursList);*/

}

admin_reservaciones::~admin_reservaciones()
{
    delete ui;
}
/*
#include "evento.h"
#include "cita.h"
#include "metodopago.h"

void VerAgendaMedico::setDiasLlenos()
{
    QTime horaEntrada = medicoRecord.value("HoraEntrada").toTime();
    QTime horaSalida  = medicoRecord.value("HoraSalida").toTime();
    int HorasDisponible = horaSalida.hour() - horaEntrada.hour() - 1;
    if(QTime::currentTime() >= horaSalida)
    {
        ui->calendario->setMinimumDate(QDate::currentDate().addDays(1));
        return;
    }
    QSqlQuery query(QSqlDatabase::database("Connection"));
    QString q =
        "SELECT fecha_evento, COUNT(id_evento) AS nEventos "
        " FROM Evento "
        " WHERE cedula_medico = :idMedico "
        " GROUP by fecha_evento";
    query.prepare(q);
    query.bindValue(":idMedico", idMedico.toInt());
    query.exec();
    if(query.next())
    {
        QDate fecha = query.value("fecha_evento").toDate();
        int nEventos = query.value("nEventos").toInt();
        if(nEventos >= HorasDisponible)
        {
            ui->calendario->markDate(fecha);
        }
    }

    ui->calendario->clicked(QDate::currentDate());
}


void VerAgendaMedico::on_listaHoras_clicked()
{
    ui->agendar->setEnabled(true);
    ui->reagendar->setEnabled(true);
}

void VerAgendaMedico::on_regresar_clicked()
{
        emit regresar();
}

// Slot para agendar
void VerAgendaMedico::on_agendar_clicked()
{
    // Datos base para agendar una cita.
    // FIXME: falta pasarle de alguna manera
    // a este widget el no_afiliacion del paciente
    // en curso.
    QDate fecha = ui->calendario->selectedDate();
    QString horaStr = ui->listaHoras->currentIndex().data().toString();
    QTime hora  = QTime::fromString(horaStr, "hh:mm 'hrs.'");
    // double precio = ui->precio->text().toDouble();
    //para fines de pruebas se muestra la info. base en consola
    // qInfo() << "Medico: " << idMedico
    //         << "\nFecha cita: " << fecha.toString("yyyy-MM-dd")
    //         << "\nHora cita: " << hora.toString("HH:mm:ss")
    //         << "\nPrecio consulta: " << QString::number(precio);


        Evento nuevoEvento(idMedico,
                       hora.toString("HH:mm:ss"),
                       hora.addSecs(3600).toString("HH:mm:ss"),
                       fecha.toString("yyyy.MM.dd"));
        QMessageBox::StandardButton reply2;
        reply2=QMessageBox::question(this,"Confirmar cita",
                                    "¿Desea confirmar su cita? <br/> <b>Datos</b><br/> "
                                    +nuevoEvento.formatoDatos(),
                                    QMessageBox::Yes|QMessageBox::No);
        if(reply2==QMessageBox::Yes)
        {
            QString id_evento=nuevoEvento.insertarBD();
            qDebug()<< id_evento;
            Cita nuevaCita(noAfiliacion,id_evento);//FIXME: Número de afiliación del paciente
            QString id_cita=nuevaCita.insertarBD();
            qDebug() << "noAfil: " <<noAfiliacion << "idCita: " << id_cita << "cedula: " << idMedico;
            QMessageBox::information(this,"Cita agendada","A continuación, seleccione un método de pago.");
            if(idOrden!=""){
                QSqlQuery query(QSqlDatabase::database("Connection"));
                query.prepare("UPDATE OrdenInterconsulta set estado= 'Agendada' "
                              "where idOrden = :idOrden");
                query.bindValue(":idOrden", idOrden);
                query.exec();

            }
            MetodoPago mp(id_cita); mp.exec();

            emit interAgendado(true);
            emit regresar();
        }

}

void VerAgendaMedico::setPaciente(QString noA){

    noAfiliacion=noA;

    QSqlQuery queryPaciente(QSqlDatabase::database("Connection"));

    QString qPaciente = "SELECT * FROM Cita AS c "
        " INNER JOIN Evento AS e ON c.id_evento = e.id_evento "
        " WHERE e.cedula_medico = :cedula_medico AND c.no_afiliacion=:no_afiliacion"
        " ORDER BY e.fecha_evento DESC"
        " LIMIT 1";
    queryPaciente.prepare(qPaciente);

    queryPaciente.bindValue(":no_afiliacion", noAfiliacion);
    queryPaciente.bindValue(":cedula_medico", idMedico);
    queryPaciente.exec();
    if(queryPaciente.next())
    {
        QDate minDate = queryPaciente.value("fecha_evento").toDate().addDays(7);
        if(minDate >= QDate::currentDate())
            ui->calendario->setMinimumDate(minDate);
    }
}

void VerAgendaMedico::setMedicoPaciente(QString idMed, const QSqlRecord &medRec, QString noAfil)
{
    setMedico(idMed, medRec);
    setPaciente(noAfil);
}

void VerAgendaMedico::setCitaMedico(const QSqlRecord &cita)
{
    citaRecord = cita;
    ui->agendar->hide();
    ui->precio->hide();
    ui->label_4->hide();
    ui->reagendar->show();
    ui->label_3->setText("3. Presione \"Regendar Cita\"");
    connect(this, &VerAgendaMedico::regresar, parentWidget(), &VerAgendaMedico::close);

    QSqlQuery query(QSqlDatabase::database("Connection"));
    query.prepare("SELECT * FROM VistaMedico WHERE Cedula=:cedula");
    query.bindValue(":cedula", citaRecord.value("Cedula").toInt());
    if(!query.exec())
    {
        qCritical() << query.lastError().text();
        return;
    }
    query.next();
    idMedico = cita.value("Cedula").toString();
    medicoRecord = query.record();
    ui->nombreMed->setText("Mi agenda");
    setDiasLlenos();

}

void VerAgendaMedico::setIdOrden(QString idOrd)
{
    idOrden = idOrd;
}

void VerAgendaMedico::on_reagendar_clicked()
{
    QDate fecha = ui->calendario->selectedDate();
    QString horaStr = ui->listaHoras->currentIndex().data().toString();
    QTime hora  = QTime::fromString(horaStr, "hh:mm 'hrs.'");
    bool ok;



    QString motivo = QInputDialog::getMultiLineText(this,
                                                    "Motivo para Reagendar",
                                                    "Introduzca el motivo por el cual desea reagendar", QString(),
                                                    &ok);
    if(ok && !motivo.isEmpty())
    {
        QSqlDatabase db = QSqlDatabase::database("Connection");
        QSqlQuery queryS(db);
        QString q = "INSERT INTO SolicitudReagendar (Cedula, id_cita, fechaCita, horaCita, "
            " motivo, nuevaFecha, nuevaHora, fechaSolicitud, horaSolicitud) "
            " VALUES(:Cedula, :id_cita, :fechaCita, :horaCita, "
            " :motivo, :nuevaFecha, :nuevaHora, :fechaSolicitud, :horaSolicitud)";
        queryS.prepare(q);
        queryS.bindValue(":Cedula", citaRecord.value("Cedula"));
        queryS.bindValue(":id_cita", citaRecord.value("id_cita"));
        queryS.bindValue(":fechaCita", citaRecord.value("fecha_evento"));
        queryS.bindValue(":horaCita", citaRecord.value("hora_inicio"));
        queryS.bindValue(":motivo", motivo);
        queryS.bindValue(":nuevaFecha", fecha);
        queryS.bindValue(":nuevaHora", hora);
        queryS.bindValue(":fechaSolicitud", QDate::currentDate());
        queryS.bindValue(":horaSolicitud", QTime::currentTime());
        if(db.transaction())
        {
            if(queryS.exec())
            {
                QSqlQuery queryC(db);
                queryC.prepare("UPDATE Cita SET estado = 'Reagendando' WHERE id_cita = :id");
                queryC.bindValue(":id", citaRecord.value("id_cita"));
                if(queryC.exec())
                {
                    db.commit();
                    QMessageBox::information(this, "Solicitud en proceso", "Su solicitud de reagendado está en proceso");
                    qobject_cast<QDialog*>(parentWidget())->accept();
                }
                else
                    db.rollback();
            }
            else
                db.rollback();

        }
        else
        {
            db.rollback();
            QMessageBox::critical(this, "Error", "Error: " + db.lastError().text());
        }

    }


}
*/

void admin_reservaciones::llenaMesas()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT numero_mesa FROM Mesa";
    query.prepare(script);
    query.exec();
    while(query.next())
        ui->cBoxMesas->addItem(query.value(0).toString());

}

void admin_reservaciones::on_btnMasExtra_clicked()
{
    int nPersonas = ui->numPersonas->text().toInt();
    (nPersonas < 10) ? nPersonas += 1 : nPersonas;
    ui->numPersonas->setText(QString::number(nPersonas));
}

void admin_reservaciones::on_btnMenosExtra_clicked()
{
    int nPersonas = ui->numPersonas->text().toInt();
    (nPersonas > 1) ? nPersonas -= 1 : nPersonas;
    ui->numPersonas->setText(QString::number(nPersonas));
}

void admin_reservaciones::setDate(const QDate &date)
{
    currentDate = date.toString("dd / MM / yyyy");
    ui->fechaReserva->setText(date.toString("dd / MM / yyyy"));
}

void admin_reservaciones::on_btnCrearReserva_clicked()
{
    QSqlQuery query(mDatabase);
    bool band = true;
    QString numero_mesa = ui->cBoxMesas->currentText();
    QString fReserva = ui->fechaReserva->text();
    QString hReserva = ui->timeEdit->text();
    QString cliente = ui->nomCliente->text();
    QString nPersonas = ui->numPersonas->text();

    QSqlQuery queryCheck(mDatabase);
    QString scriptCheck = "SELECT numero_mesa,hora_llegada FROM "
                          "reserva WHERE fecha = '"+fReserva+"' ";
    queryCheck.prepare(scriptCheck);
    queryCheck.exec();
    while(queryCheck.next())
    {
        if(queryCheck.value(0).toString() == numero_mesa &&
                queryCheck.value(1).toString() == hReserva)
            band = false;
    }

    if(!cliente.isEmpty() && band == true){
        QString script = "INSERT INTO reserva (numero_mesa, "
                         "fecha, hora_llegada, nombre_cliente, "
                         "num_personas) VALUES "
                         "("+numero_mesa+",'"+fReserva+"', "
                         "'"+hReserva+"', '"+cliente+"', "+nPersonas+")";
        query.prepare(script);
        query.exec();
        QMessageBox::information(this, tr("Exito"),
                             "La reservacion se ha realizado correctamente");
    }else{
        if(band == true){
            QMessageBox::warning(this, tr("Error"),
                "Por favor, llene el campo destinado para el nombre");
        }else{
            QMessageBox::warning(this, tr("Error"),
                "Ya fue registrada una reservacion con los mismos datos");
        }
    }

}

void admin_reservaciones::on_btnVerAgenda_clicked()
{
    reservacionesAgendadas dates(currentDate,this);
    dates.exec();
}
