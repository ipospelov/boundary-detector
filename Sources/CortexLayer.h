//
// Created by posiv on 12.02.18.
//

#ifndef BOUNDARYDETECTOR_CORTEXLAYER_H
#define BOUNDARYDETECTOR_CORTEXLAYER_H

#include <opencv2/opencv.hpp>
using namespace cv;

class CortexLayer {

private:
    unsigned long n;
    double gamma;
    double sigma;
    Size size;
    int k;
    std::vector<Mat> filters;

    Mat getGaussianKernel(double theta);
    Mat getMax(Mat src);

public:
    CortexLayer(double theta, unsigned long n, double sigma, const Size &size, int k);
    void printKernel(int index);
    Mat getDrg(Mat srg);
    Mat getDgr(Mat sgr);
    Mat getDby(Mat sby);
    Mat getDyb(Mat syb);





};


#endif //BOUNDARYDETECTOR_CORTEXLAYER_H
