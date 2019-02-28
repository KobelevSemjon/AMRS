#ifndef DESCRIPTIONDIALOG_H
#define DESCRIPTIONDIALOG_H

#include <QDialog>
#include <QStandardPaths>
#include <QFileDialog>

#include "algorithms.h"

namespace Ui {
class DescriptionDialog;
}

class DescriptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DescriptionDialog(QWidget *parent = nullptr);
    ~DescriptionDialog();
    bool isEmpty()
    {
        return _dir.isEmpty();
    }
    void descript();

private slots:

    void progress(int percent);
    void on_saveButton_clicked();

private:
    Ui::DescriptionDialog *ui;

    DataFrame _df;
    QDir _dir;

    void initTableWidget();
    void insertObjectDescription(int row, const ObjectDescription& od);
};

#endif // DESCRIPTIONDIALOG_H
