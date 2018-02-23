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
    void suppressImage(cv::Mat src);

private:
    int const size = 3;
    cv::Mat getMean(cv::Mat mag, int x, int y);
    cv::Mat getMeanImage(cv::Mat src, int size);
    cv::Mat getGradientMagnitude(cv::Mat src);
};


#endif //BOUNDARYDETECTOR_SPATIALSPARSENESSCONSTRAINT_H
