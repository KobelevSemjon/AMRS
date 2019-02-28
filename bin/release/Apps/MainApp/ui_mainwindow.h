/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <extendedtreeview.h>
#include "imageview.h"
#include "miniview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    MiniView *miniView;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *classifierName;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *accuracy;
    QLabel *sensitivity;
    QLabel *specifity;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLabel *diagnosis;
    QLabel *mark;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *imageName;
    QProgressBar *progressBar;
    QSplitter *splitter;
    ExtendedTreeView *treeView;
    ImageView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(941, 642);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        miniView = new MiniView(centralWidget);
        miniView->setObjectName(QStringLiteral("miniView"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(miniView->sizePolicy().hasHeightForWidth());
        miniView->setSizePolicy(sizePolicy);
        miniView->setMinimumSize(QSize(256, 192));
        miniView->setMaximumSize(QSize(256, 192));
        miniView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        miniView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_3->addWidget(miniView, 0, 2, 1, 1);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        gridLayout_3->addWidget(tableWidget, 2, 2, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        classifierName = new QLabel(centralWidget);
        classifierName->setObjectName(QStringLiteral("classifierName"));

        gridLayout->addWidget(classifierName, 1, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        accuracy = new QLabel(centralWidget);
        accuracy->setObjectName(QStringLiteral("accuracy"));

        gridLayout->addWidget(accuracy, 2, 1, 1, 1);

        sensitivity = new QLabel(centralWidget);
        sensitivity->setObjectName(QStringLiteral("sensitivity"));

        gridLayout->addWidget(sensitivity, 3, 1, 1, 1);

        specifity = new QLabel(centralWidget);
        specifity->setObjectName(QStringLiteral("specifity"));

        gridLayout->addWidget(specifity, 4, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout, 1, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font;
        font.setPointSize(14);
        label_5->setFont(font);

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        diagnosis = new QLabel(centralWidget);
        diagnosis->setObjectName(QStringLiteral("diagnosis"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(diagnosis->sizePolicy().hasHeightForWidth());
        diagnosis->setSizePolicy(sizePolicy2);
        diagnosis->setFont(font);

        gridLayout_2->addWidget(diagnosis, 2, 1, 1, 1);

        mark = new QLabel(centralWidget);
        mark->setObjectName(QStringLiteral("mark"));
        sizePolicy2.setHeightForWidth(mark->sizePolicy().hasHeightForWidth());
        mark->setSizePolicy(sizePolicy2);
        mark->setFont(font);

        gridLayout_2->addWidget(mark, 1, 1, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        imageName = new QLabel(centralWidget);
        imageName->setObjectName(QStringLiteral("imageName"));
        sizePolicy2.setHeightForWidth(imageName->sizePolicy().hasHeightForWidth());
        imageName->setSizePolicy(sizePolicy2);
        imageName->setFont(font);

        gridLayout_2->addWidget(imageName, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 3, 2, 2, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy3);
        progressBar->setValue(0);

        gridLayout_3->addWidget(progressBar, 6, 0, 1, 3);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeView = new ExtendedTreeView(splitter);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy4);
        treeView->setMinimumSize(QSize(0, 0));
        treeView->setMaximumSize(QSize(16777215, 16777215));
        treeView->setBaseSize(QSize(200, 0));
        treeView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        splitter->addWidget(treeView);
        graphicsView = new ImageView(splitter);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        sizePolicy4.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy4);
        graphicsView->setMinimumSize(QSize(100, 0));
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);
        splitter->addWidget(graphicsView);

        gridLayout_3->addWidget(splitter, 0, 0, 5, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 941, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271 \320\272\320\273\320\260\321\201\321\201\320\270\321\204\320\270\320\272\320\260\321\202\320\276\321\200", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\247\321\203\320\262\321\201\321\202\320\262\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214", nullptr));
        classifierName->setText(QApplication::translate("MainWindow", "\320\235\320\265\321\202", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\242\320\276\321\207\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\265\321\206\320\270\321\204\320\270\321\207\320\275\320\276\321\201\321\202\321\214", nullptr));
        accuracy->setText(QString());
        sensitivity->setText(QString());
        specifity->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "\320\236\321\206\320\265\320\275\320\272\320\260", nullptr));
        diagnosis->setText(QApplication::translate("MainWindow", "?", nullptr));
        mark->setText(QApplication::translate("MainWindow", "?", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\224\320\270\320\260\320\263\320\275\320\276\320\267", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        imageName->setText(QApplication::translate("MainWindow", "?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
