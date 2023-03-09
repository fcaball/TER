#include "mainwindow.h"
#include <QApplication>
#include "opencv2/opencv.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    using namespace cv;
        Mat image = imread("/home/fabien/Documents/FDS/M1/TER/data/imageGauche.ppm");
        imshow("Output", image);
    return a.exec();
}
