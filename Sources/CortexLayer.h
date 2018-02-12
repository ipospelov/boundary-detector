//
// Created by posiv on 12.02.18.
//

#ifndef BOUNDARYDETECTOR_CORTEXLAYER_H
#define BOUNDARYDETECTOR_CORTEXLAYER_H

#include <opencv2/opencv.hpp>
using namespace cv;

class CortexLayer {

private:
    double theta;
    double gamma;
    double sigma;
    Size size;
    int k;
    Mat gaussianKernel;

    void getGaussianKernel();

public:
    CortexLayer(double theta, double gamma, double sigma, const Size &size, int k);
    void printKernel();

};


#endif //BOUNDARYDETECTOR_CORTEXLAYER_H
