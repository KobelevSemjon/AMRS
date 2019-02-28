#include "database.h"

DataBaseError::DataBaseError(const char *str):std::runtime_error(str){}

void DataBase::create_boosteddecisiontree()
{
    QSqlQuery query(
                "CREATE TABLE boosteddecisiontree ( "
                "boosteddecisiontreeId INTEGER    PRIMARY KEY, "
                "model                 TEXT, "
                "scaler                TEXT, "
                "boostType             STRING, "
                "weakCount             INT, "
                "mainId                INTEGER    REFERENCES main (mainId) "
                ");");
    query.exec();
}

void DataBase::create_kneighborsclassifier()
{
    QSqlQuery query("CREATE TABLE kneighborsclassifier ( "
                    "kneighborsclassifierId INTEGER    PRIMARY KEY, "
                    "model                  TEXT, "
                    "scaler                 TEXT, "
                    "algType                STRING, "
                    "defaultK               INT, "
                    "mainId                 INTEGER REFERENCES main (mainId)"
                    ");");
    query.exec();
}

void DataBase::create_logisticregressor()
{
    QSqlQuery query(
                "CREATE TABLE logisticregressor ("
                "logisticregressorId INTEGER    PRIMARY KEY, "
                "model               TEXT, "
                "scaler              TEXT, "
                "iterations          INT, "
                "learningRate        DOUBLE, "
                "regularizationType  STRING, "
                "mainId              INTEGER    REFERENCES main (mainId)"
                ");");
    query.exec();
}

void DataBase::create_main()
{
    QSqlQuery query(
                "CREATE TABLE main ( "
                "mainId         INTEGER    PRIMARY KEY, "
                "ClassifierName STRING, "
                "Accuracy       DOUBLE, "
                "Sensitivity    DOUBLE, "
                "Specificity    DOUBLE, "
                "TrainPos       INTEGER, "
                "TrainNeg       INTEGER, "
                "TestPos        INTEGER, "
                "TestNeg        INTEGER, "
                "classifierId   INTEGER "
                ");");
    query.exec();
}

void DataBase::create_mlpregressor()
{
    QSqlQuery query(
                "CREATE TABLE mlpregressor ("
                "mlpregressorId INTEGER    PRIMARY KEY,"
                "model          TEXT,"
                "scaler         TEXT, "
                "layerSizes     STRING,"
                "mainId         INTEGER    REFERENCES main (mainId)"
                ");");
    query.exec();
}

void DataBase::create_randomforest()
{
    QSqlQuery query("CREATE TABLE randomforest ( "
                    "randomforestId INTEGER  PRIMARY KEY, "
                    "model          TEXT, "
                    "scaler         TEXT, "
                    "treesCount     INT, "
                    "mainId         INTEGER  REFERENCES main (mainId) "
                    ");");
    query.exec();
}

void DataBase::create_supportvectormachines()
{
    QSqlQuery query("CREATE TABLE supportvectormachines ( "
                    "supportvectormachinesId INTEGER  PRIMARY KEY, "
                    "model          TEXT, "
                    "scaler         TEXT, "
                    "kernelType     STRING, "
                    "C              DOUBLE, "        
                    "Gamma          DOUBLE, "
                    "Coef0          DOUBLE, "
                    "degree         DOUBLE, "
                    "inv            BOOL, "
                    "mainId         INTEGER  REFERENCES main (mainId) "
                    ");");
    query.exec();
}

void DataBase::open()
{
    if (!_db.open())
    {
        qDebug() << _db.lastError().text();
        throw DataBaseError("\n in DataBase()");
    }
}

DataBase::DataBase(QString filepath, bool create_if_not_exist)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(filepath);
    bool isExist = QFile::exists(filepath);
    if (isExist) open();
    else if (create_if_not_exist)
    {
        open();
        createEmptyDataBase();
    }
    else throw DataBaseError("\n filepath doesn't exist \n in DataBase()");
}

