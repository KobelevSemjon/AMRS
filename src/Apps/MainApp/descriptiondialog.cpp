#include "descriptiondialog.h"
#include "ui_descriptiondialog.h"

DescriptionDialog::DescriptionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DescriptionDialog)
{
    QString base_folder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString file_path = QFileDialog::getExistingDirectory(this, "Папка с изображениями",
                                                          base_folder); //! \todo отобразить картинки
    _dir = QDir(file_path);
    _dir.setNameFilters({"*.jpg","*.bmp"});

    ui->setupUi(this);
    setWindowTitle("Описание");
    ui->progressBar->setMaximum(100);
    ui->saveButton->hide();

    //descript();
}

DescriptionDialog::~DescriptionDialog()
{
    delete ui;
}

void DescriptionDialog::descript()
{
    ui->label->setText("Идет процесс описания изображений папки, пожалуйста подождите...");

    std::list<string> header = descriptHeader();
    _df.reset();
    _df.setTableName("Image");
    _df.setHeader(descriptHeader());

    initTableWidget();

    int table_widget_row = 1;
    int dirrownum = 0;
    for(QString name: _dir.entryList())
    {
        QString filepath = _dir.absoluteFilePath(name);
        cv::Mat3b cv_img = imread(filepath);
        if(cv_img.rows < 0 || cv_img.rows>1920 || cv_img.cols>2560)
        {
            qDebug()<<"bad image, not discribed";
            ++dirrownum;
            continue;
        }

        cv::Mat3b nevi = getNevusOtsuThrs(cv_img);

        cv_img.release();
        auto obj = descriptSegment(nevi, name.toStdString());

        nevi.release();
        //qDebug() << obj.size() << " " <<_df.cols();
        _df.newObject(obj);

        ui->tableWidget->setItem(table_widget_row, 0, newTableItem(name));
        insertObjectDescription(table_widget_row,obj);

        ++table_widget_row;

        ++dirrownum;
        progress((100*dirrownum)/int(_dir.count()));

        if (!isVisible()) break;
        wakeApp();
    }
    progress(100);
    ui->tableWidget->update();
    ui->saveButton->show();
    ui->label->hide();
    ui->progressBar->hide();
    wakeApp();
}

void DescriptionDialog::progress(int percent)
{
    ui->progressBar->setValue(percent);
    wakeApp();
}

void DescriptionDialog::on_saveButton_clicked()
{
    QString base_folder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString file_path = QFileDialog::getSaveFileName(this, "Сохранить выборку",
                      base_folder,"Таблица (*.csv)");
    if(file_path!=QString())
    {
        QFile csv(file_path);
        if (!csv.open(QIODevice::WriteOnly | QIODevice::Text)) return;
        QTextStream out(&csv);
        out<<_df;
        csv.close();
    }
}

void DescriptionDialog::initTableWidget()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->clear();

    ui->tableWidget->setRowCount(int(_dir.count()+1));
    ui->tableWidget->setColumnCount(int(_df.cols()+1));
    ui->tableWidget->setItem(0,0,newTableItem(_df.getTableName()));

    int widg_col = 1;
    for(const auto& col_name: _df.getHeader())
        ui->tableWidget->setItem(0,widg_col++,newTableItem(col_name));

    //int widg_row = 1;
    //for(QString name: _dir.entryList())
        // ui->tableWidget->setItem(widg_row++, 0, newTableItem(""));

}

void DescriptionDialog::insertObjectDescription(int row, const ObjectDescription &od)
{
    int widg_row = row, widg_col = 1;
    for(double val: od.description())
    {
        ui->tableWidget->setItem(widg_row, widg_col, newTableItem(val));
        ++widg_col;
    }
}
