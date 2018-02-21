//
// Created by posiv on 12.02.18.
//

#ifndef BOUNDARYDETECTOR_CORTEXLAYER_H
#define BOUNDARYDETECTOR_CORTEXLAYER_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

class CortexLayer {

private:
    unsigned long n;
    double gamma;
    double sigma;
    Size size;
    int k;
    std::vector<Mat> filters;

    Mat getFilterKernel(double theta);
    Mat getMax(Mat src);
    void derivativeGaussianKernel(Mat& img,double theta);
    Mat getD(int index, Mat s);

public:
    CortexLayer(double theta, unsigned long n, double sigma, const Size &size, int k);
    void printMat(Mat mat);
    Mat getDrg(Mat srg);
    Mat getDgr(Mat sgr);
    Mat getDby(Mat sby);
    Mat getDyb(Mat syb);





};


#endif //BOUNDARYDETECTOR_CORTEXLAYER_H
