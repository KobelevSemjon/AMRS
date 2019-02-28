#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>
#include <QFile>
#include <QSqlError>
#include <exception>
/*! \defgroup DataBase - Модуль базы данных.
 */
//! \ingroup DataBase
struct DataBaseError: public std::runtime_error
{DataBaseError(const char* str);};

//! \ingroup DataBase
class DataBase
{
    QSqlDatabase _db;

    enum CLF{BDT,KNN,LR,MLP,RF,SVM};
    QVector<QString> _clf_table_names = {"bdt","knn","lr","mlp","rf","svm"};

    void createMain();
    void createClassifierTable(QString table_name);
    void createEmptyDataBase();
    void open();

    QSqlQuery selectParams(const QString& clf_name, int classifierId, const QString& params);

public:
    DataBase(QString filepath = "clf_v0.sqlite", bool create_if_not_exist = false);
    const QSqlDatabase& database(){return _db;}

    int addClassifier(const QString& clf_name, const QString& model, const QString& scaler, const QString& params);
    QString getClassifier(const QString& clf_name, int classifierId);
    QString getClassifier(int mainId);
    bool removeClassifier(int mainId);

    bool addStatistics(int mainId, double Accuracy, double Sensetivity, double Specificity);
    void getStatistics(int mainId, double& Accuracy, double& Sensetivity, double& Specificity);

    bool addSampleValues(int mainId, int TrainPos, int TrainNeg, int TestPos, int TestNeg);
    void getSampleValues(int mainId, int& TrainPos, int& TrainNeg, int& TestPos, int& TestNeg);

    int main2classifierID(int mainId);
    QString getClassifierName(int mainId);
    int classifier2mainID(const QString &clf_name, int classifierId);

    QString getScaler(const QString& clf_name, int classifierId);
    QString getScaler(int mainId);

    QVector<int> selectMainIds(QString where_condition = "");
    QSqlQuery selectMainWithoutIDs();
    void close();
    ~DataBase();
};

#endif // DATABASE_H
