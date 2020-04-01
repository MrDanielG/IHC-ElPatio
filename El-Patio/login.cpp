#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <mainwindow.h>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->padre = qobject_cast<MainWindow*>(parent); //Casteo de QWidget a MainWindow
    conexionBD();
}

login::~login()
{
    delete ui;
}

void login::conexionBD()
{
    mDatabase = QSqlDatabase::database("Connection");
    if(!mDatabase.isOpen()){
        qDebug()<<"ERROR, LOGIN";
    }
}

void login::on_btn1_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "1");
}

void login::on_btn2_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "2");
}

void login::on_btn3_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "3");
}

void login::on_btn4_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "4");
}

void login::on_btn5_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "5");
}

void login::on_btn6_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "6");
}

void login::on_btn7_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "7");
}

void login::on_btn8_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "8");
}

void login::on_btn9_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "9");
}

void login::on_btn0_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    ui->lineEdit_Entrada->setText(actual + "0");
}

void login::on_btnDel_clicked()
{
    QString actual = ui->lineEdit_Entrada->text();
    int tam = actual.length();
    actual.remove(tam-1,1);
    ui->lineEdit_Entrada->setText(actual);
}

void login::on_btnPrimario_clicked()
{
    QString claveActual = ui->lineEdit_Entrada->text();

    QSqlQuery verificarUsuario(mDatabase);
    verificarUsuario.prepare("SELECT * FROM `usuario` WHERE clave = " + claveActual);
    verificarUsuario.exec();
    verificarUsuario.next();

    QString claveUsuario = verificarUsuario.value("clave").toString();
    QString tipoUsuario = verificarUsuario.value("Tipo_id_tipo").toString();

    if(!claveUsuario.isEmpty()){
        switch (tipoUsuario.toInt()) {
        case 1:
            qDebug()<<"Admin";
            this->padre->cambiar_pagina(7);
            break;

        case 2:
            qDebug()<<"Mesero";
            break;

        case 3:
            qDebug()<<"Cocinero";
            break;

        case 4:
            qDebug()<<"Barista";
            break;

        case 5:
            qDebug()<<"Almacenista";
            break;

        default:
            qDebug()<<"Error al detectar Usuario";
            break;
        }

    } else {
        QMessageBox::warning(this, tr("Error"),
            " Clave de Usuario Incorrecta o Usuario Inexistente");
        ui->lineEdit_Entrada->clear();
    }
}
