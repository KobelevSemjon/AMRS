#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "database.h"

namespace Ui {
class DataBaseDialog;
}

struct ClassifierUnion
{
    QString name;
    QString clf;
    QString scaler;

    double acc, sen, spe;
};

class DataBaseDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit DataBaseDialog(QWidget *parent = nullptr);
    ~DataBaseDialog();

private slots:
    void on_deleteButton_clicked();
    void on_useButton_clicked();

signals:

    void getClassifierUnion(ClassifierUnion);


private:
    Ui::DataBaseDialog *ui;

    QSqlTableModel *model;
    DataBase _db;
};

#endif // DATABASEDIALOG_H
