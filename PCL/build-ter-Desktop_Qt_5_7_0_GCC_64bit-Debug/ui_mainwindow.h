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
#include <QtWidgets/QCheckBox>
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
    QAction *actionExtraction_de_caract_ristiques;
    QAction *actionMise_en_correspondance;
    QAction *actionReconstruction_3D;
    QAction *actionZoom;
    QAction *actionZoom_2;
    QAction *actionOpen_folder;
    QAction *actionVisualisation_des_points_3D;
    QAction *actionNuage_de_point_final;
    QWidget *centralWidget;
    QPushButton *slideleft;
    QPushButton *slideright;
    QTreeView *treeView;
    QLabel *imagespace;
    QLabel *infosimage;
    QLabel *sliderholder;
    QCheckBox *checkBox;
    QMenuBar *menuBar;
    QMenu *menuOptions;
    QMenu *menuOutils;
    QMenu *menuHelp;
    QMenu *menuOpen;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1231, 816);
        QPalette palette;
        QBrush brush(QColor(170, 255, 127, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        MainWindow->setPalette(palette);
        actionExtraction_de_caract_ristiques = new QAction(MainWindow);
        actionExtraction_de_caract_ristiques->setObjectName(QStringLiteral("actionExtraction_de_caract_ristiques"));
        actionMise_en_correspondance = new QAction(MainWindow);
        actionMise_en_correspondance->setObjectName(QStringLiteral("actionMise_en_correspondance"));
        actionReconstruction_3D = new QAction(MainWindow);
        actionReconstruction_3D->setObjectName(QStringLiteral("actionReconstruction_3D"));
        actionZoom = new QAction(MainWindow);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionZoom_2 = new QAction(MainWindow);
        actionZoom_2->setObjectName(QStringLiteral("actionZoom_2"));
        actionOpen_folder = new QAction(MainWindow);
        actionOpen_folder->setObjectName(QStringLiteral("actionOpen_folder"));
        actionVisualisation_des_points_3D = new QAction(MainWindow);
        actionVisualisation_des_points_3D->setObjectName(QStringLiteral("actionVisualisation_des_points_3D"));
        actionNuage_de_point_final = new QAction(MainWindow);
        actionNuage_de_point_final->setObjectName(QStringLiteral("actionNuage_de_point_final"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QPalette palette1;
        QBrush brush1(QColor(113, 221, 116, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        centralWidget->setPalette(palette1);
        slideleft = new QPushButton(centralWidget);
        slideleft->setObjectName(QStringLiteral("slideleft"));
        slideleft->setGeometry(QRect(230, 0, 191, 401));
        slideright = new QPushButton(centralWidget);
        slideright->setObjectName(QStringLiteral("slideright"));
        slideright->setGeometry(QRect(1040, 0, 191, 401));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setGeometry(QRect(10, 1, 201, 401));
        QPalette palette2;
        QBrush brush2(QColor(0, 170, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        treeView->setPalette(palette2);
        imagespace = new QLabel(centralWidget);
        imagespace->setObjectName(QStringLiteral("imagespace"));
        imagespace->setGeometry(QRect(460, 20, 541, 361));
        QPalette palette3;
        QBrush brush3(QColor(85, 170, 127, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        imagespace->setPalette(palette3);
        infosimage = new QLabel(centralWidget);
        infosimage->setObjectName(QStringLiteral("infosimage"));
        infosimage->setGeometry(QRect(230, 410, 991, 161));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        infosimage->setPalette(palette4);
        sliderholder = new QLabel(centralWidget);
        sliderholder->setObjectName(QStringLiteral("sliderholder"));
        sliderholder->setGeometry(QRect(430, 0, 601, 391));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(920, 380, 101, 21));
        MainWindow->setCentralWidget(centralWidget);
        imagespace->raise();
        sliderholder->raise();
        slideleft->raise();
        slideright->raise();
        treeView->raise();
        infosimage->raise();
        checkBox->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1231, 20));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuOutils = new QMenu(menuBar);
        menuOutils->setObjectName(QStringLiteral("menuOutils"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuOpen = new QMenu(menuBar);
        menuOpen->setObjectName(QStringLiteral("menuOpen"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOpen->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuOutils->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuOptions->addAction(actionExtraction_de_caract_ristiques);
        menuOptions->addAction(actionMise_en_correspondance);
        menuOptions->addAction(actionVisualisation_des_points_3D);
        menuOptions->addAction(actionNuage_de_point_final);
        menuOptions->addAction(actionReconstruction_3D);
        menuOutils->addAction(actionZoom);
        menuOutils->addAction(actionZoom_2);
        menuOpen->addAction(actionOpen_folder);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionExtraction_de_caract_ristiques->setText(QApplication::translate("MainWindow", "Extraction de caract\303\251ristiques", 0));
        actionMise_en_correspondance->setText(QApplication::translate("MainWindow", "Mise en correspondance", 0));
        actionReconstruction_3D->setText(QApplication::translate("MainWindow", "Reconstruction 3D", 0));
        actionZoom->setText(QApplication::translate("MainWindow", "Zoom +", 0));
        actionZoom_2->setText(QApplication::translate("MainWindow", "Zoom - ", 0));
        actionOpen_folder->setText(QApplication::translate("MainWindow", "Open folder", 0));
        actionVisualisation_des_points_3D->setText(QApplication::translate("MainWindow", "Visualisation des points 3D", 0));
        actionNuage_de_point_final->setText(QApplication::translate("MainWindow", "Nuage de point final", 0));
        slideleft->setText(QString());
        slideright->setText(QString());
        imagespace->setText(QString());
        infosimage->setText(QString());
        sliderholder->setText(QString());
        checkBox->setText(QApplication::translate("MainWindow", "S\303\251lectionner", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
        menuOutils->setTitle(QApplication::translate("MainWindow", "Outils", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuOpen->setTitle(QApplication::translate("MainWindow", "Open", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
