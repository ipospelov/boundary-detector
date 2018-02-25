//
// Created by Ivan Kirov on 23.02.2018.
//

#include <opencv/cv.hpp>
#include <iostream>
#include "SpatialSparsenessConstraint.h"

SpatialSparsenessConstraint::SpatialSparsenessConstraint() {}

void SpatialSparsenessConstraint::suppressImage(cv::Mat& src) {

    meanMats.clear();
    cv::normalize(src, src, 10, 0);
    cv::Mat mag = getGradientMagnitude(src);
    float mu, muCurr;
    cv::Mat meanMat;
    float meanValue;

    int shift = size*size;
    setMeanMats(mag);


    for(int y = 0; y < src.rows; y++){
        for(int x = 0; x < src.cols; x++){

            if((x % size*size == 0) || (y % size*size == 0)) {

                //meanMat = getMeanMat(mag, x, y);
                meanMat = meanMats[y / shift][x / shift];
                mu = getSparseness(meanMat);
                meanValue = getMeanValue(meanMat, 0.0f, 1.5f);
            }

            muCurr = mu;
            muCurr *= src.at<float>(y, x)/meanValue < 1 ? src.at<float>(y, x)/meanValue : 1;

            src.at<float>(y, x) *= muCurr;

        }
    }

}

void SpatialSparsenessConstraint::setMeanMats(cv::Mat mag) {

    int shift = size*size;

    for(int y = 0; y < mag.rows; y+=shift) {

        std::vector<cv::Mat> mats;

        for (int x = 0; x < mag.cols; x+=shift) {

            mats.push_back( getMeanMat(mag, x, y));

        }

        meanMats.push_back(mats);

    }

}

cv::Mat SpatialSparsenessConstraint::getGradientMagnitude(cv::Mat src) {

    cv::Mat Sx;
    cv::Mat Sy;
    cv::Sobel(src, Sx, CV_32FC1, 1, 0, 3);
    cv::Sobel(src, Sy, CV_32FC1, 0, 1, 3);
    cv::Mat mag;
    cv::magnitude(Sx, Sy, mag);
    return mag;

}

cv::Mat SpatialSparsenessConstraint::getMeanMat(cv::Mat mag, int x, int y) {

    int xstart = x / (size*size); //start of big quad
    int ystart = y / (size*size);

    float fRange[] = { 0.0f, 1.5f };
    int nHistSize = 1000;
    const float* fHistRange = { fRange };
    cv::Mat matHist; //histogram for small quad
    cv::Mat matOfMeans(1, size * size, CV_32FC1); //histogram for quad of quads

    for(auto i = 0; i < size; i++){
        for(auto j = 0; j < size; j++){

            int xshift = xstart + j * size;
            int yshift = ystart + i * size;

            cv::Rect rect(xstart + xshift, ystart + yshift, size, size); //small quad
            cv::Mat roi = mag(rect);
            cv::calcHist(&roi, 1, 0, cv::Mat(), matHist, 1, &nHistSize, &fHistRange);
            matOfMeans.at<float>(0, size * i + j) = getMeanValue(matHist, fRange[0], fRange[1]);

        }
    }

    return matOfMeans;

}


float SpatialSparsenessConstraint::getMeanValue(cv::Mat hist, float lowBoundary, float highBoundary) {

    int length = hist.rows;
    float shift = (highBoundary - lowBoundary) / length;
    cv::Point maxLoc;
    cv::minMaxLoc(hist, 0, 0, 0, &maxLoc);
    return (maxLoc.y + 1) * shift;

}

float SpatialSparsenessConstraint::getFirstNorm(cv::Mat mat) {

    float norm = 0;
    for(auto i = 0; i < mat.rows; i++){
        for(auto j = 0; j < mat.cols; j++){
            norm += mat.at<float>(i,j);
        }
    }
    return norm;

}

float SpatialSparsenessConstraint::getSecondNorm(cv::Mat mat) {

    float norm = 0;
    for(auto i = 0; i < mat.rows; i++){
        for(auto j = 0; j < mat.cols; j++){
            norm += std::pow(mat.at<float>(i,j), 2);
        }
    }
    return std::sqrt(norm);

}

float SpatialSparsenessConstraint::getSparseness(cv::Mat hist) {

    int n = hist.rows * hist.cols;
    float denominator = 1./(std::sqrt(n) - 1);
    float norm1 = getFirstNorm(hist);
    float norm2 = getSecondNorm(hist);
    //std::cout<<" norm1: "<<norm1/norm2<<" norm2: "<<norm2<<std::endl;

    return (std::sqrt(n) - norm1/norm2) * denominator;


}



