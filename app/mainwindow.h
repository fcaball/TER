#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <stdio.h>
#include <iostream>
#include <QKeyEvent>
#include <vector>





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updatePictures(QString s1);
    void keyPressEvent(QKeyEvent *e);


private slots:
private slots:
    void on_actionOpen_folder_triggered();

    int randomize(int low, int high);

    void previous_image();

    void next_image();

    void on_slideleft_clicked();

    void on_slideright_clicked();

    void start_animation();

    void end_animation();

    void renderImage();

    void setImage(QString chemin);

    void setImageInfos(QString chemin);


    void setAnimation();

    void infoImage();

    void on_actionZoom_triggered();

    void on_actionZoom_2_triggered();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_actionReconstruction_3D_triggered();

    void on_actionMise_en_correspondance_triggered();

    void on_actionExtraction_de_caract_ristiques_triggered();

    void on_checkBox_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    QString currentDirectory="";
    QString namePicture;

    QString image_directory[128], temp_directory;
    float anim_period = 0.5;
    QString PATH;
    int i=0;
    int count;
    bool timer_checker, comboBox_checker, image_checker, mouse_click_checker, anim_checker;

    std::vector<QString> ImagesSelectedForCorrespondance;
};

#endif // MAINWINDOW_H
