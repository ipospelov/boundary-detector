#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "ExtendedMat.h"

#define PI 3.14
#define SIGMA 0.5

using namespace cv;
using namespace std;

int main() {
    Mat img = imread( "/home/posiv/НГУ/BoundaryDetector/1.jpg", CV_LOAD_IMAGE_COLOR); // Открытие файла

    if(! img.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    vector<Mat> splitedImg = vector<Mat>();
    split(img, splitedImg);

/*
    ExtendedMat red = ExtendedMat(img.rows, img.cols, img.type());
    ExtendedMat green = ExtendedMat(img.rows, img.cols, img.type());
    ExtendedMat blue = ExtendedMat(img.rows, img.cols, img.type());
    ExtendedMat luminacity = ExtendedMat(img.rows, img.cols, img.type());

    red.copyFrom(img, 1.0, 0.0, 0.0);
    green.copyFrom(img, 0.0, 1.0, 0.0);
    blue.copyFrom(img, 0.0, 0.0, 1.0);
    luminacity.copyFrom(img, 0.5, 0.0 ,0.5);*/

    /*Cone layer*/

    Mat red;
    splitedImg[2].copyTo(red);

    Mat green;
    splitedImg[1].copyTo(green);

    Mat blue;
    splitedImg[0].copyTo(blue);

    Mat yellow = splitedImg[1] * 0.5 + splitedImg[2] * 0.5;


    /*//namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", yellow);                   // Show our image inside it.
    imshow( "Display window2", red);                   // Show our image inside it.
    imshow( "Display window3", green);                   // Show our image inside it.
    waitKey(0);
*/
    /* ________________________________*/
    /*LGN layer*/

    Mat Cr;
    red.copyTo(Cr);

    for(int i=0; i<Cr.rows; i++)
        for(int j=0; j<Cr.cols; j++) {
            Cr.at<cv::Vec3b>(i, j) *= exp(- (pow(i, 2) + pow(j, 2) / (2 * pow(SIGMA, 2)))) / (2 * PI * pow(SIGMA, 2));
            cout<< exp(- (pow(i, 2) + pow(j, 2) / (2 * pow(SIGMA, 2)))) / (2 * PI * pow(SIGMA, 2)) << endl;
        }

    imshow( "Display window3", Cr);                   // Show our image inside it.
    waitKey(0);



    return 0;

}