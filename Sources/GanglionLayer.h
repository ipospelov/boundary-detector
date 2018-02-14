//
// Created by posiv on 10.02.18.
//
#include <opencv2/opencv.hpp>
#ifndef BOUNDARYDETECTOR_GANGLIONLAYER_H
#define BOUNDARYDETECTOR_GANGLIONLAYER_H
using namespace cv;

class GanglionLayer {
private:
    float w1;
    float w2;
    float sigma;
    Mat red;
    Mat green;
    Mat blue;
    Mat yellow;

    Mat Cr;
    Mat Cg;
    Mat Cb;
    Mat Cy;

    void initBluredImages();


public:

    GanglionLayer(float w1, float w2, float sigma, const Mat &red, const Mat &green, const Mat &blue,
                  const Mat &yellow);

    void reInitImages(const Mat &red, const Mat &green, const Mat &blue, const Mat &yellow);

    MatExpr getSRG();

    MatExpr getSGR();

    MatExpr getSBY();

    MatExpr getSYB();



};


#endif //BOUNDARYDETECTOR_GANGLIONLAYER_H
