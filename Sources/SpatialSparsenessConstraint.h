//
// Created by Ivan Kirov on 23.02.2018.
//

#ifndef BOUNDARYDETECTOR_SPATIALSPARSENESSCONSTRAINT_H
#define BOUNDARYDETECTOR_SPATIALSPARSENESSCONSTRAINT_H


#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>


class SpatialSparsenessConstraint {
public:
    SpatialSparsenessConstraint();
    void suppressImage(cv::Mat& src);

private:
    int const size = 3;
    cv::Mat getMeanMat(cv::Mat mag, int x, int y);
    cv::Mat getMeanImage(cv::Mat src, int size);
    cv::Mat getGradientMagnitude(cv::Mat src);
    float getMeanValue(cv::Mat src, float lowBoundary, float highBoundary);
    float getFirstNorm(cv::Mat mat);
    float getSecondNorm(cv::Mat mat);
    float getSparsness(cv::Mat hist);

};


#endif //BOUNDARYDETECTOR_SPATIALSPARSENESSCONSTRAINT_H
