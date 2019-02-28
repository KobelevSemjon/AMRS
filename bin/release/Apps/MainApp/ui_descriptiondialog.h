/********************************************************************************
** Form generated from reading UI file 'descriptiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESCRIPTIONDIALOG_H
#define UI_DESCRIPTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DescriptionDialog
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *saveButton;
    QProgressBar *progressBar;
    QLabel *label;

    void setupUi(QDialog *DescriptionDialog)
    {
        if (DescriptionDialog->objectName().isEmpty())
            DescriptionDialog->setObjectName(QStringLiteral("DescriptionDialog"));
        DescriptionDialog->resize(640, 480);
        gridLayout = new QGridLayout(DescriptionDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(DescriptionDialog);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 2);

        saveButton = new QPushButton(DescriptionDialog);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        gridLayout->addWidget(saveButton, 2, 1, 1, 1);

        progressBar = new QProgressBar(DescriptionDialog);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 2, 0, 1, 1);

        label = new QLabel(DescriptionDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);


        retranslateUi(DescriptionDialog);

        QMetaObject::connectSlotsByName(DescriptionDialog);
    } // setupUi

    void retranslateUi(QDialog *DescriptionDialog)
    {
        DescriptionDialog->setWindowTitle(QApplication::translate("DescriptionDialog", "Dialog", nullptr));
        saveButton->setText(QApplication::translate("DescriptionDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label->setText(QApplication::translate("DescriptionDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DescriptionDialog: public Ui_DescriptionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESCRIPTIONDIALOG_H
