//
// Created by posiv on 12.02.18.
//

#ifndef BOUNDARYDETECTOR_CORTEXLAYER_H
#define BOUNDARYDETECTOR_CORTEXLAYER_H

#include <opencv2/opencv.hpp>
using namespace cv;

class CortexLayer {

private:
    int n;
    double gamma;
    double sigma;
    Size size;
    int k;
    Mat gaussianKernel;
    std::vector<Mat> filters;

    Mat getGaussianKernel(double theta);
    Mat& getDrg();

public:
    CortexLayer(double theta, int n, double sigma, const Size &size, int k);
    void printKernel();

};


#endif //BOUNDARYDETECTOR_CORTEXLAYER_H
