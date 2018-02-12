#ifndef BOUNDARYDETECTOR_CONELAYER_H
#define BOUNDARYDETECTOR_CONELAYER_H


#include <opencv2/core/mat.hpp>
#include <opencv/cv.hpp>


class ConeLayer {

private:

    std::vector<cv::Mat> splited_img;

public:

    ConeLayer(cv::Mat &source_image);

    cv::Mat& get_red_image();

    cv::Mat& get_green_image();

    cv::Mat& get_blue_image();

    cv::MatExpr get_yellow_image();

    void reinit(cv::Mat &source_image);
};


#endif //BOUNDARYDETECTOR_CONELAYER_H
