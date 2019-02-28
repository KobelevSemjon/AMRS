#include "learningdialog.h"
#include "ui_learningdialog.h"

LearningDialog::LearningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LearningDialog)
{
    ui->setupUi(this);
    setWindowTitle("Обучение");
    ui->nextButton->setDisabled(true);
    ui->posLineEdit->setReadOnly(true);
    ui->negLineEdit->setReadOnly(true);

    ui->tabWidget->setTabText(0,"BDT");
    ui->tabWidget->setTabText(1,"kNN");
    ui->tabWidget->setTabText(2,"LR");
    ui->tabWidget->setTabText(3,"MLP");
    ui->tabWidget->setTabText(4,"RF");
    ui->tabWidget->setTabText(5,"SVM");

    ui->svmCoef0SpinBox->setDisabled(true);
    ui->svmGammaSpinBox->setDisabled(true);
    ui->svmDegreeSpinBox->setDisabled(true);
}

LearningDialog::~LearningDialog()
{
    delete ui;
}

void LearningDialog::on_negPushButton_clicked()
{
    QString base_folder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString neg_dir_path = QFileDialog::getOpenFileName(this,
                                                tr("Выбор таблицы с описаниями отрицательных примеров"),
                                                base_folder,
                                                tr("Таблицы (*.csv)"),nullptr, QFileDialog::DontResolveSymlinks);
    QString format = neg_dir_path.split('.').last();
    if (format == "csv")
    {
        readDataFrame(_negative_examples, neg_dir_path);
        ui->negLineEdit->setText(neg_dir_path);
    }
    if (neg_dir_path == "") _negative_examples.reset();

    if (isAllSetted())
        ui->nextButton->setEnabled(true);
    else
        ui->nextButton->setDisabled(true);
}

void LearningDialog::on_posPushButton_clicked()
{
    QString base_folder = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString pos_dir_path = QFileDialog::getOpenFileName(this,
                                                tr("Выбор таблицы с описаниями положительных примеров"),
                                                base_folder,
                                                tr("Таблицы (*.csv)"),nullptr, QFileDialog::DontResolveSymlinks);
    QString format = pos_dir_path.split('.').last();
    if (format == "csv")
    {
        readDataFrame(_positive_examples, pos_dir_path);
        ui->posLineEdit->setText(pos_dir_path);
    }
    if (pos_dir_path == "") _positive_examples.reset();

    if (isAllSetted())
        ui->nextButton->setEnabled(true);
    else
        ui->nextButton->setDisabled(true);
}

