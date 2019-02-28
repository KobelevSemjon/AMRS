#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("AMRS");
    setForm();
    setConnects();
    setTopMenu();
}

MainWindow::~MainWindow()
{
    if(copy_paste_buffer !=nullptr)
    {
        copy_paste_buffer->close();
        delete copy_paste_buffer;
    }
    delete current_clf;
    delete model;
    delete ui;
}

void MainWindow::setForm()
{
    ui->graphicsView->setScene(new QGraphicsScene);

    model->setRootPath("");
    model->setNameFilters({"*.jpg","*.bmp"});
    model->setNameFilterDisables(false);

    ui->treeView->setFileSystemModel(model);
    ui->treeView->setColumnHidden(1,true);
    ui->treeView->setColumnHidden(2,true);
    ui->treeView->setColumnHidden(3,true);

    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 1000);

    ui->miniView->setScalableView(ui->graphicsView);

    //ui->currentLabel->setHidden(true);

    ui->progressBar->setHidden(true);
    ui->tableWidget->setColumnCount(1);
    QStringList header;
    for(auto feature: descriptHeader())
        header << QString::fromStdString(feature);
    ui->tableWidget->setRowCount(header.size());
    ui->tableWidget->setVerticalHeaderLabels(header);
    ui->tableWidget->setDisabled(1);
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setHorizontalHeaderItem(0,newTableItem("Признаки"));

    ui->progressBar->setRange(0,header.size());
    //ui->classifyButton->setDisabled(1);
}

void MainWindow::setConnects()
{
    connect(ui->treeView, SIGNAL(clicked(const QModelIndex &)),
            this,SLOT(load(const QModelIndex &)));
    connect(ui->treeView, SIGNAL(rightButtonClicked()),
            this, SLOT(treeClicked()));
    connect(ui->graphicsView, SIGNAL(rightButtonClicked()),
            this, SLOT(viewClicked()));

}

void MainWindow::setTopMenu()
{
    QMenu *description_menu = new QMenu("Описание", this);
    QAction *description_act = new QAction("Описание", this);
    description_menu->addAction(description_act);
    connect(description_act, &QAction::triggered, [&]()
    {
        qDebug()<<"Вызов окна - Описание";
        DescriptionDialog* dialog = new DescriptionDialog(this);

        if (dialog->isEmpty())
            delete dialog;
        else
        {
            dialog->show();
            dialog->descript();
        }
    });
    ui->menuBar->addMenu(description_menu);

    QMenu *learning_menu = new QMenu("Обучение", this);
    QAction *learning_act = new QAction("Обучение по описаниям", this);
    learning_menu->addAction(learning_act);
    connect(learning_act, &QAction::triggered, [&]()
    {
        qDebug()<<"Вызов окна - Обучение";
        LearningDialog* dialog = new LearningDialog(this);
        dialog->show();
    });
    ui->menuBar->addMenu(learning_menu);

    QMenu *classifying_menu = new QMenu("Классификация", this);
    QAction *classifying_act = new QAction("Выбрать модель", this);
    classifying_menu->addAction(classifying_act);
    connect(classifying_act, &QAction::triggered, [&]()
    {
        qDebug()<<"Вызов окна - Классификация";
        DataBaseDialog* dialog = new DataBaseDialog(this);
        connect(dialog, SIGNAL(getClassifierUnion(ClassifierUnion)),this,SLOT(setClassifierUnion(ClassifierUnion)));
        dialog->show();
    });
    ui->menuBar->addMenu(classifying_menu);

}

void MainWindow::treeClicked()
{
    auto idx = ui->treeView->currentIndex();
    QFileInfo file_info = model->fileInfo(idx);

    if (file_info.isFile())
    {
        QMenu* right_btn_menu = new QMenu("treeClicked");

        QAction* copy_act = new QAction("Копировать",this);
        right_btn_menu->addAction(copy_act);
        connect(copy_act, &QAction::triggered, [&]()
        {
            if (copy_paste_buffer != nullptr)
            {
                copy_paste_buffer->close();
                delete copy_paste_buffer;
            }
            copy_paste_buffer = new QFile(file_info.filePath());
            copy_paste_buffer->open(QIODevice::ReadOnly);
        });

        QAction* paste_act = new QAction("Вставить",this);
        right_btn_menu->addAction(paste_act);
        connect(paste_act, &QAction::triggered, [&]()
        {
            QString file_name = copy_paste_buffer->fileName().split("/").last();
            QString target_dir = (file_info.isFile())?file_info.path():file_info.absoluteFilePath();
            for(int i = 1; QDir(target_dir).exists(file_name); ++i)
            {
                //qDebug() << file_name;
                QString name = file_name.split(".")[0].split("(")[0];
                QString format = file_name.split(".")[1];
                file_name = name+QString("(%1).").arg(i)+format;
            }
            QString new_path = target_dir;
            new_path += "/" + file_name;
            copy_paste_buffer->copy(new_path);
        });
        paste_act->setDisabled(copy_paste_buffer==nullptr);

        QAction* remove_act = new QAction("Удалить",this);
        right_btn_menu->addAction(remove_act);
        connect(remove_act, &QAction::triggered, [&]()
        {
            if(((copy_paste_buffer!=nullptr) && (copy_paste_buffer->fileName() == file_info.filePath()))
                    || (!QFile::remove(file_info.filePath())))
            {
                auto* em  = new QErrorMessage(this);
                em->showMessage("Файл редактируется или недостаточно прав для его удаления");
            }
            ui->treeView->update();
        });

        right_btn_menu->exec(QCursor::pos());
    }
}

