#include "catalogomesas.h"
#include "ui_catalogomesas.h"
#include <QDate>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <QSpinBox>
#include <QDebug>
#include <QSqlQuery>

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
}

CatalogoMesas::~CatalogoMesas()
{
    delete ui;
}

void CatalogoMesas::AgregarMesas(int n)
{
    int nMesas;
    QString script;
    switch (n) {
    case 1:
        script = "SELECT COUNT(*) FROM Mesa";
        break;
    case 2:
        script = "SELECT COUNT(*) FROM Mesa WHERE Estado = 'libre'";
        break;
    case 3:
        script = "SELECT COUNT(*) FROM Mesa WHERE Estado = 'ocupado'";
        break;
    }

    QSqlQuery query(mDatabase);
    query.prepare(script);
    query.exec();
    //nMesas = query.value(0).toInt();
    nMesas = 10;
    QFont fuente("MS Shell Dlg 2",25,4,false);
    QString estilo = "*{background-color: rgb(225, 225, 225);"
                      " border:2px solid rgb(225, 225, 225);"
                      "border-radius: 10px; padding: 0 8px; }"
                      "QPushButton:hover { border: 2px solid  #66c011; }";

    for(int i = 0; i < nMesas; i++)
    {
        QPushButton * mesa = new QPushButton(this);
        mesa->setText(QString::number(i+1));
        mesa->setMinimumWidth(150);
        mesa->setMinimumHeight(150);
        mesa->setFont(fuente);
        mesa->show();
        mesa->setStyleSheet(estilo);
        ui->gridLayout_6->addWidget(mesa,i/4, i%4);
        connect(mesa,SIGNAL(clicked()), this, SLOT(seleccionarMesa()));
    }
}


void CatalogoMesas::on_btnTodos_clicked()
{
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
    QString newStyle = "*{background-color: rgb(255, 255, 255);"
                    "border: 2px solid rgb(255,255,255);"
                    "border-bottom-color: gray;}";
    QString oldStyle = "*{background-color: rgb(255, 255, 255);"
                       "border: 2px solid rgb(255,255,255);}";
    ui->btnTodos->setStyleSheet(oldStyle);
    ui->btnLibre->setStyleSheet(newStyle);
    ui->btnOcupado->setStyleSheet(oldStyle);
    AgregarMesas(1);
}

void CatalogoMesas::on_btnOcupado_clicked()
{
    QString newStyle = "*{background-color: rgb(255, 255, 255);"
                    "border: 2px solid rgb(255,255,255);"
                    "border-bottom-color: gray;}";
    QString oldStyle = "*{background-color: rgb(255, 255, 255);"
                       "border: 2px solid rgb(255,255,255);}";
    ui->btnTodos->setStyleSheet(oldStyle);
    ui->btnLibre->setStyleSheet(oldStyle);
    ui->btnOcupado->setStyleSheet(newStyle);
    AgregarMesas(1);
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
                       tr("Por favor, ingresa el número de personas que ocuparán la mesa"));
               return;
        }
        else
        {
            QString hora = QTime::currentTime().toString("hh:mm");
            QString User = ui->lineEdit_Entrada->text();
            QString mesa = ui->label_nMesa->text();
            QString script = "INSERT INTO Comanda(hora_apertura,numero_personas,Usuario_clave,Mesa_numero_mesa) "
                             "VALUES ('"+hora+"',"+nPersonas+","+User+","+mesa+")";
            QSqlQuery query(mDatabase);
            query.prepare(script);
            query.exec();
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
            query2.prepare("UPDATE mesa SET estado = 'Ocupada' WHERE numero_mesa = '"+mesa+"'");
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
                     " border:2px solid rgb(225, 225, 225);"
                     "border-radius: 10px; padding: 0 8px; }"
                     "QPushButton:hover { border: 2px solid  #66c011; }";
    QString newStyle = "*{background-color: rgb(225, 225, 225);"
                     " border:4px solid rgb(70, 176, 75);"
                     "border-radius: 10px; padding: 0 8px; }";
    if(btn->styleSheet() == oldStyle)
    {
        btn->setStyleSheet(newStyle);
        bool ok;

        int n = QInputDialog::getInt(this,tr("Por favor,Ingresa Un Numero de Personas"),tr("Numero"),1,1,10,1,&ok);
        nPersonas = QString::number(n);
        btn->setStyleSheet(oldStyle);
    }
}
