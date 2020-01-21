#include <QtTest>

// add necessary includes here

class Pruebas_ElPatio : public QObject
{
    Q_OBJECT

public:
    Pruebas_ElPatio();
    ~Pruebas_ElPatio();

private slots:
    void test_case1();

};

Pruebas_ElPatio::Pruebas_ElPatio()
{

}

Pruebas_ElPatio::~Pruebas_ElPatio()
{

}

void Pruebas_ElPatio::test_case1()
{

}

QTEST_APPLESS_MAIN(Pruebas_ElPatio)

#include "tst_pruebas_elpatio.moc"
