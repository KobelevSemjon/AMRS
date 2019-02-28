/********************************************************************************
** Form generated from reading UI file 'learningdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEARNINGDIALOG_H
#define UI_LEARNINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LearningDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *negLineEdit;
    QPushButton *nextButton;
    QLineEdit *posLineEdit;
    QLabel *label;
    QLabel *label_2;
    QPushButton *negPushButton;
    QPushButton *posPushButton;
    QLabel *label_3;
    QLabel *label_4;
    QTabWidget *tabWidget;
    QWidget *bdt;
    QGridLayout *gridLayout_3;
    QSpinBox *bdtSpinBox;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QWidget *knn;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QSpinBox *knnSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_8;
    QWidget *lr;
    QGridLayout *gridLayout_4;
    QSpinBox *lrIterSpinBox;
    QLabel *label_14;
    QLabel *label_9;
    QDoubleSpinBox *lrRateSpinBox;
    QLabel *label_13;
    QLabel *label_15;
    QComboBox *lrRegComboBox;
    QWidget *mlp;
    QGridLayout *gridLayout_5;
    QLabel *label_16;
    QLineEdit *mlpLayers;
    QLabel *label_10;
    QWidget *rf;
    QGridLayout *gridLayout_6;
    QSpinBox *rfSpinBox;
    QLabel *label_11;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_3;
    QWidget *svm;
    QGridLayout *gridLayout_7;
    QDoubleSpinBox *svmGammaSpinBox;
    QDoubleSpinBox *svmCoef0SpinBox;
    QComboBox *svmKernelComboBox;
    QLabel *label_22;
    QLabel *label_12;
    QDoubleSpinBox *svmCSpinBox;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_18;
    QLabel *label_21;
    QDoubleSpinBox *svmDegreeSpinBox;

    void setupUi(QDialog *LearningDialog)
    {
        if (LearningDialog->objectName().isEmpty())
            LearningDialog->setObjectName(QStringLiteral("LearningDialog"));
        LearningDialog->resize(604, 244);
        gridLayout = new QGridLayout(LearningDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        negLineEdit = new QLineEdit(LearningDialog);
        negLineEdit->setObjectName(QStringLiteral("negLineEdit"));
        negLineEdit->setEnabled(true);

        gridLayout->addWidget(negLineEdit, 1, 1, 1, 1);

        nextButton = new QPushButton(LearningDialog);
        nextButton->setObjectName(QStringLiteral("nextButton"));

        gridLayout->addWidget(nextButton, 5, 2, 1, 1);

        posLineEdit = new QLineEdit(LearningDialog);
        posLineEdit->setObjectName(QStringLiteral("posLineEdit"));

        gridLayout->addWidget(posLineEdit, 2, 1, 1, 1);

        label = new QLabel(LearningDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(LearningDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        negPushButton = new QPushButton(LearningDialog);
        negPushButton->setObjectName(QStringLiteral("negPushButton"));

        gridLayout->addWidget(negPushButton, 1, 2, 1, 1);

        posPushButton = new QPushButton(LearningDialog);
        posPushButton->setObjectName(QStringLiteral("posPushButton"));

        gridLayout->addWidget(posPushButton, 2, 2, 1, 1);

        label_3 = new QLabel(LearningDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 3);

        label_4 = new QLabel(LearningDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        tabWidget = new QTabWidget(LearningDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        bdt = new QWidget();
        bdt->setObjectName(QStringLiteral("bdt"));
        gridLayout_3 = new QGridLayout(bdt);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        bdtSpinBox = new QSpinBox(bdt);
        bdtSpinBox->setObjectName(QStringLiteral("bdtSpinBox"));
        bdtSpinBox->setMinimum(1);
        bdtSpinBox->setMaximum(500);
        bdtSpinBox->setSingleStep(10);
        bdtSpinBox->setValue(100);

        gridLayout_3->addWidget(bdtSpinBox, 1, 1, 1, 1);

        label_6 = new QLabel(bdt);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 2, 1, 1);

        label_5 = new QLabel(bdt);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 3);

        tabWidget->addTab(bdt, QString());
        knn = new QWidget();
        knn->setObjectName(QStringLiteral("knn"));
        gridLayout_2 = new QGridLayout(knn);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_7 = new QLabel(knn);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        knnSpinBox = new QSpinBox(knn);
        knnSpinBox->setObjectName(QStringLiteral("knnSpinBox"));
        knnSpinBox->setMinimum(1);
        knnSpinBox->setSingleStep(2);
        knnSpinBox->setDisplayIntegerBase(10);

        gridLayout_2->addWidget(knnSpinBox, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        label_8 = new QLabel(knn);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 0, 0, 1, 3);

        tabWidget->addTab(knn, QString());
        lr = new QWidget();
        lr->setObjectName(QStringLiteral("lr"));
        gridLayout_4 = new QGridLayout(lr);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        lrIterSpinBox = new QSpinBox(lr);
        lrIterSpinBox->setObjectName(QStringLiteral("lrIterSpinBox"));
        lrIterSpinBox->setMinimum(1);
        lrIterSpinBox->setMaximum(1000);
        lrIterSpinBox->setValue(100);

        gridLayout_4->addWidget(lrIterSpinBox, 1, 1, 1, 1);

        label_14 = new QLabel(lr);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_4->addWidget(label_14, 1, 2, 1, 1);

        label_9 = new QLabel(lr);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_4->addWidget(label_9, 0, 0, 1, 2);

        lrRateSpinBox = new QDoubleSpinBox(lr);
        lrRateSpinBox->setObjectName(QStringLiteral("lrRateSpinBox"));
        lrRateSpinBox->setDecimals(3);
        lrRateSpinBox->setMinimum(0.001);
        lrRateSpinBox->setMaximum(0.999);

        gridLayout_4->addWidget(lrRateSpinBox, 1, 3, 1, 1);

        label_13 = new QLabel(lr);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_4->addWidget(label_13, 1, 0, 1, 1);

        label_15 = new QLabel(lr);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_4->addWidget(label_15, 1, 4, 1, 1);

        lrRegComboBox = new QComboBox(lr);
        lrRegComboBox->addItem(QString());
        lrRegComboBox->addItem(QString());
        lrRegComboBox->addItem(QString());
        lrRegComboBox->setObjectName(QStringLiteral("lrRegComboBox"));

        gridLayout_4->addWidget(lrRegComboBox, 1, 5, 1, 1);

        tabWidget->addTab(lr, QString());
        mlp = new QWidget();
        mlp->setObjectName(QStringLiteral("mlp"));
        gridLayout_5 = new QGridLayout(mlp);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_16 = new QLabel(mlp);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_5->addWidget(label_16, 1, 0, 1, 1);

        mlpLayers = new QLineEdit(mlp);
        mlpLayers->setObjectName(QStringLiteral("mlpLayers"));

        gridLayout_5->addWidget(mlpLayers, 1, 1, 1, 1);

        label_10 = new QLabel(mlp);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 0, 0, 1, 2);

        tabWidget->addTab(mlp, QString());
        rf = new QWidget();
        rf->setObjectName(QStringLiteral("rf"));
        gridLayout_6 = new QGridLayout(rf);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        rfSpinBox = new QSpinBox(rf);
        rfSpinBox->setObjectName(QStringLiteral("rfSpinBox"));
        rfSpinBox->setMinimum(1);
        rfSpinBox->setMaximum(500);
        rfSpinBox->setValue(100);
        rfSpinBox->setDisplayIntegerBase(10);

        gridLayout_6->addWidget(rfSpinBox, 1, 1, 1, 1);

        label_11 = new QLabel(rf);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_6->addWidget(label_11, 0, 0, 1, 1);

        label_17 = new QLabel(rf);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_6->addWidget(label_17, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        tabWidget->addTab(rf, QString());
        svm = new QWidget();
        svm->setObjectName(QStringLiteral("svm"));
        gridLayout_7 = new QGridLayout(svm);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        svmGammaSpinBox = new QDoubleSpinBox(svm);
        svmGammaSpinBox->setObjectName(QStringLiteral("svmGammaSpinBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(svmGammaSpinBox->sizePolicy().hasHeightForWidth());
        svmGammaSpinBox->setSizePolicy(sizePolicy);
        svmGammaSpinBox->setDecimals(3);
        svmGammaSpinBox->setMinimum(-100);
        svmGammaSpinBox->setMaximum(100);
        svmGammaSpinBox->setValue(1);

        gridLayout_7->addWidget(svmGammaSpinBox, 1, 5, 1, 1);

        svmCoef0SpinBox = new QDoubleSpinBox(svm);
        svmCoef0SpinBox->setObjectName(QStringLiteral("svmCoef0SpinBox"));
        sizePolicy.setHeightForWidth(svmCoef0SpinBox->sizePolicy().hasHeightForWidth());
        svmCoef0SpinBox->setSizePolicy(sizePolicy);
        svmCoef0SpinBox->setMinimum(-100);
        svmCoef0SpinBox->setMaximum(100);

        gridLayout_7->addWidget(svmCoef0SpinBox, 1, 7, 1, 1);

        svmKernelComboBox = new QComboBox(svm);
        svmKernelComboBox->addItem(QString());
        svmKernelComboBox->addItem(QString());
        svmKernelComboBox->addItem(QString());
        svmKernelComboBox->addItem(QString());
        svmKernelComboBox->addItem(QString());
        svmKernelComboBox->setObjectName(QStringLiteral("svmKernelComboBox"));

        gridLayout_7->addWidget(svmKernelComboBox, 1, 1, 1, 1);

        label_22 = new QLabel(svm);
        label_22->setObjectName(QStringLiteral("label_22"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(label_22, 1, 8, 1, 1);

        label_12 = new QLabel(svm);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_7->addWidget(label_12, 0, 0, 1, 2);

        svmCSpinBox = new QDoubleSpinBox(svm);
        svmCSpinBox->setObjectName(QStringLiteral("svmCSpinBox"));
        sizePolicy.setHeightForWidth(svmCSpinBox->sizePolicy().hasHeightForWidth());
        svmCSpinBox->setSizePolicy(sizePolicy);
        svmCSpinBox->setDecimals(4);
        svmCSpinBox->setMaximum(1000);
        svmCSpinBox->setValue(1);

        gridLayout_7->addWidget(svmCSpinBox, 1, 3, 1, 1);

        label_19 = new QLabel(svm);
        label_19->setObjectName(QStringLiteral("label_19"));
        sizePolicy1.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(label_19, 1, 2, 1, 1);

        label_20 = new QLabel(svm);
        label_20->setObjectName(QStringLiteral("label_20"));
        sizePolicy1.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(label_20, 1, 4, 1, 1);

        label_18 = new QLabel(svm);
        label_18->setObjectName(QStringLiteral("label_18"));
        sizePolicy1.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(label_18, 1, 0, 1, 1);

        label_21 = new QLabel(svm);
        label_21->setObjectName(QStringLiteral("label_21"));
        sizePolicy1.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(label_21, 1, 6, 1, 1);

        svmDegreeSpinBox = new QDoubleSpinBox(svm);
        svmDegreeSpinBox->setObjectName(QStringLiteral("svmDegreeSpinBox"));
        sizePolicy.setHeightForWidth(svmDegreeSpinBox->sizePolicy().hasHeightForWidth());
        svmDegreeSpinBox->setSizePolicy(sizePolicy);
        svmDegreeSpinBox->setDecimals(3);
        svmDegreeSpinBox->setMinimum(0.001);
        svmDegreeSpinBox->setValue(1);

        gridLayout_7->addWidget(svmDegreeSpinBox, 1, 9, 1, 1);

        tabWidget->addTab(svm, QString());

        gridLayout->addWidget(tabWidget, 4, 0, 1, 3);


        retranslateUi(LearningDialog);

        tabWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(LearningDialog);
    } // setupUi

    void retranslateUi(QDialog *LearningDialog)
    {
        LearningDialog->setWindowTitle(QApplication::translate("LearningDialog", "Dialog", nullptr));
        nextButton->setText(QApplication::translate("LearningDialog", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214", nullptr));
        label->setText(QApplication::translate("LearningDialog", "\320\242\320\260\320\261\320\273\320\270\321\206\320\260 \321\201 \320\264\320\276\320\261\321\200\320\276\320\272\320\260\321\207\320\265\321\201\321\202\320\262\320\265\320\275\320\275\321\213\320\274\320\270\n"
"\320\277\321\200\320\270\320\274\320\265\321\200\320\260\320\274\320\270 (\320\276\321\202\321\200\320\270\321\206\320\260\321\202\320\265\320\273\321\214\320\275\321\213\320\271 \320\272\320\273\320\260\321\201\321\201)", nullptr));
        label_2->setText(QApplication::translate("LearningDialog", "\320\242\320\260\320\261\320\273\320\270\321\206\320\260 \321\201 \320\267\320\273\320\276\320\272\320\260\321\207\320\265\321\201\321\202\320\262\320\265\320\275\320\275\321\213\320\274\320\270\n"
"\320\277\321\200\320\270\320\274\320\265\321\200\320\260\320\274\320\270 (\320\277\320\276\320\273\320\276\320\266\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\271 \320\272\320\273\320\260\321\201\321\201)", nullptr));
        negPushButton->setText(QApplication::translate("LearningDialog", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        posPushButton->setText(QApplication::translate("LearningDialog", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214", nullptr));
        label_3->setText(QApplication::translate("LearningDialog", "\320\250\320\260\320\263 1. \320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\276\320\277\320\270\321\201\320\275\320\270\321\217 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262 (\320\276\320\261\321\203\321\207\320\260\321\216\321\211\321\203\321\216 \320\262\321\213\320\261\320\276\321\200\320\272\321\203) \320\270 \321\202\320\270\320\277 \320\272\320\273\320\260\321\201\321\201\320\270\321\204\320\270\320\272\320\260\321\202\320\276\321\200\320\260", nullptr));
        label_4->setText(QApplication::translate("LearningDialog", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \320\272\320\273\320\260\321\201\321\201\320\270\321\204\320\270\320\272\320\260\321\206\320\270\320\270", nullptr));
        label_6->setText(QApplication::translate("LearningDialog", "\320\247\320\270\321\201\320\273\320\276 \320\264\320\265\321\200\320\265\320\262\321\214\320\265\320\262", nullptr));
        label_5->setText(QApplication::translate("LearningDialog", "\320\223\321\200\320\260\320\264\320\270\320\265\320\275\321\202\320\275\321\213\320\271 \320\261\321\203\321\201\321\202\320\270\320\275\320\263 \320\275\320\260\320\264 \321\200\320\265\321\210\320\260\321\216\321\211\320\270\320\274\320\270 \320\264\320\265\321\200\320\265\320\262\321\214\321\217\320\274\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(bdt), QApplication::translate("LearningDialog", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
        label_7->setText(QApplication::translate("LearningDialog", "\320\247\320\270\321\201\320\273\320\276 \321\201\320\276\321\201\320\265\320\264\320\265\320\271", nullptr));
        label_8->setText(QApplication::translate("LearningDialog", "\320\234\320\265\321\202\320\276\320\264 k-\320\261\320\273\320\270\320\266\320\260\320\271\321\210\320\270\321\205 \321\201\320\276\321\201\320\265\320\264\320\265\320\271", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(knn), QApplication::translate("LearningDialog", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
        label_14->setText(QApplication::translate("LearningDialog", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        label_9->setText(QApplication::translate("LearningDialog", "\320\233\320\276\320\263\320\270\321\201\321\202\320\270\321\207\320\265\321\201\320\272\320\260\321\217 \321\200\320\265\320\263\321\200\320\265\321\201\321\201\320\270\321\217", nullptr));
        label_13->setText(QApplication::translate("LearningDialog", "\320\230\321\202\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        label_15->setText(QApplication::translate("LearningDialog", "\320\242\320\270\320\277 \321\200\320\265\320\263\321\203\320\273\320\260\321\200\320\270\320\267\320\260\321\206\320\270\320\270", nullptr));
        lrRegComboBox->setItemText(0, QApplication::translate("LearningDialog", "\320\235\320\265\321\202", nullptr));
        lrRegComboBox->setItemText(1, QApplication::translate("LearningDialog", "L1", nullptr));
        lrRegComboBox->setItemText(2, QApplication::translate("LearningDialog", "L2", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(lr), QApplication::translate("LearningDialog", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
        label_16->setText(QApplication::translate("LearningDialog", "\320\247\320\270\321\201\320\273\320\276 \320\262\320\275\321\203\321\202\321\200\320\265\320\275\320\275\320\270\321\205 \321\201\320\273\320\276\320\265\320\262 (\321\207\320\265\321\200\320\265\320\267 \",\")", nullptr));
        mlpLayers->setText(QApplication::translate("LearningDialog", "10,10,5", nullptr));
        label_10->setText(QApplication::translate("LearningDialog", "\320\234\320\275\320\276\320\263\320\276\321\201\320\273\320\276\320\271\320\275\321\213\320\271 \320\277\320\265\321\200\321\201\320\265\320\277\321\202\321\200\320\276\320\275 (\320\230\321\201\320\272\321\203\321\201\321\201\321\202\320\262\320\265\320\275\320\275\320\260\321\217 \320\275\320\265\320\271\321\200\320\276\320\275\320\275\320\260\321\217 \321\201\320\265\321\202\321\214)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(mlp), QApplication::translate("LearningDialog", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
        label_11->setText(QApplication::translate("LearningDialog", "\320\241\320\273\321\203\321\207\320\260\320\271\320\275\321\213\320\271 \320\273\320\265\321\201", nullptr));
        label_17->setText(QApplication::translate("LearningDialog", "\320\247\320\270\321\201\320\273\320\276 \320\264\320\265\321\200\320\265\320\262\321\214\320\265\320\262", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(rf), QApplication::translate("LearningDialog", "Tab 1", nullptr));
        svmKernelComboBox->setItemText(0, QApplication::translate("LearningDialog", "LINEAR", nullptr));
        svmKernelComboBox->setItemText(1, QApplication::translate("LearningDialog", "POLY", nullptr));
        svmKernelComboBox->setItemText(2, QApplication::translate("LearningDialog", "RBF", nullptr));
        svmKernelComboBox->setItemText(3, QApplication::translate("LearningDialog", "SIGMOID", nullptr));
        svmKernelComboBox->setItemText(4, QApplication::translate("LearningDialog", "CHI2", nullptr));

        label_22->setText(QApplication::translate("LearningDialog", "\320\241\321\202\320\265\320\277\320\265\320\275\321\214", nullptr));
        label_12->setText(QApplication::translate("LearningDialog", "\320\234\320\265\321\202\320\276\320\264 \320\276\320\277\320\276\321\200\320\275\321\213\321\205 \320\262\320\265\320\272\321\202\320\276\321\200\320\276\320\262", nullptr));
        label_19->setText(QApplication::translate("LearningDialog", "\320\241", nullptr));
        label_20->setText(QApplication::translate("LearningDialog", "Gamma", nullptr));
        label_18->setText(QApplication::translate("LearningDialog", "\320\242\320\270\320\277 \321\217\320\264\321\200\320\260", nullptr));
        label_21->setText(QApplication::translate("LearningDialog", "Coef0", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(svm), QApplication::translate("LearningDialog", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LearningDialog: public Ui_LearningDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEARNINGDIALOG_H
