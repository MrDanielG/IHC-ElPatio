#include <QtTest>
#include <QSqlDatabase>
#include <QSqlQuery>

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
    /*void calculaPropina();
    void agregarPropina();
    void addUser();
    void verifyUserAdd();
    void showUsers();
    void usuario();
    void setEstado();
    void validaEstado();
    void modificarUsuario();
    void eliminarUsuario();
    void verificaEliminado();*/
    void platillosDisponibles();
    void listarIngredientes();
    void getPlatillo();
    void getCategorias();
    void getIngredientes();
    void cambiaPlatillo();
    void verificaCambio();
    void quitarIngredientes();
    void verificaQuitados();
    void insertaIngrediente();
    void verificaInsertado();
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

void Pruebas_ElPatio::platillosDisponibles()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT * FROM `platillo` WHERE estado = 'disponible'";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::listarIngredientes()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT ingrediente.id_ingrediente,"
                     " ingrediente.nombre FROM ingrediente"
                     " INNER JOIN lista_ingrediente ON"
                     " ingrediente.id_ingrediente ="
                     " lista_ingrediente.id_ingrediente"
                     " INNER JOIN platillo ON platillo.id_platillo"
                     " = lista_ingrediente.id_platillo"
                     " WHERE platillo.id_platillo = 1";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::getPlatillo()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT * FROM `platillo` WHERE id_platillo = 1";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::getCategorias()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT categoria FROM platillo GROUP BY categoria";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::getIngredientes()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT * FROM ingrediente ORDER BY nombre";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::cambiaPlatillo()
{
    QSqlQuery query(mDatabase);
    QString script = "UPDATE platillo SET precio"
                     " = '100' ,nombre = 'Con jamon,"
                     " tocino, salchicha y longaniza',"
                     " categoria = 'Huevos',"
                     " estado = 'disponible',"
                     " foto = null WHERE id_platillo = 1";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::verificaCambio()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT precio FROM platillo WHERE id_platillo = 1";
    query.prepare(script);
    query.exec();
    QString aux = "";
    while(query.next())
        aux = query.value(0).toString();
    query.finish();
    QCOMPARE("100",aux);
}

void Pruebas_ElPatio::quitarIngredientes()
{
    QSqlQuery query(mDatabase);
    QString script = "DELETE FROM lista_ingrediente WHERE id_platillo = 1";
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::verificaQuitados()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT * FROM lista_ingrediente WHERE id_platillo = 1";
    query.prepare(script);
    query.exec();
    QString aux = "";
    while(query.next())
        aux = query.value(0).toString();
    query.finish();
    QCOMPARE("",aux);
}

void Pruebas_ElPatio::insertaIngrediente()
{
    QSqlQuery query(mDatabase);
    QString script = "INSERT INTO lista_ingrediente ( id_platillo, id_ingrediente) VALUES ";
    for(int i = 4; i < 8; i++)
    {
        if(i != 7)
            script = script + "(1 ," + QString::number(i) + "),";
        else
            script = script + "(1 ," + QString::number(i) + ")";
    }
    query.prepare(script);
    QVERIFY(query.exec());
    query.finish();
}

void Pruebas_ElPatio::verificaInsertado()
{
    QSqlQuery query(mDatabase);
    QString script = "SELECT id_elemento_lista FROM lista_ingrediente";
    query.prepare(script);
    query.exec();
    QString aux = "";
    query.next();
    aux = query.value(0).toString();
    QString variant = query.lastInsertId().toString();
    query.finish();
    QCOMPARE(variant, aux);
}

/*void Pruebas_ElPatio::calculaPropina()
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
*/


QTEST_APPLESS_MAIN(Pruebas_ElPatio)

#include "tst_pruebas_elpatio.moc"
