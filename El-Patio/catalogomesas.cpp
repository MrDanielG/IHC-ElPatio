#include "catalogomesas.h"
#include "ui_catalogomesas.h"
#include "mainwindow.h"
#include <QDate>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QInputDialog>

CatalogoMesas::CatalogoMesas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatalogoMesas)
{
    ui->setupUi(this);

    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug()<<"ERROR, Mesas no conectado";
    }
    AgregarMesas(1);

    ui->fecha->setText(QDate::currentDate().toString("dd/MMMM/yyyy"));

    //this->padre=parent;
    //connect(this, SIGNAL(cambiarStackedWidget()), parent->parent(), SLOT(cambiarStacked_indice(1)));
}

//void CatalogoMesas::setMainWindow(MainWindow *P)
//{    padre = P;}

CatalogoMesas::~CatalogoMesas()
{
    delete ui;
}

void CatalogoMesas::AgregarMesas(int n)
{
    QString script;
    switch (n) {
    case 1:
        script = "SELECT numero_mesa FROM Mesa";
        break;
    case 2:
        script = "SELECT numero_mesa FROM Mesa WHERE Estado = 'Libre'";
        break;
    case 3:
        script = "SELECT numero_mesa FROM Mesa WHERE Estado = 'Ocupado'";
        break;
    }

    QFont fuente("MS Shell Dlg 2",25,4,false);
    QString estilo = "*{background-color: rgb(225, 225, 225);"
                      " border:1px solid black;"
                      "padding: 0 8px;"
                      "border-radius: 10px; padding: 0 8px; }"
                      "QPushButton:hover { border: 2px solid  #66c011; }";
    QSqlQuery query(mDatabase);
    query.prepare(script);
    query.exec();
    int i = 0;
    while(query.next())
    {
        QPushButton * mesa = new QPushButton(this);
        mesa->setText(query.value(0).toString());
        mesa->setMinimumWidth(150);
        mesa->setMinimumHeight(150);
        mesa->setMaximumWidth(150);
        mesa->setMaximumHeight(150);
        mesa->setFont(fuente);
        mesa->show();
        mesa->setStyleSheet(estilo);
        ui->gridLayout_3->addWidget(mesa,i/4, i%4);
        connect(mesa,SIGNAL(clicked()), this, SLOT(seleccionarMesa()));
        i++;
    }
    query.finish();
}


void CatalogoMesas::on_btnTodos_clicked()
{
    borrar();
    QString newStyle = "*{background-color: rgb(255, 255, 255);"
                    "border: 2px solid rgb(255,255,255);"
                    "border-bottom-color: gray;}";
    QString oldStyle = "*{background-color: rgb(255, 255, 255);"
                       "border: 2px solid rgb(255,255,255);}";

    ui->btnTodos->setStyleSheet(newStyle);
    ui->btnLibre->setStyleSheet(oldStyle);
    ui->btnOcupado->setStyleSheet(oldStyle);
    AgregarMesas(1);
}

void CatalogoMesas::on_btnLibre_clicked()
{
    borrar();
    QString newStyle = "*{background-color: rgb(255, 255, 255);"
                    "border: 2px solid rgb(255,255,255);"
                    "border-bottom-color: gray;}";
    QString oldStyle = "*{background-color: rgb(255, 255, 255);"
                       "border: 2px solid rgb(255,255,255);}";
    ui->btnTodos->setStyleSheet(oldStyle);
    ui->btnLibre->setStyleSheet(newStyle);
    ui->btnOcupado->setStyleSheet(oldStyle);
    AgregarMesas(2);
}

void CatalogoMesas::on_btnOcupado_clicked()
{
    borrar();
    QString newStyle = "*{background-color: rgb(255, 255, 255);"
                    "border: 2px solid rgb(255,255,255);"
                    "border-bottom-color: gray;}";
    QString oldStyle = "*{background-color: rgb(255, 255, 255);"
                       "border: 2px solid rgb(255,255,255);}";
    ui->btnTodos->setStyleSheet(oldStyle);
    ui->btnLibre->setStyleSheet(oldStyle);
    ui->btnOcupado->setStyleSheet(newStyle);
    AgregarMesas(3);
}

void CatalogoMesas::on_btn1_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "1");
}

void CatalogoMesas::on_btn2_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "2");
}

