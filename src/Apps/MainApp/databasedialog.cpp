#include "databasedialog.h"
#include "ui_databasedialog.h"

DataBaseDialog::DataBaseDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DataBaseDialog),_db("clf_v2.sqlite")
{
    ui->setupUi(this);
    setWindowTitle("Выбор классификатора");
    model = new QSqlTableModel(this, _db.database());
    model->setTable("main");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    int last_column = 9;
    ui->tableView->hideColumn(last_column);
}

DataBaseDialog::~DataBaseDialog()
{ 
    delete model;
    _db.close();
    delete ui;
}

void DataBaseDialog::on_deleteButton_clicked()
{
    auto row = ui->tableView->currentIndex().row();
    if(row>=0)
    {
        auto index = model->index(row,0);
        int mainId = index.data().toInt();
        _db.removeClassifier(mainId);
        //ui->tableView->update();
        ui->tableView->hideRow(row);
    }
}

void DataBaseDialog::on_useButton_clicked()
{
    auto row = ui->tableView->currentIndex().row();
    if(row>=0)
    {
        auto index = model->index(row,0);
        int mainId = index.data().toInt();
        ClassifierUnion cu;
        cu.clf = _db.getClassifier(mainId);
        cu.scaler = _db.getScaler(mainId);
        cu.name = _db.getClassifierName(mainId);
        _db.getStatistics(mainId,cu.acc,cu.sen,cu.spe);
        emit getClassifierUnion(cu);
        close();
    }
}
