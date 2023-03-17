#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <stdio.h>
#include <iostream>





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updatePictures(QString s1,int nb);


private slots:

    void on_actionOpen_pictures_folder_triggered();

    void on_actionZoom_triggered();

    void on_actionZoom_2_triggered();

    void on_actionCaracteristics_extraction_triggered();

    void on_actionCorrespondance_triggered();

    void on_actionTriangulation_triggered();

    void on_actionContact_us_triggered();

    void on_pushButton_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);




private:
    Ui::MainWindow *ui;
    QString currentDirectory;
    int lastPictureAdded;
    QString namePicture1;
    QString namePicture2;
    QString namePicture3;
};

#endif // MAINWINDOW_H
