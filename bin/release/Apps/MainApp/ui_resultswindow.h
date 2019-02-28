/********************************************************************************
** Form generated from reading UI file 'resultswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTSWINDOW_H
#define UI_RESULTSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ResultsWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label_5;
    QPushButton *pushButton;
    QLabel *label_6;
    QLabel *label_3;
    QFrame *line;
    QLabel *sensitivity;
    QLabel *accuracy;
    QLabel *label;
    QLabel *clfType;
    QLabel *specificity;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *trainPosNeg;
    QLabel *testPosNeg;

    void setupUi(QDialog *ResultsWindow)
    {
        if (ResultsWindow->objectName().isEmpty())
            ResultsWindow->setObjectName(QStringLiteral("ResultsWindow"));
        ResultsWindow->resize(475, 231);
        gridLayout = new QGridLayout(ResultsWindow);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_5 = new QLabel(ResultsWindow);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        pushButton = new QPushButton(ResultsWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 7, 0, 1, 3);

        label_6 = new QLabel(ResultsWindow);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        label_3 = new QLabel(ResultsWindow);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        line = new QFrame(ResultsWindow);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 1, 6, 1);

        sensitivity = new QLabel(ResultsWindow);
        sensitivity->setObjectName(QStringLiteral("sensitivity"));

        gridLayout->addWidget(sensitivity, 5, 2, 1, 1);

        accuracy = new QLabel(ResultsWindow);
        accuracy->setObjectName(QStringLiteral("accuracy"));

        gridLayout->addWidget(accuracy, 4, 2, 1, 1);

        label = new QLabel(ResultsWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        clfType = new QLabel(ResultsWindow);
        clfType->setObjectName(QStringLiteral("clfType"));

        gridLayout->addWidget(clfType, 1, 2, 1, 1);

        specificity = new QLabel(ResultsWindow);
        specificity->setObjectName(QStringLiteral("specificity"));

        gridLayout->addWidget(specificity, 6, 2, 1, 1);

        label_2 = new QLabel(ResultsWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_4 = new QLabel(ResultsWindow);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_7 = new QLabel(ResultsWindow);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        trainPosNeg = new QLabel(ResultsWindow);
        trainPosNeg->setObjectName(QStringLiteral("trainPosNeg"));

        gridLayout->addWidget(trainPosNeg, 2, 2, 1, 1);

        testPosNeg = new QLabel(ResultsWindow);
        testPosNeg->setObjectName(QStringLiteral("testPosNeg"));

        gridLayout->addWidget(testPosNeg, 3, 2, 1, 1);


        retranslateUi(ResultsWindow);

        QMetaObject::connectSlotsByName(ResultsWindow);
    } // setupUi

    void retranslateUi(QDialog *ResultsWindow)
    {
        ResultsWindow->setWindowTitle(QApplication::translate("ResultsWindow", "Dialog", nullptr));
        label_5->setText(QApplication::translate("ResultsWindow", "\320\247\321\203\320\262\321\201\321\202\320\262\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 (\320\275\320\260\320\271\320\264\320\265\320\275\320\276 \"+\")", nullptr));
        pushButton->setText(QApplication::translate("ResultsWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 \320\261\320\260\320\267\321\203 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        label_6->setText(QApplication::translate("ResultsWindow", "\320\241\320\277\320\265\321\206\320\270\321\204\320\270\321\207\320\275\320\276\321\201\321\202\321\214 (\320\275\320\260\320\271\320\264\320\265\320\275\320\276 \"-\")", nullptr));
        label_3->setText(QApplication::translate("ResultsWindow", "\320\242\320\276\321\207\320\275\320\276\321\201\321\202\321\214 (\320\264\320\276\320\273\321\217 \320\262\320\265\321\200\320\275\321\213\321\205 \320\276\321\202\320\262\320\265\321\202\320\276\320\262)", nullptr));
        sensitivity->setText(QApplication::translate("ResultsWindow", "TextLabel", nullptr));
        accuracy->setText(QApplication::translate("ResultsWindow", "TextLabel", nullptr));
        label->setText(QApplication::translate("ResultsWindow", "\320\232\320\273\320\260\321\201\321\201\320\270\321\204\320\270\320\272\320\260\321\202\320\276\321\200 \320\276\320\261\321\203\321\207\320\265\320\275!", nullptr));
        clfType->setText(QApplication::translate("ResultsWindow", "TextLabel", nullptr));
        specificity->setText(QApplication::translate("ResultsWindow", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("ResultsWindow", "\320\242\320\270\320\277 \320\272\320\273\320\260\321\201\321\201\320\270\321\204\320\270\320\272\320\260\321\202\320\276\321\200\320\260:", nullptr));
        label_4->setText(QApplication::translate("ResultsWindow", "\320\241\320\276\320\276\321\202\320\275\320\276\321\210\320\265\320\275\320\270\320\265 +/- \320\262 \320\277\321\200\320\270 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\320\270 (80%)", nullptr));
        label_7->setText(QApplication::translate("ResultsWindow", "\320\241\320\276\320\276\321\202\320\275\320\276\321\210\320\265\320\275\320\270\320\265 +/- \320\262 \320\277\321\200\320\270 \321\202\320\265\321\201\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\270 (20%)", nullptr));
        trainPosNeg->setText(QApplication::translate("ResultsWindow", "TextLabel", nullptr));
        testPosNeg->setText(QApplication::translate("ResultsWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResultsWindow: public Ui_ResultsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTSWINDOW_H
