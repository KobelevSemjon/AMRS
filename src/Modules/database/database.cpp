#include "database.h"

DataBaseError::DataBaseError(const char *str):std::runtime_error(str){}
void DataBase::createMain()
{
    QSqlQuery query(
                "CREATE TABLE main ( "
                "mainId         INTEGER    PRIMARY KEY, "
                "Type           STRING, "
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
void DataBase::createClassifierTable(QString table_name)
{
    QString text_query = QString("CREATE TABLE %1 ( "
                         "%2Id      INTEGER    PRIMARY KEY, "
                         "model      TEXT, "
                         "scaler     TEXT, "
                         "params     TEXT, "
                         "mainId     INTEGER    REFERENCES main (mainId) "
                         ");").arg(table_name).arg(table_name);
    QSqlQuery(text_query).exec();
}

void DataBase::createEmptyDataBase()
{
    createMain();
    for(auto name: _clf_table_names)
        createClassifierTable(name);
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
    QString query1 = QString("INSERT INTO %1(model, scaler, params) VALUES ('%2','%3','%4');")
            .arg(clf_name).arg(model).arg(scaler).arg(params);
    int classifierId = QSqlQuery(query1).lastInsertId().toInt();

    QString query2 = QString("INSERT INTO main(Type, classifierId) VALUES ('%1', %2);")
            .arg(clf_name).arg(classifierId);
    int mainId = QSqlQuery(query2).lastInsertId().toInt();

    QString query3 = QString("UPDATE %1 SET mainId = %2 WHERE %3 = %4;")
            .arg(clf_name).arg(mainId).arg(clf_name+"Id").arg(classifierId);
    QSqlQuery(query3).exec();

    return mainId;
}

bool DataBase::addStatistics(int mainId, double Accuracy, double Sensitivity, double Specificity)
{
    QString query = QString("UPDATE main SET Accuracy = %1, Sensitivity= %2, Specificity = %3 WHERE mainId = %4;")
            .arg(Accuracy).arg(Sensitivity).arg(Specificity).arg(mainId);
    return QSqlQuery(query).exec();
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

bool DataBase::addSampleValues(int mainId, int TrainPos, int TrainNeg, int TestPos, int TestNeg)
{
    QString query = QString("UPDATE main \n"
                  "SET TrainPos = %1, TrainNeg = %2, TestPos = %3, TestNeg = %4 \n"
                  "WHERE mainId = %5;")
            .arg(TrainPos).arg(TrainNeg).arg(TestPos).arg(TestNeg).arg(mainId);
    return QSqlQuery(query).exec();
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
    QString text = QString("SELECT Type FROM main WHERE mainId = %1;")
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
    QString text1 = QString("SELECT Type, classifierId\n"
                   "FROM main\n"
                   "WHERE mainId = %1;").arg(mainId);
    QSqlQuery query1(text1);
    bool is_exist = query1.exec();
    if (is_exist)
    {
        query1.next();
        QString clf_name = query1.value(0).toString();
        int classifierId = query1.value(1).toInt();

        QString text2 = QString("DELETE FROM main WHERE mainId = %1;").arg(mainId);
        QSqlQuery(text2).exec();

        QString text3 = QString("DELETE FROM %1 WHERE %2 = %3;")
                .arg(clf_name).arg(clf_name+"Id").arg(classifierId);
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
    query.prepare("SELECT Type, "
                  "Accuracy, Sensitivity, Specificity, "
                  "TrainPos, TrainNeg, TestPos, TestNeg FROM main");
    return query;
}

void DataBase::close(){_db.close();}



DataBase::~DataBase()
{
    _db.close();
}
