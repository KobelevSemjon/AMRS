#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSplitter>
#include <QDebug>
#include <QErrorMessage>
#include <QGraphicsPixmapItem>

#include "descriptiondialog.h"
#include "learningdialog.h"
#include "databasedialog.h"

#include "imageview.h"
#include "miniview.h"
#include "extendedtreeview.h"
#include "algorithms.h"
#include "database.h"//

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileSystemModel* model = new QFileSystemModel;
    QFile* copy_paste_buffer = nullptr;
    QString img_file_path;

    AbstractClassifier* current_clf = nullptr;
    StandardTableScaler _scaler;

    //DataBase db;//
    void setForm();
    void setConnects();
    void setTopMenu();

private slots:
    void treeClicked();
    void viewClicked();
    void load(const QModelIndex & index);

    void setClassifierUnion(const ClassifierUnion& cu);
    void desctriptAndClassify();
};

#endif // MAINWINDOW_H
