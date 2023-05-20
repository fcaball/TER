#ifndef IMAGES_H
#define IMAGES_H

#include "images.h"
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <QStringListModel>
#include <vector>
#include "mainwindow.h"


using namespace cv;
class images
{
    Mat src, src_gray;
    int thresh = 200;
    int max_thresh = 255;
    const char *source_window = "Source image";
    const char *corners_window = "Corners detected";
    const int draw_multiplier = 16;
    const int draw_shift_bits = 4;
    MainWindow *window;


    public:
        images(MainWindow *currentwindow);
        void drawMatche(InputArray img1, const std::vector<KeyPoint> &keypoints1,
                        InputArray img2, const std::vector<KeyPoint> &keypoints2,
                        const std::vector<DMatch> &matches1to2, InputOutputArray outImg);

        void getCaracteristiques(QString in,QString out, int nb);

        void drawMatches_(InputArray img1, const std::vector<KeyPoint> &keypoints1,
                          InputArray img2, const std::vector<KeyPoint> &keypoints2,
                          const std::vector<DMatch> &matches1to2, InputOutputArray outImg,
                          const int matchesThickness, const Scalar &matchColor,
                          const Scalar &singlePointColor, const std::vector<char> &matchesMask,
                          DrawMatchesFlags flags);

         void _prepareImgAndDrawKeypoints(InputArray img1, const std::vector<KeyPoint> &keypoints1,
                                                InputArray img2, const std::vector<KeyPoint> &keypoints2,
                                                InputOutputArray _outImg, Mat &outImg1, Mat &outImg2,
                                                const Scalar &singlePointColor, DrawMatchesFlags flags);

         void _prepareImage(InputArray src, const Mat &dst);

        void _drawMatch(InputOutputArray outImg, InputOutputArray outImg1, InputOutputArray outImg2,
                        const KeyPoint &kp1, const KeyPoint &kp2, const Scalar &matchColor, DrawMatchesFlags flags,
                        const int matchesThickness);

         inline void _drawKeypoint(InputOutputArray img, const KeyPoint &p, const Scalar &color, DrawMatchesFlags flags);

         bool reconstruction3D(QString arg1, QString arg2, QString arg3);



};

#endif // IMAGES_H