int DataBase::addClassifier(const QString &clf_name, const QString &model, const QString& scaler, const QString &params)
{
    QString query1 = QString("INSERT INTO %1(model, scaler) VALUES ('%2','%3');")
            .arg(clf_name).arg(model).arg(scaler);
    int classifierId = QSqlQuery(query1).lastInsertId().toInt();

    QString query2 = QString("INSERT INTO main(ClassifierName, classifierId) VALUES ('%1', %2);")
            .arg(clf_name).arg(classifierId);
    int mainId = QSqlQuery(query2).lastInsertId().toInt();

    if (params!="")
    {
        QString query3 = QString("UPDATE %1 SET mainId = %2, %3 WHERE %4 = %5;")
                .arg(clf_name).arg(mainId).arg(params).arg(clf_name+"Id").arg(classifierId);
        QSqlQuery(query3).exec();
    }
    else {
        QString query3 = QString("UPDATE %1 SET mainId = %2 WHERE %4 = %5;")
                .arg(clf_name).arg(mainId).arg(clf_name+"Id").arg(classifierId);
        QSqlQuery(query3).exec();
    }

    return mainId;
}

int DataBase::addBoostedDecisionTree(const QString &model, const QString& scaler, const QString &boostType, int weakCount)
{
    QString ClassifierName = "boosteddecisiontree";
    QString params = QString("boostType = '%1', weakCount = %2").arg(boostType).arg(weakCount);
    int mainId = addClassifier(ClassifierName,model,scaler,params);
    return mainId;
}

int DataBase::addKNeighborsClassifier(const QString &model, const QString& scaler, const QString &algType, int defaultK)
{
    QString ClassifierName = "kneighborsclassifier";
    QString params = QString("algType = '%1', defaultK = %2").arg(algType).arg(defaultK);
    int mainId = addClassifier(ClassifierName,model,scaler,params);
    return mainId;
}

int DataBase::addLogisticRegressor(const QString &model, const QString& scaler, int iterations, double learningRate, const QString &regularizationType)
{
    QString ClassifierName = "logisticregressor";
    QString params = QString("iterations = %1, learningRate = %2, regularizationType ='%3'")
            .arg(iterations)
            .arg(learningRate)
            .arg(regularizationType);
    int mainId = addClassifier(ClassifierName,model,scaler,params);
    return mainId;
}

int DataBase::addMLPRegressor(const QString &model, const QString& scaler, const QString &layerSizes)
{
    QString ClassifierName = "mlpregressor";
    QString params = QString("layerSizes = '%1'")
            .arg(layerSizes);
    int mainId = addClassifier(ClassifierName,model,scaler, params);
    return mainId;
}

int DataBase::addRandomForest(const QString &model, const QString& scaler, int treesCount)
{
    QString ClassifierName = "randomforest";
    QString params = QString("treesCount = %1")
            .arg(treesCount);
    int mainId = addClassifier(ClassifierName,model,scaler,params);
    return mainId;
}

int DataBase::addSupportVectorMachines(const QString &model, const QString& scaler, const QString &kernelType, double C, double Gamma, double Coef0, double degree, bool inv)
{
    QString ClassifierName = "supportvectormachines";
    QString params = QString("kernelType = '%1', C = %2, Gamma = %3, Coef0 = %4, degree = %5, inv = %6")
            .arg(kernelType).arg(C).arg(Gamma).arg(Coef0).arg(degree).arg(inv);
    int mainId = addClassifier(ClassifierName,model,scaler,params);
    return mainId;
}

void DataBase::addStatistics(int mainId, double Accuracy, double Sensitivity, double Specificity)
{
    QString query = QString("UPDATE main \n"
                  "SET Accuracy = %1, Sensitivity = %2, Specificity = %3 \n"
                  "WHERE mainId = %4;")
            .arg(Accuracy).arg(Sensitivity).arg(Specificity).arg(mainId);
    QSqlQuery(query).exec();
}

void DataBase::getStatistics(int mainId, double &Accuracy, double &Sensetivity, double &Specificity)
{

    QString text = QString("SELECT Accuracy, Sensitivity, Specificity \n"
                  "FROM main \n"
                  "WHERE mainId = %1;").arg(mainId);
    QSqlQuery query(text);
    if (query.exec())
    {
        query.next();
        Accuracy =  query.value(0).toDouble();
        Sensetivity =  query.value(1).toDouble();
        Specificity =  query.value(2).toDouble();
    }
    else Accuracy = Sensetivity = Specificity = -1;
}

