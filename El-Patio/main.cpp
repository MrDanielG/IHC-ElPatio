#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QSqlDatabase mDatabase;
    mDatabase = QSqlDatabase::addDatabase("QODBC","Connection");
    mDatabase.setDatabaseName("elpatio");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
