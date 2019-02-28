#ifndef DATABASE_H
#define DATABASE_H
#include <QDebug>
#include <QtSql>
#include <QSqlQuery>
#include <QFile>
#include <QSqlError>
#include <exception>

struct DataBaseError: public std::runtime_error
{DataBaseError(const char* str);};

class DataBase
{
    QSqlDatabase _db;

    void create_boosteddecisiontree();
    void create_kneighborsclassifier();
    void create_logisticregressor();
    void create_main();
    void create_mlpregressor();
    void create_randomforest();
    void create_supportvectormachines();
    void createEmptyDataBase();
    void open();


    QSqlQuery selectParams(const QString& clf_name, int classifierId, const QString& params);

public:
    DataBase(QString filepath = "clf_v0.sqlite", bool create_if_not_exist = false);
    const QSqlDatabase& database(){return _db;}

    int addClassifier(const QString& clf_name, const QString& model, const QString& scaler, const QString& params = "");
    int addBoostedDecisionTree(const QString& model, const QString& scaler, const QString& boostType, int weakCount);
    int addKNeighborsClassifier(const QString& model, const QString& scaler, const QString& algType, int defaultK);
    int addLogisticRegressor(const QString& model, const QString& scaler, int iterations,double learningRate,const QString& regularizationType);
    int addMLPRegressor(const QString& model, const QString& scaler, const QString& layerSizes);
    int addRandomForest(const QString& model, const QString& scaler, int treesCount);
    int addSupportVectorMachines(const QString& model, const QString& scaler, const QString& kernelType, double C, double Gamma, double Coef0, double degree, bool inv);

    void addStatistics(int mainId, double Accuracy, double Sensetivity, double Specificity);
    void getStatistics(int mainId, double& Accuracy, double& Sensetivity, double& Specificity);

    void addSampleValues(int mainId, int TrainPos, int TrainNeg, int TestPos, int TestNeg);
    void getSampleValues(int mainId, int& TrainPos, int& TrainNeg, int& TestPos, int& TestNeg);

    int main2classifierID(int mainId);
    QString getClassifierName(int mainId);
    int classifier2mainID(const QString &clf_name, int classifierId);

    bool removeClassifier(int mainId);
    QString getClassifier(const QString& clf_name, int classifierId);
    QString getClassifier(int mainId);
    QString getBoostedDecisionTree(int classifierId, QString& boostType, int& weakCount);
    QString getKNeighborsClassifier(int classifierId, QString& algType, int& defaultK);
    QString getLogisticRegressor(int classifierId, int& iterations, double& learningRate, QString& regularizationType);
    QString getMLPRegressor(int classifierId, QString& layerSizes);
    QString getRandomForest(int classifierId, int& treesCount);
    QString getSupportVectorMachines(int classifierId, QString& kernelType, double& C, double& Gamma, double& Coef0, double& degree, bool& inv);
    QString getScaler(const QString& clf_name, int classifierId);
    QString getScaler(int mainId);
    QVector<int> selectMainIds(QString where_condition = "");
    QSqlQuery selectMainWithoutIDs();
    void close();
    ~DataBase();
};

#endif // DATABASE_H