void DataBase::addSampleValues(int mainId, int TrainPos, int TrainNeg, int TestPos, int TestNeg)
{
    QString query = QString("UPDATE main \n"
                  "SET TrainPos = %1, TrainNeg = %2, TestPos = %3, TestNeg = %4 \n"
                  "WHERE mainId = %5;")
            .arg(TrainPos).arg(TrainNeg).arg(TestPos).arg(TestNeg).arg(mainId);
    QSqlQuery(query).exec();
}
void DataBase::getSampleValues(int mainId, int& TrainPos, int& TrainNeg, int& TestPos, int& TestNeg)
{

    QString text = QString("SELECT TrainPos, TrainNeg, TestPos, TestNeg \n"
                  "FROM main \n"
                  "WHERE mainId = %1;").arg(mainId);
    QSqlQuery query(text);
    if (query.exec())
    {
        query.next();
        TrainPos =  query.value(0).toInt();
        TrainNeg =  query.value(1).toInt();
        TestPos =  query.value(2).toInt();
        TestNeg =  query.value(3).toInt();
    }
    else TrainPos = TrainNeg = TestPos = TestNeg = -1;
}

//! \todo нужна проверка на существование mainId
int DataBase::main2classifierID(int mainId)
{   
    QString text = QString("SELECT classifierId \n"
                  "FROM main \n"
                  "WHERE mainId = %1;").arg(mainId);
    QSqlQuery query(text);
    if (query.exec())
    {
        query.next();
        return query.value(0).toInt();
    }
    return -1;
}

QString DataBase::getClassifierName(int mainId)
{
    QString text = QString("SELECT ClassifierName FROM main WHERE mainId = %1;")
            .arg(mainId);
    QSqlQuery query(text);
    query.next();
    return query.value(0).toString();
}
//! \todo нужна проверка на существование classifierId
int DataBase::classifier2mainID(const QString &clf_name, int classifierId)
{
    QString text = QString("SELECT mainId FROM %1 WHERE %2 = %3;")
            .arg(clf_name).arg(clf_name+"Id").arg(classifierId);

    QSqlQuery query(text);
    if (query.exec())
    {
        query.next();
        return query.value(0).toInt();
    }
    return -1;
}

bool DataBase::removeClassifier(int mainId)
{

    QString text1 = QString("SELECT ClassifierName, classifierId\n"
                   "FROM main\n"
                   "WHERE mainId = %1;").arg(mainId);
    QSqlQuery query1(text1);
    bool is_exist = query1.exec();
    if (is_exist)
    {
        query1.next();
        QString ClassifierName = query1.value(0).toString();
        int classifierId = query1.value(0).toInt();

        QString text2 = QString("DELETE FROM main WHERE mainId = %1;").arg(mainId);
        QSqlQuery(text2).exec();

        QString text3 = QString("DELETE FROM %1 WHERE %2 = %3;")
                .arg(ClassifierName).arg(ClassifierName+"Id").arg(classifierId);
        QSqlQuery(text3).exec();
    }

    return is_exist;
}

QString DataBase::getClassifier(const QString &clf_name, int classifierId)
{

    QString text = QString("SELECT model FROM %1 WHERE %2 = %3;")
            .arg(clf_name).arg(clf_name+"Id").arg(classifierId);
    QSqlQuery query(text);
    if (!query.exec()) return QString();
    query.next();
    return query.value(0).toString();
}

QString DataBase::getClassifier(int mainId)
{
    auto ClassifierName = getClassifierName(mainId);
    auto classifierId = main2classifierID(mainId);
    return getClassifier(ClassifierName, classifierId);
}

QString DataBase::getScaler(const QString &clf_name, int classifierId)
{
    QString text = QString("SELECT scaler FROM %1 WHERE %2 = %3;")
            .arg(clf_name).arg(clf_name+"Id").arg(classifierId);
    QSqlQuery query(text);
    if (!query.exec()) return QString();
    query.next();
    return query.value(0).toString();
}

