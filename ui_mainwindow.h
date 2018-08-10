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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *refreshButton;
    QComboBox *processList;
    QSplitter *splitter;
    QTableWidget *moduleList;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *pagedStatusLayout;
    QPushButton *refreshPaged;
    QProgressBar *amountUnpaged;
    QHBoxLayout *addressLayout;
    QLineEdit *curAddress;
    QLineEdit *patternField;
    QPushButton *findPattern;
    QScrollArea *hexWidget;
    QWidget *scrollAreaWidgetContents;
    QPushButton *dumpModule;
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(926, 478);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        refreshButton = new QPushButton(centralWidget);
        refreshButton->setObjectName(QStringLiteral("refreshButton"));
        sizePolicy.setHeightForWidth(refreshButton->sizePolicy().hasHeightForWidth());
        refreshButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(refreshButton);

        processList = new QComboBox(centralWidget);
        processList->setObjectName(QStringLiteral("processList"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(processList->sizePolicy().hasHeightForWidth());
        processList->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(processList);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setCursor(QCursor(Qt::ArrowCursor));
        splitter->setAutoFillBackground(false);
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Plain);
        splitter->setMidLineWidth(0);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(2);
        splitter->setChildrenCollapsible(true);
        moduleList = new QTableWidget(splitter);
        moduleList->setObjectName(QStringLiteral("moduleList"));
        sizePolicy1.setHeightForWidth(moduleList->sizePolicy().hasHeightForWidth());
        moduleList->setSizePolicy(sizePolicy1);
        moduleList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        moduleList->setSelectionMode(QAbstractItemView::SingleSelection);
        moduleList->setSelectionBehavior(QAbstractItemView::SelectItems);
        moduleList->setSortingEnabled(true);
        splitter->addWidget(moduleList);
        moduleList->verticalHeader()->setStretchLastSection(false);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pagedStatusLayout = new QHBoxLayout();
        pagedStatusLayout->setSpacing(6);
        pagedStatusLayout->setObjectName(QStringLiteral("pagedStatusLayout"));
        refreshPaged = new QPushButton(verticalLayoutWidget);
        refreshPaged->setObjectName(QStringLiteral("refreshPaged"));
        sizePolicy.setHeightForWidth(refreshPaged->sizePolicy().hasHeightForWidth());
        refreshPaged->setSizePolicy(sizePolicy);

        pagedStatusLayout->addWidget(refreshPaged);

        amountUnpaged = new QProgressBar(verticalLayoutWidget);
        amountUnpaged->setObjectName(QStringLiteral("amountUnpaged"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(amountUnpaged->sizePolicy().hasHeightForWidth());
        amountUnpaged->setSizePolicy(sizePolicy3);
        amountUnpaged->setMaximum(0);
        amountUnpaged->setValue(0);

        pagedStatusLayout->addWidget(amountUnpaged);


        verticalLayout_2->addLayout(pagedStatusLayout);

        addressLayout = new QHBoxLayout();
        addressLayout->setSpacing(6);
        addressLayout->setObjectName(QStringLiteral("addressLayout"));
        curAddress = new QLineEdit(verticalLayoutWidget);
        curAddress->setObjectName(QStringLiteral("curAddress"));
        sizePolicy.setHeightForWidth(curAddress->sizePolicy().hasHeightForWidth());
        curAddress->setSizePolicy(sizePolicy);
        curAddress->setMaxLength(18);

        addressLayout->addWidget(curAddress);

        patternField = new QLineEdit(verticalLayoutWidget);
        patternField->setObjectName(QStringLiteral("patternField"));
        sizePolicy3.setHeightForWidth(patternField->sizePolicy().hasHeightForWidth());
        patternField->setSizePolicy(sizePolicy3);
        patternField->setMaxLength(1000);
        patternField->setClearButtonEnabled(true);

        addressLayout->addWidget(patternField);

        findPattern = new QPushButton(verticalLayoutWidget);
        findPattern->setObjectName(QStringLiteral("findPattern"));
        sizePolicy.setHeightForWidth(findPattern->sizePolicy().hasHeightForWidth());
        findPattern->setSizePolicy(sizePolicy);

        addressLayout->addWidget(findPattern);


        verticalLayout_2->addLayout(addressLayout);

        hexWidget = new QScrollArea(verticalLayoutWidget);
        hexWidget->setObjectName(QStringLiteral("hexWidget"));
        hexWidget->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 391, 96));
        hexWidget->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(hexWidget);

        dumpModule = new QPushButton(verticalLayoutWidget);
        dumpModule->setObjectName(QStringLiteral("dumpModule"));

        verticalLayout_2->addWidget(dumpModule);

        splitter->addWidget(verticalLayoutWidget);

        verticalLayout->addWidget(splitter);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 926, 24));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        sizePolicy2.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy2);
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        refreshButton->setText(QApplication::translate("MainWindow", "Refresh", nullptr));
        refreshPaged->setText(QApplication::translate("MainWindow", "Refresh", nullptr));
#ifndef QT_NO_TOOLTIP
        amountUnpaged->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Percentage of data in RAM as opposed to being paged out to disk.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        curAddress->setInputMask(QString());
        curAddress->setPlaceholderText(QApplication::translate("MainWindow", "Enter Address", nullptr));
        patternField->setPlaceholderText(QApplication::translate("MainWindow", "Enter Pattern", nullptr));
        findPattern->setText(QApplication::translate("MainWindow", "Find Pattern", nullptr));
        dumpModule->setText(QApplication::translate("MainWindow", "Dump Module", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
