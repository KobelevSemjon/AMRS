#include "dialogsvm.h"
#include "ui_dialogsvm.h"

DialogSVM::DialogSVM(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSVM)
{
    ui->setupUi(this);
}

DialogSVM::~DialogSVM()
{
    delete ui;
}
