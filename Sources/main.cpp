#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include "ExtendedMat.h"

#define PI 3.14
#define SIGMA 0.5
#define W1 0.9
#define W2 -0.9

using namespace cv;
using namespace std;

int main() {
    Mat img = imread( "/home/posiv/НГУ/BoundaryDetector/pictures/1.jpg", CV_LOAD_IMAGE_COLOR); // Открытие файла

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
    GaussianBlur(Cr, Cr, Size(3,3), SIGMA, SIGMA);

    Mat Cg;
    green.copyTo(Cg);
    GaussianBlur(Cg, Cg, Size(3,3), SIGMA, SIGMA);

    Mat Cb;
    blue.copyTo(Cb);
    GaussianBlur(Cb, Cb, Size(3,3), SIGMA, SIGMA);

    Mat Cy;
    yellow.copyTo(Cy);
    GaussianBlur(Cy, Cy, Size(3,3), SIGMA, SIGMA);

    /*for(int i=0; i<Cr.rows; i++)
        for(int j=0; j<Cr.cols; j++) {
            Cr.at<cv::Vec3b>(i, j) *= exp(- (pow(i, 2) + pow(j, 2) / (2 * pow(SIGMA, 2)))) / (2 * PI * pow(SIGMA, 2));
            cout<< exp(- (pow(i, 2) + pow(j, 2) / (2 * pow(SIGMA, 2)))) / (2 * PI * pow(SIGMA, 2)) << endl;
        }*/

    Mat Srg = W1 * Cr + W2 * Cg;
    Mat Sgr = W1 * Cg + W2 * Cr;
    Mat Sby = W1 * Cb + W2 * Cy;
    Mat Syb = W1 * Cy + W2 * Cb;

    /*_____________________*/
    /*Cortex Layer*/

    imshow( "Display window3", Sgr);                   // Show our image inside it.
    waitKey(0);



    return 0;

}

Mat getGaussianKernel(int rows, int cols, double sigmax, double sigmay, double theta, int k, double gamma){

    auto gauss_x = cv::getGaussianKernel(cols, k*sigmax, CV_32F);
    auto gauss_y = cv::getGaussianKernel(rows, k*sigmay/gamma, CV_32F);

    Mat dst = gauss_x * gauss_y.t();

    CvPoint2D32f center = cvPoint2D32f(dst.rows/2, dst.cols/2);
    Mat rot_mat = getRotationMatrix2D(center, theta, 1.0);
    warpAffine(dst, dst, rot_mat, dst.size());
    return dst;

}