QString DataBase::getScaler(int mainId)
{
    QString clf_type = getClassifierName(mainId);
    int clf_id = main2classifierID(mainId);
    return getScaler(clf_type, clf_id);
}

QSqlQuery DataBase::selectParams(const QString& clf_name, int classifierId, const QString& params)
{
    QString text = QString("SELECT %1 FROM %2 WHERE %3 = %4;")
            .arg(params)
            .arg(clf_name)
            .arg(clf_name+"Id")
            .arg(classifierId);
    QSqlQuery query(text);
    if (query.exec()) query.next();
    return query;
}


QString DataBase::getBoostedDecisionTree(int classifierId, QString &boostType, int &weakCount)
{
    QString ClassifierName = "boosteddecisiontree";
    QSqlQuery query = selectParams(ClassifierName, classifierId, QString("boostType,weakCount"));
    boostType = query.value(0).toString();
    weakCount = query.value(1).toInt();
    return getClassifier(ClassifierName, classifierId);
}

QString DataBase::getKNeighborsClassifier(int classifierId, QString &algType, int &defaultK)
{
    QString ClassifierName = "kneighborsclassifier";
    QSqlQuery query = selectParams(ClassifierName, classifierId, QString("algType, defaultK"));
    algType = query.value(0).toString();
    defaultK = query.value(1).toInt();
    return getClassifier(ClassifierName, classifierId);
}

QString DataBase::getLogisticRegressor(int classifierId, int &iterations, double &learningRate, QString &regularizationType)
{
    QString ClassifierName = "logisticregressor";
    QSqlQuery query = selectParams(ClassifierName, classifierId, QString("iterations, learningRate, regularizationType"));
    iterations = query.value(0).toInt();
    learningRate = query.value(1).toDouble();
    regularizationType = query.value(2).toString();
    return getClassifier(ClassifierName, classifierId);
}

QString DataBase::getMLPRegressor(int classifierId, QString &layerSizes)
{
    QString ClassifierName = "mlpregressor";
    QSqlQuery query = selectParams(ClassifierName, classifierId, QString("layerSizes"));
    layerSizes = query.value(0).toString();
    return getClassifier(ClassifierName, classifierId);
}

QString DataBase::getRandomForest(int classifierId, int &treesCount)
{
    QString ClassifierName = "randomforest";
    QSqlQuery query = selectParams(ClassifierName, classifierId, QString("treesCount"));
    treesCount = query.value(0).toInt();
    return getClassifier(ClassifierName, classifierId);
}

QString DataBase::getSupportVectorMachines(int classifierId, QString &kernelType, double &C, double &Gamma, double &Coef0, double &degree, bool &inv)
{
    QString ClassifierName = "supportvectormachines";
    QSqlQuery query = selectParams(ClassifierName, classifierId, QString("kerneltype,C,Gamma,Coef0,degree,inv"));
    kernelType = query.value(0).toString();
    C = query.value(0).toDouble();
    Gamma = query.value(1).toDouble();
    Coef0 = query.value(2).toDouble();
    degree = query.value(3).toDouble();
    inv = query.value(4).toBool();
    return getClassifier(ClassifierName, classifierId);
}

QVector<int> DataBase::selectMainIds(QString where_condition)
{
    QSqlQuery query;
    query.prepare("SELECT mainId FROM main WHERE "+where_condition);
    query.exec();
    QList<int> ids;
    while(query.next())
    {
        int id = query.value(0).toInt();
        ids.push_back(id);
    }
    return ids.toVector();
}

QSqlQuery DataBase::selectMainWithoutIDs()
{
    QSqlQuery query;
    query.prepare("SELECT ClassifierName, "
                  "Accuracy, Sensitivity, Specificity, "
                  "TrainPos, TrainNeg, TestPos, TestNeg FROM main");
    return query;
}

void DataBase::close(){_db.close();}

void DataBase::createEmptyDataBase()
{
    create_main();
    create_boosteddecisiontree();
    create_kneighborsclassifier();
    create_logisticregressor();
    create_mlpregressor();
    create_randomforest();
    create_supportvectormachines();
}

DataBase::~DataBase()
{
    _db.close();
}
