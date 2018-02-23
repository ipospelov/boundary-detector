//
// Created by Ivan Kirov on 23.02.2018.
//

#include <opencv/cv.hpp>
#include <iostream>
#include "SpatialSparsenessConstraint.h"

SpatialSparsenessConstraint::SpatialSparsenessConstraint() {}

void SpatialSparsenessConstraint::suppressImage(cv::Mat src) {

    cv::normalize(src, src, 1, 0);
    cv::Mat mag = getGradientMagnitude(src);

    //cv::imshow( "Display src", src);                   // Show our image inside it.
    //cv::normalize(mag, mag, 255, 0);
    //cv::imshow( "Display mag", mag);                   // Show our image inside it.
    //cv::waitKey(0);
    //std::cout<< mag<< std::endl;


    //cv::calcHist(&mag, 1, 0, cv::Mat(), matHist, 1, &nHistSize, &fHistRange);
    //cv::imshow( "Display hist", matHist);                   // Show our image inside it.
    //cv::waitKey(0);

}

cv::Mat SpatialSparsenessConstraint::getGradientMagnitude(cv::Mat src) {

    cv::Mat Sx;
    cv::Mat Sy;
    cv::Sobel(src, Sx, CV_32FC1, 1, 0, 3);
    cv::Sobel(src, Sy, CV_32FC1, 0, 1, 3);
    cv::Mat mag;
    cv::magnitude(Sx, Sy, mag);
    getMean(mag, 100,100);
    return mag;

}

cv::Mat SpatialSparsenessConstraint::getMean(cv::Mat mag, int x, int y) {
    int xstart = x / size;
    int ystart = y / size;
    cv::Rect rect(xstart, ystart, size, size);
    cv::Mat roi = mag(rect);
    std::cout<<roi<<std::endl;
    float fRange[] = { 0.0f, 1.5f };
    int nHistSize = 100;
    const float* fHistRange = { fRange };
    cv::Mat matHist;
    cv::calcHist(&roi, 1, 0, cv::Mat(), matHist, 1, &nHistSize, &fHistRange);
    std::cout<<"HIST"<<std::endl;
    std::cout<<matHist<<std::endl;
    return matHist;

}


cv::Mat SpatialSparsenessConstraint::getMeanImage(cv::Mat src, int size) {
    return cv::Mat();
}

