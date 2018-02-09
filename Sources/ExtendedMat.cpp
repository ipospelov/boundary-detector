//
// Created by posiv on 07.02.18.
//

#include "ExtendedMat.h"

void ExtendedMat::copyFrom(Mat &src, float b, float g, float r) {
    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols; j++){
            this->at<Vec3b>(i,j)[0] = src.at<Vec3b>(i,j)[0] * b;
            this->at<Vec3b>(i,j)[1] = src.at<Vec3b>(i,j)[1] * g;
            this->at<Vec3b>(i,j)[2] = src.at<Vec3b>(i,j)[2] * r;
        }
    }
}

ExtendedMat::ExtendedMat(int rows, int cols, int type) : Mat(rows, cols, type) {

}