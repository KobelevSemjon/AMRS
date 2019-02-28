/********************************************************************************
** Form generated from reading UI file 'databasedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEDIALOG_H
#define UI_DATABASEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataBaseDialog
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *deleteButton;
    QPushButton *useButton;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DataBaseDialog)
    {
        if (DataBaseDialog->objectName().isEmpty())
            DataBaseDialog->setObjectName(QStringLiteral("DataBaseDialog"));
        DataBaseDialog->resize(827, 583);
        centralwidget = new QWidget(DataBaseDialog);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        gridLayout->addWidget(deleteButton, 1, 0, 1, 1);

        useButton = new QPushButton(centralwidget);
        useButton->setObjectName(QStringLiteral("useButton"));

        gridLayout->addWidget(useButton, 1, 1, 1, 1);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        gridLayout->addWidget(tableView, 0, 0, 1, 2);

        DataBaseDialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DataBaseDialog);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 827, 21));
        DataBaseDialog->setMenuBar(menubar);
        statusbar = new QStatusBar(DataBaseDialog);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        DataBaseDialog->setStatusBar(statusbar);

        retranslateUi(DataBaseDialog);

        QMetaObject::connectSlotsByName(DataBaseDialog);
    } // setupUi

    void retranslateUi(QMainWindow *DataBaseDialog)
    {
        DataBaseDialog->setWindowTitle(QApplication::translate("DataBaseDialog", "MainWindow", nullptr));
        deleteButton->setText(QApplication::translate("DataBaseDialog", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        useButton->setText(QApplication::translate("DataBaseDialog", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataBaseDialog: public Ui_DataBaseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEDIALOG_H
