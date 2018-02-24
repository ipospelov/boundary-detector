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
    getMeanMat(mag, 100,100);
    return mag;

}

cv::Mat SpatialSparsenessConstraint::getMeanMat(cv::Mat mag, int x, int y) {

    int xstart = x / std::pow(size, 2); //start of big quad
    int ystart = y / std::pow(size, 2);

    /*int xshift = (x % (int)std::pow(size, 2)) / size; //start of small quad in big quad
    int yshift = (y % (int)std::pow(size, 2)) / size;*/

    float fRange[] = { 0.0f, 1.5f };
    int nHistSize = 1000;
    const float* fHistRange = { fRange };
    cv::Mat matHist; //histogram for small quad
    cv::Mat matOfMeans(1, size * size, CV_32FC1); //histogram for quad of quads

    for(auto i = 0; i < size; i++){
        for(auto j = 0; j < size; j++){

            int xshift = xstart + j * size;
            int yshift = ystart + i * size;

            cv::Rect rect(xstart, ystart, size, size); //small quad
            cv::Mat roi = mag(rect);
            cv::calcHist(&roi, 1, 0, cv::Mat(), matHist, 1, &nHistSize, &fHistRange);
            matOfMeans.at<double>(size * i + j) = getMeanValue(matHist, fRange[0], fRange[1]);

        }
    }
    
    //std::cout<<matHist<<std::endl;
    //std::cout<<getMeanValue(matHist, fRange[0], fRange[1]);

    return matOfMeans;

}


float SpatialSparsenessConstraint::getMeanValue(cv::Mat hist, float lowBoundary, float highBoundary) {

    int length = hist.rows;
    float shift = (highBoundary - lowBoundary) / length;
    cv::Point maxLoc;
    cv::minMaxLoc(hist, 0, 0, 0, &maxLoc);
    return (maxLoc.y + 1) * shift;

}