void LearningDialog::on_nextButton_clicked()
{
    StandardTableScaler scaler;

    scaler.fit(vstack(_negative_examples,_positive_examples));
    scaler.transform(_positive_examples);
    scaler.transform(_negative_examples);
    _scaler = scaler;

    auto sample = createSample(_positive_examples,_negative_examples);
    auto tts = train_test_split(sample.first,sample.second);
    _X_train = get<0>(tts);
    _y_train = get<1>(tts);
    _X_test = get<2>(tts);
    _y_test = get<3>(tts);

    QString classifier_name;
    AbstractClassifier* clf = nullptr;
    enum CLF{BDT,KNN,LR,MLD,RF,SVM};
    try {switch(ui->tabWidget->currentIndex())
        {
        case CLF::BDT:{
            classifier_name = "bdt";
            BoostedDecisionTree* bdt = new BoostedDecisionTree();
            int weak_count = ui->bdtSpinBox->value();
            bdt->setWeakCount(weak_count);
            clf = bdt;
        }break;

        case CLF::KNN:{
            classifier_name = "knn";
            KNeighborsClassifier* knn = new KNeighborsClassifier();
            int defaultK = ui->knnSpinBox->value();
            qDebug()<<"KNN:" << defaultK;
            knn->setDefaultK(defaultK);
            clf = knn;
        }break;

        case CLF::LR:{
            classifier_name = "lr";
            LogisticRegressor* lr = new LogisticRegressor();
            lr->setIterations(ui->lrIterSpinBox->value());
            lr->setLearningRate(ui->lrRateSpinBox->value());
            // REG_DISABLE = -1, REG_L1 = 0, REG_L2 = 1
            lr->setRegularization(ui->lrRegComboBox->currentIndex()-1);
            clf = lr;
        }break;

        case CLF::MLD:{
            classifier_name = "mlp";
            MLPRegressor* mlp = new MLPRegressor();
            QString layers_str = ui->mlpLayers->text();
            QStringList layers_str_list = layers_str.split(",");
            vector<ushort> layers;
            for(auto& l: layers_str_list)
            {
                bool ok = false;
                ushort layer_size = l.toUShort(&ok);
                if(ok) layers.push_back(layer_size);
                else throw std::invalid_argument("Некорректный ввод\n");
            }
            mlp->setLayerSizes(layers);
            clf = mlp;
        }break;

        case CLF::RF:{
            classifier_name = "rf";
            RandomForest* rf = new RandomForest();
            rf->setTreesCount(ui->rfSpinBox->value());
            clf = rf;
        }break;

        case CLF::SVM:{
            //  LINEAR =0, POLY =1, RBF =2, SIGMOID =3, CHI2 =4, INTER =5
            classifier_name = "svm";
            SupportVectorMachines* svm = new SupportVectorMachines();
            svm->setKernel(1+ui->svmKernelComboBox->currentIndex());
            svm->setDegree(ui->svmDegreeSpinBox->value());
            svm->setC(ui->svmCSpinBox->value());
            svm->setGamma(ui->svmGammaSpinBox->value());
            svm->setCoef0(ui->svmCoef0SpinBox->value());         
            clf = svm;
        }break;

        default: assert(false);
        }
        clf->fit(_X_train,_y_train);
        auto responses = clf->predict(_X_test);
        auto cm = createConfusionMatrix(_y_test, responses);

        ResultsWindow* window = new ResultsWindow(this);
        window->setScaler(QString::fromStdString(scaler.toStdString()));
        window->setAccuracy(cm.accuracy());
        window->setSensitivity(cm.sensitivity());
        window->setSpecificity(cm.specificity());
        int TrainPos = std::count_if(_y_train.begin(),_y_train.end(),[](float f)
        {return f > 0.5f;});
        int TrainNeg = _y_train.rows - TrainPos;
        //int TestPo
        window->setSampleValues(TrainPos,TrainNeg,cm.TP+cm.FN,cm.TN+cm.FP);

        window->setClassifierType(classifier_name);
        window->setClassifier(QString::fromStdString(clf->saveToString()));
        window->setParams(QString::fromStdString(clf->getParams()));

        window->show();
        delete clf;
    }
    catch(...)
    {
        auto* em  = new QErrorMessage(this);
        em->showMessage("Ошибка обучения - классификатор не может быть обучен:\n"
                        "- проверте правильность ввода параметров и их корректность;\n"
                        "- проверте валидность обучающей выборки;");
    }
}

bool LearningDialog::isAllSetted()
{
    return  (_positive_examples.rows()!=0 )
            && (_negative_examples.rows()!=0);
            //&& (ui->clfComboBox->currentIndex()!=0);
}

void LearningDialog::on_svmKernelComboBox_activated(int index)
{
    enum Type{LINEAR,POLY,RBF,SIGMOID,CHI2,INTER};
    switch (index) {
    case LINEAR:
    {
        ui->svmCoef0SpinBox->setDisabled(true);
        ui->svmGammaSpinBox->setDisabled(true);
        ui->svmDegreeSpinBox->setDisabled(true);
        ui->svmGammaSpinBox->setMinimum(-100);
    }break;
    case POLY:
    {
        ui->svmCoef0SpinBox->setDisabled(false);
        ui->svmGammaSpinBox->setDisabled(false);
        ui->svmDegreeSpinBox->setDisabled(false);
        ui->svmGammaSpinBox->setMinimum(0.001);
    }break;

    case RBF:
    {
        ui->svmCoef0SpinBox->setDisabled(false);
        ui->svmGammaSpinBox->setDisabled(false);
        ui->svmDegreeSpinBox->setDisabled(true);
        ui->svmGammaSpinBox->setMinimum(0.001);
    }break;

    case SIGMOID:
    {
        ui->svmCoef0SpinBox->setDisabled(false);
        ui->svmGammaSpinBox->setDisabled(false);
        ui->svmDegreeSpinBox->setDisabled(true);
        ui->svmGammaSpinBox->setMinimum(-100);
    }break;

    case CHI2:
    {
        ui->svmCoef0SpinBox->setDisabled(false);
        ui->svmGammaSpinBox->setDisabled(false);
        ui->svmDegreeSpinBox->setDisabled(true);
        ui->svmGammaSpinBox->setMinimum(0.001);
    }break;

    case INTER:
    {
        ui->svmCoef0SpinBox->setDisabled(true);
        ui->svmGammaSpinBox->setDisabled(true);
        ui->svmDegreeSpinBox->setDisabled(true);
        ui->svmGammaSpinBox->setMinimum(-100);
    }break;
    }
}
