#include <QtTest>
#include <database.h>
// add necessary includes here

class TestDataBase : public QObject
{
    Q_OBJECT
    DataBase* db;
public:
    TestDataBase(){}
    ~TestDataBase(){}

private slots:
    void initTestCase();
    void addingClf();
    void cleanupTestCase();

};
void TestDataBase::initTestCase()
{
    QString data_base_path = "clf_test.sqlite";
    QFile(data_base_path).remove();
    db = new DataBase(data_base_path,true);
}
void TestDataBase::addingClf()
{
    //QCOMPARE(1, db->addMLPRegressor("{mlp}","{1,2}","{10,10}"));
    //QCOMPARE(2, db->addKNeighborsClassifier("{knn}","{1,2}","IType",3));
    //QCOMPARE(3, db->addBoostedDecisionTree("{bdt}","{1,2}","IIType",5));
    //QCOMPARE(4, db->addRandomForest("{rf}","{1,2}",50));
    //QCOMPARE(5, db->addLogisticRegressor("{rf}","{1,2}",50,0.95,"L2"));
    //QCOMPARE(6, db->addSupportVectorMachines("{rf}","{1,2}","SIGMA", 10,  1,  0,  -1,  true));
}
void TestDataBase::cleanupTestCase()
{
    delete db;
}
QTEST_APPLESS_MAIN(TestDataBase)

#include "tst_testdatabase.moc"