void MainWindow::viewClicked()
{
    if(QFile::exists(img_file_path))
    {
        QMenu* right_btn_menu = new QMenu("viewClicked");

        QAction* copy_act = new QAction("Сохранить",this);
        right_btn_menu->addAction(copy_act);
        connect(copy_act, &QAction::triggered, [&]()
        {
            auto items = ui->graphicsView->scene()->items();
            auto pixitem = qgraphicsitem_cast<QGraphicsPixmapItem*>(items.last());
            QPixmap pixmap = pixitem->pixmap();
            qDebug()<<pixmap.width() << " " << pixmap.height();
            savePixmap(this,pixmap);
        });

        QAction* boarder_act = new QAction("Наложить границы",this);
        right_btn_menu->addAction(boarder_act);
        connect(boarder_act, &QAction::triggered, [&]()
        {
            Mat3b img = imread(img_file_path);
            auto pixmap = QPixmap::fromImage(getNevusBoardersOnImage(img));
            ui->graphicsView->scene()->clear();
            ui->graphicsView->scene()->addPixmap(pixmap);
        });

        QAction* mask_act = new QAction("Наложить маску",this);
        right_btn_menu->addAction(mask_act);
        connect(mask_act, &QAction::triggered, [&]()
        {
             Mat3b img = imread(img_file_path);
             Mat3b masked_img = getNevusOtsuThrs(img,false);
             auto pixmap = QPixmap::fromImage(Mat2QImage(masked_img));
             ui->graphicsView->scene()->clear();
             ui->graphicsView->scene()->addPixmap(pixmap);
        });

        QAction* return_act = new QAction("Вернуть исходное",this);
        right_btn_menu->addAction(return_act);
        connect(return_act, &QAction::triggered, [&]()
        {
            QPixmap pixmap(img_file_path);
            ui->graphicsView->scene()->clear();
            ui->graphicsView->addPixmap(pixmap);
            ui->miniView->scene()->clear();
            ui->miniView->setMinimap(pixmap);
        });

        if (this->current_clf != nullptr)
        {
            QAction* predict_act = new QAction("Оценить злокачественность",this);
            right_btn_menu->addAction(predict_act);
            connect(predict_act, &QAction::triggered, [&]()
            {
                qDebug()<<"Вызов окна - Оценить злокачественность";
                desctriptAndClassify();
            });
        }

        right_btn_menu->exec(QCursor::pos());
    }
}

void MainWindow::load(const QModelIndex &index)
{
    QFileInfo file_info = model->fileInfo(index);
    if(file_info.isFile())
    {
        QPixmap pixmap(file_info.filePath());
        ui->graphicsView->addPixmap(pixmap);
        ui->miniView->scene()->clear();
        ui->miniView->setMinimap(pixmap);

        img_file_path = file_info.absoluteFilePath();
        //ui->currentLabel->setText(file_info.fileName());
    }
}

void MainWindow::setClassifierUnion(const ClassifierUnion &cu)
{
    delete current_clf;
    if (cu.name == QString("bdt").toLower())
        current_clf = new BoostedDecisionTree();
    else if  (cu.name == QString("knn").toLower())
        current_clf = new KNeighborsClassifier();
    else if (cu.name == QString("lr").toLower())
        current_clf = new LogisticRegressor();
    else if (cu.name == QString("mlp").toLower())
        current_clf = new MLPRegressor();
    else if (cu.name == QString("rf").toLower())
        current_clf = new RandomForest();
    else if (cu.name == QString("svm").toLower())
        current_clf = new SupportVectorMachines();
    else {
        qDebug() << cu.name << " unknown type of classifing";
        std::abort();
    }
    current_clf->loadFromString(cu.clf.toStdString());
    _scaler.fromStdString(cu.scaler.toStdString());

    ui->classifierName->setText(cu.name);
    ui->accuracy->setNum(cu.acc);
    ui->sensitivity->setNum(cu.sen);
    ui->specifity->setNum(cu.spe);
    //ui->classifyButton->setEnabled(true);
}


void MainWindow::desctriptAndClassify()
{ 
    ui->tableWidget->clearContents();
    ui->mark->clear();
    ui->diagnosis->clear();
    ui->imageName->clear();

    ui->progressBar->show();
    ui->progressBar->setValue(0);

    WakeApp wakeApp;
    connect(&wakeApp, &WakeApp::called, [&]()
    {
        int value = ui->progressBar->value();
        ui->progressBar->setValue(value+1);
    });

    Mat3b img = imread(img_file_path);
    Mat3b nevus = getNevusOtsuThrs(img);
    if (isValidNevus(nevus))
    {
        auto od = descriptSegment(nevus, "Undef", wakeApp);

        ui->tableWidget->setEnabled(1);
        auto It = od.description().begin();
        for(int r = 0; r<int(od.size()); ++r)
            ui->tableWidget->setItem(r,0,newTableItem(*It++));

        qDebug()<<od.size() <<" "<<_scaler.size();
        _scaler.transform(od);

        Mat1f row(1,int(od.size()));
        std::copy(od.description().begin(), od.description().end(), row.begin()); 

        float mark = current_clf->predict_for(row);
        ui->mark->setNum(double(mark));
        QString diagnosis = (mark > 0.5f)?"Меланома":"Доброкач.";
        ui->diagnosis->setText(diagnosis);
        ui->imageName->setText(QFileInfo(img_file_path).baseName());
    }
    ui->progressBar->hide();
    wakeApp.disconnect();
}
