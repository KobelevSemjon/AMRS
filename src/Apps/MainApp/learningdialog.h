#ifndef LEARNINGDIALOG_H
#define LEARNINGDIALOG_H

#include <QDialog>
#include <QStandardPaths>
#include <QFileDialog>
#include <QErrorMessage>

#include "algorithms.h"
#include "resultswindow.h"

namespace Ui {
class LearningDialog;
}

class LearningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LearningDialog(QWidget *parent = nullptr);
    ~LearningDialog();


private slots:
    void on_negPushButton_clicked();
    void on_posPushButton_clicked();

    void on_nextButton_clicked();

    void on_svmKernelComboBox_activated(int index);

private:
    Ui::LearningDialog *ui;

    DataFrame _positive_examples;
    DataFrame _negative_examples;
    Mat1f _X_train, _y_train, _X_test, _y_test;
    StandardTableScaler _scaler;

    bool isAllSetted();
};

#endif // LEARNINGDIALOG_H
