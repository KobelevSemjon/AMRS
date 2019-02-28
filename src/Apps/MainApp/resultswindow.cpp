#include "resultswindow.h"
#include "ui_resultswindow.h"

ResultsWindow::ResultsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultsWindow),_db("clf_v2.sqlite",true)
{
    ui->setupUi(this);
    setWindowTitle("Обучение успешно завершено");
}

void ResultsWindow::setAccuracy(double accuracy)
{
    _acc = accuracy;
    ui->accuracy->setNum(accuracy);
}

void ResultsWindow::setSensitivity(double sensitivity)
{
    _sen = sensitivity;
    ui->sensitivity->setNum(sensitivity);
}

void ResultsWindow::setSpecificity(double specificity)
{
    _spe = specificity;
    ui->specificity->setNum(specificity);
}

void ResultsWindow::setSampleValues(int TrainPos, int TrainNeg, int TestPos, int TestNeg)
{
    _TrainPos=TrainPos;
    _TrainNeg=TrainNeg;
    ui->trainPosNeg->setText(QString("%1/%2").arg(TrainPos).arg(TrainNeg));
    _TestPos=TestPos;
    _TestNeg=TestNeg;
    ui->testPosNeg->setText(QString("%1/%2").arg(TestPos).arg(TestNeg));
}

void ResultsWindow::setClassifierType(QString clf_type)
{
    _clf_type = clf_type;
    ui->clfType->setText(clf_type);
}

void ResultsWindow::setScaler(QString scaler)
{
    _scaler = scaler;
}

void ResultsWindow::setClassifier(QString classifier)
{
    _clf = classifier;
}

void ResultsWindow::setParams(QString params)
{
    _params = params;
}

ResultsWindow::~ResultsWindow()
{
    //this->disconnect();
    delete ui;
}

void ResultsWindow::on_pushButton_clicked()
{
    int mainId = _db.addClassifier(_clf_type,_clf,_scaler,_params);
    _db.addStatistics(mainId,_acc,_sen,_spe);
    _db.addSampleValues(mainId,_TrainPos, _TrainNeg, _TestPos, _TestNeg);
    _db.close();
    this->close();
}
