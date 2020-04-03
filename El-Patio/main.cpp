#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>

int main(int argc, char *argv[])
{
    QSqlDatabase mDatabase;
    mDatabase = QSqlDatabase::addDatabase("QODBC","Connection");
    mDatabase.setDatabaseName("elpatio");

    QFile stylesheet(":/iconos/resources/Styles.qss");

    QApplication a(argc, argv);
    stylesheet.open(QFile::ReadOnly);
    QString stylestr = QLatin1String(stylesheet.readAll());
    a.setStyleSheet(stylestr);
    stylesheet.close();

    MainWindow w;
    w.show();

    return a.exec();
}