void CatalogoMesas::on_btn3_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "3");
}

void CatalogoMesas::on_btn4_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "4");
}

void CatalogoMesas::on_btn5_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "5");
}

void CatalogoMesas::on_btn6_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "6");
}

void CatalogoMesas::on_btn7_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "7");
}

void CatalogoMesas::on_btn8_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "8");
}

void CatalogoMesas::on_btn9_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "9");
}

void CatalogoMesas::on_btn0_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "0");
}


void CatalogoMesas::on_btnDel_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    int tam = actual.length();
    actual.remove(tam-1,1);
    ui->lineEdit_Entrada->setText(actual);
}

void CatalogoMesas::on_btnAbrirMesa_clicked()
{
     //padre->cambiarStacked_indice(1);
    if(ui->label_nMesa->text() == "Numero de Mesa")
    {
        QMessageBox::warning(this, tr("No Seleccionado"),
                   tr("Por favor, selecciona una mesa para abrirla"));
           return;
    }
    else
    {
        if(ui->lineEdit_Entrada->text().isEmpty())
        {
            QMessageBox::warning(this, tr("Campo Vacío"),
                       tr("Por favor, ingresa el número de mesero"));
               return;
        }
        else
        {
            QString hora = QTime::currentTime().toString("hh:mm");
            QString User = ui->lineEdit_Entrada->text();
            nMesa = ui->label_nMesa->text();
            QString script = "INSERT INTO Comanda(hora_apertura,numero_personas,Usuario_clave,Mesa_numero_mesa) "
                             "VALUES ('"+hora+"',"+nPersonas+","+User+","+nMesa+")";
            QSqlQuery query(mDatabase);
            query.prepare(script);
            if(query.exec()){
                nComanda = query.lastInsertId().toInt();
                //padre->cambiarStacked_indice(1);
            }
            else{
                QMessageBox::warning(this, tr("Error"), "La comanda no se ha registrado, error.");
            }
            QString newStyle = "*{background-color: rgb(255, 255, 255);"
                            "border: 2px solid rgb(255,255,255);"
                            "border-bottom-color: gray;}";
            QString oldStyle = "*{background-color: rgb(255, 255, 255);"
                               "border: 2px solid rgb(255,255,255);}";
            ui->btnTodos->setStyleSheet(newStyle);
            ui->btnLibre->setStyleSheet(oldStyle);
            ui->btnOcupado->setStyleSheet(oldStyle);
            AgregarMesas(1);
            ui->lineEdit_Entrada->clear();
            ui->label_nMesa->setText("Numero de Mesa");
            QSqlQuery query2(mDatabase);
            query2.prepare("UPDATE mesa SET estado = 'Ocupada' WHERE numero_mesa = "+nMesa+"");
            query2.exec();

        }
    }
}

void CatalogoMesas::seleccionarMesa()
{
    QPushButton * btn = qobject_cast<QPushButton *>(sender());
    QString num = btn->text();
    ui->label_nMesa->setText("Numero de Mesa: " + num);
    QString oldStyle = "*{background-color: rgb(225, 225, 225);"
                     " border:1px solid black;"
                       "padding: 0 8px;"
                     "border-radius: 10px; padding: 0 8px; }"
                     "QPushButton:hover { border: 2px solid  #66c011; }";
    QString newStyle = "*{background-color: rgb(225, 225, 225);"
                     " border:4px solid rgb(70, 176, 75);"
                     "border-radius: 10px; padding: 0 8px; }";
    if(btn->styleSheet() == oldStyle)
    {
        btn->setStyleSheet(newStyle);
        bool ok;
        QInputDialog InpDia;
        int n = InpDia.getInt(this,tr("Por favor,Ingresa Un Numero de Personas"),tr("Numero"),1,1,10,1,&ok);
        nPersonas = QString::number(n);
        btn->setStyleSheet(oldStyle);
    }
}

void CatalogoMesas::limpia(QLayout *layout)
{
    if(!layout)
        return;

    while(auto item = layout->takeAt(0))
    {
        delete item->widget();
        limpia(item->layout());
    }

}

void CatalogoMesas::borrar()
{
    limpia(ui->gridLayout_3);
}

QString CatalogoMesas::getNumMesa()
{
    return nMesa;
}
