#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QDialog>
#include "algorithms.h"
#include "database.h"

namespace Ui {
class ResultsWindow;
}

class ResultsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResultsWindow(QWidget *parent);

    void setAccuracy(double accuracy);
    void setSensitivity(double sensitivity);
    void setSpecificity(double specificity);
    void setSampleValues(int TrainPos, int TrainNeg, int TestPos, int TestNeg);
    void setClassifierType(QString clf_type);
    void setScaler(QString scaler);
    void setClassifier(QString classifier);
    void setParams(QString params);

    ~ResultsWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ResultsWindow *ui;

    int _TrainPos, _TrainNeg;
    int _TestPos, _TestNeg;
    QString _scaler;
    QString _clf;
    QString _clf_type;
    double _acc, _sen, _spe;
    QString _params;

    DataBase _db;
};

#endif // RESULTSWINDOW_H
