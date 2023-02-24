/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_pictures_folder;
    QAction *actionZoom;
    QAction *actionZoom_2;
    QAction *actionCaracteristics_extraction;
    QAction *actionCorrespondance;
    QAction *actionTriangulation;
    QAction *actionContact_us;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTreeView *treeView;
    QLabel *picture1;
    QLabel *picture2;
    QMenuBar *menuBar;
    QMenu *menuTools;
    QMenu *menu3D_reconsruct;
    QMenu *menuHelp;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1300, 689);
        actionOpen_pictures_folder = new QAction(MainWindow);
        actionOpen_pictures_folder->setObjectName(QStringLiteral("actionOpen_pictures_folder"));
        QFont font;
        font.setFamily(QStringLiteral("OpenSymbol"));
        actionOpen_pictures_folder->setFont(font);
        actionOpen_pictures_folder->setMenuRole(QAction::ApplicationSpecificRole);
        actionZoom = new QAction(MainWindow);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionZoom_2 = new QAction(MainWindow);
        actionZoom_2->setObjectName(QStringLiteral("actionZoom_2"));
        actionCaracteristics_extraction = new QAction(MainWindow);
        actionCaracteristics_extraction->setObjectName(QStringLiteral("actionCaracteristics_extraction"));
        actionCorrespondance = new QAction(MainWindow);
        actionCorrespondance->setObjectName(QStringLiteral("actionCorrespondance"));
        actionTriangulation = new QAction(MainWindow);
        actionTriangulation->setObjectName(QStringLiteral("actionTriangulation"));
        actionContact_us = new QAction(MainWindow);
        actionContact_us->setObjectName(QStringLiteral("actionContact_us"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1210, 600, 80, 23));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 10, 211, 581));
        treeView->setAutoFillBackground(false);
        picture1 = new QLabel(centralWidget);
        picture1->setObjectName(QStringLiteral("picture1"));
        picture1->setGeometry(QRect(270, 40, 471, 451));
        picture1->setScaledContents(true);
        picture2 = new QLabel(centralWidget);
        picture2->setObjectName(QStringLiteral("picture2"));
        picture2->setGeometry(QRect(800, 40, 471, 451));
        picture2->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1300, 20));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menu3D_reconsruct = new QMenu(menuBar);
        menu3D_reconsruct->setObjectName(QStringLiteral("menu3D_reconsruct"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menu3D_reconsruct->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuTools->addAction(actionZoom);
        menuTools->addAction(actionZoom_2);
        menu3D_reconsruct->addAction(actionCaracteristics_extraction);
        menu3D_reconsruct->addAction(actionCorrespondance);
        menu3D_reconsruct->addAction(actionTriangulation);
        menuHelp->addAction(actionContact_us);
        menuFile->addAction(actionOpen_pictures_folder);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen_pictures_folder->setText(QApplication::translate("MainWindow", "Open pictures folder", 0));
        actionZoom->setText(QApplication::translate("MainWindow", "Zoom +", 0));
        actionZoom_2->setText(QApplication::translate("MainWindow", "Zoom -", 0));
        actionCaracteristics_extraction->setText(QApplication::translate("MainWindow", "Caracteristics extraction", 0));
        actionCorrespondance->setText(QApplication::translate("MainWindow", "Correspondance", 0));
        actionTriangulation->setText(QApplication::translate("MainWindow", "Triangulation", 0));
        actionContact_us->setText(QApplication::translate("MainWindow", "Contact us", 0));
        pushButton->setText(QApplication::translate("MainWindow", "3D PRINT", 0));
        picture1->setText(QString());
        picture2->setText(QString());
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menu3D_reconsruct->setTitle(QApplication::translate("MainWindow", "3D reconsruct", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
