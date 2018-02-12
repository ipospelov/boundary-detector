#include "ConeLayer.h"

ConeLayer::ConeLayer(cv::Mat &source_image){

    splited_img = std::vector<cv::Mat>();
    cv::split(source_image, splited_img);
}

cv::Mat& ConeLayer::get_red_image() {

    return splited_img[2];

}

cv::Mat& ConeLayer::get_green_image() {

    return splited_img[1];

}

cv::Mat& ConeLayer::get_blue_image() {

    return splited_img[0];

}

cv::MatExpr ConeLayer::get_yellow_image() {

    return splited_img[1] * 0.5 + splited_img[2] * 0.5;

}

void ConeLayer::reinit(cv::Mat &source_image) {
    cv::split(source_image, splited_img);
}
