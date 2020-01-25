#include "catalogomesas.h"|
#include "ui_catalogomesas.h"
#include <QDate>

CatalogoMesas::CatalogoMesas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CatalogoMesas)
{
    ui->setupUi(this);
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

    /*QSqlQuery query(mDatabase);
    query.prepare(script);
    query.exec();
    nMesas = query.value(0);*/

    QFont fuente("MS Shell Dlg 2",25,4,false);
    QString estilo = "*{background-color: rgb(225, 225, 225);"
                     " border:2px solid rgb(225, 225, 225);"
                     "border-radius: 10px; padding: 0 8px; }"
                     "QPushButton:hover { border: 4px solid  #66c011; }";

    //En lugar de 25, debe ser el numero de mesas obtenido de la base (nMesas)
    for(int i = 0; i < 25; i++)
    {
        QPushButton * mesa = new QPushButton(this);
        mesa->setText(QString::number(i+1));
        mesa->setMinimumWidth(150);
        mesa->setMinimumHeight(150);
        mesa->setFont(fuente);
        mesa->show();
        mesa->setStyleSheet(estilo);
        ui->gridLayout_6->addWidget(mesa,i/4, i%4);
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

void CatalogoMesas::on_btnP_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + ".");
}

void CatalogoMesas::on_btnAbrirMesa_clicked()
{

}
