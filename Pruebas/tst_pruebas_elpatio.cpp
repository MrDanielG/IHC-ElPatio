#include <QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>

// add necessary includes here

class Pruebas_ElPatio : public QObject
{
    Q_OBJECT
private:
    QSqlDatabase mDatabase;
public:
    Pruebas_ElPatio();
    ~Pruebas_ElPatio();
    int calculaPropina(int, int);
private slots:
    void test_connection();
    void calculaPropina();
    void agregarPropina();
    void addUser();
    void verifyUserAdd();
    void showUsers();
    void usuario();
    void setEstado();
    void validaEstado();
    void modificarUsuario();
    void eliminarUsuario();
    void verificaEliminado();
};

Pruebas_ElPatio::Pruebas_ElPatio()
{
    mDatabase = QSqlDatabase::addDatabase("QODBC","Connection");
    mDatabase.setDatabaseName("elpatio");
}

Pruebas_ElPatio::~Pruebas_ElPatio()
{

}

void Pruebas_ElPatio::test_connection()
{
    if(!mDatabase.open()){
        qDebug()<< "Failed";
        return;
    }else
        qDebug() << "Success";
}

void Pruebas_ElPatio::calculaPropina()
{
    int total = 100;
    int porcentaje = 10;
    QCOMPARE(calculaPropina(total,porcentaje),10);
}

void Pruebas_ElPatio::agregarPropina()
{
    int total = 100;
    int porcentaje = 10;
    QCOMPARE(calculaPropina(total,porcentaje) + total, 110);
}

void Pruebas_ElPatio::addUser()
{
    /*QLineEdit id_usuario;
    QTest::keyClicks(&id_usuario,"729431");
    */
    QSqlQuery query(mDatabase);
    QString script = "INSERT INTO `usuario`(`clave`,`apellido_paterno`, `apellido_materno`, "
                     "`nombre`, `Tipo_id_tipo`) "
                     "VALUES (200,'Perez','Hernandez','Maria',2)";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::verifyUserAdd()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT * FROM usuario WHERE clave = 200 ";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::showUsers()
{
    QString script = "SELECT * FROM usuario INNER JOIN"
                     " tipo ON usuario.Tipo_id_tipo = tipo.id_tipo";
    QSqlQuery query(mDatabase);
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::usuario()
{
    QString script = "SELECT * FROM usuario INNER JOIN"
                     " tipo ON usuario.Tipo_id_tipo = tipo.id_tipo"
                     " WHERE usuario.clave = 200";
    QSqlQuery query(mDatabase);
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::setEstado()
{
    QString script = "UPDATE usuario SET estado = 'ACTIVO' WHERE clave = 200";
    QSqlQuery query(mDatabase);
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::validaEstado()
{
    QString script = "SELECT estado FROM usuario WHERE clave = 200";
    QSqlQuery query(mDatabase);
    query.prepare(script);
    QString res;
    query.exec();
    while(query.next())
        res = query.value(0).toString();
    query.finish();
    QCOMPARE("ACTIVO",res);
}

void Pruebas_ElPatio::modificarUsuario()
{
    QSqlQuery query(mDatabase);
    QString script = "UPDATE usuario SET "
                   "clave = 200, "
                   "apellido_paterno = 'Gomez', "
                   "apellido_materno = 'Fernandez', "
                   "nombre = 'Maria', "
                   "Tipo_id_tipo = 2 "
                   "WHERE clave = 200;";
    query.prepare(script);
    QVERIFY(query.exec());
}

void Pruebas_ElPatio::eliminarUsuario()
{
    QSqlQuery query(mDatabase);
    QString script = "DELETE FROM usuario WHERE clave = 200";
    query.prepare(script);
    QVERIFY(query.exec());
}

void Pruebas_ElPatio::verificaEliminado()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT * FROM usuario WHERE clave = 200";
    query.prepare(script);
    QString res;
    query.exec();
    while(query.next())
        res = query.value(0).toString();
    QCOMPARE(res, "");
}

int Pruebas_ElPatio::calculaPropina(int n, int p)
{
    return (n * p) / 100;
}

QTEST_APPLESS_MAIN(Pruebas_ElPatio)

#include "tst_pruebas_elpatio.moc"
