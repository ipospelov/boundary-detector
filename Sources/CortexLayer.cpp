//
// Created by posiv on 12.02.18.
//

#include "CortexLayer.h"

#define PI 3.14

CortexLayer::CortexLayer(double gamma, unsigned long n, double sigma, const Size &size, int k) : n(n),
                                                                                                 gamma(gamma),
                                                                                                 sigma(sigma), size(size),
                                                                                                 k(k) {
    for(auto i = 1; i <= n; i++){
        filters.push_back(getGaussianKernel((i - 1)*PI*2/n));
       // printKernel(i-1);

    }
}

void CortexLayer::printKernel(int index) {
    std::cout << "kernel = "<< std::endl << " "  << filters[index] << std::endl << std::endl;
}

Mat CortexLayer::getDrg(Mat srg) { return getMax(std::move(srg)); }
Mat CortexLayer::getDgr(Mat sgr) { return getMax(std::move(sgr)); }
Mat CortexLayer::getDby(Mat sby) { return getMax(std::move(sby)); }
Mat CortexLayer::getDyb(Mat syb) { return getMax(std::move(syb)); }


Mat CortexLayer::getMax(Mat src) {

    std::vector<Mat> arr(n);
    Mat max(src.rows, src.cols, src.type());
    Mat filtered(src.rows, src.cols, src.type());

    for(auto i = 0; i < n; i++){
        cv::filter2D(src, filtered,src.depth(), filters[i]);
        filtered.copyTo(arr[i]);

    }

    arr[0].copyTo(max);

    for(auto i = 1; i < n; i++){
        cv::max(arr[i], max, max);
        //imshow( "Display max", max);                   // Show our image inside it.
        //waitKey(0);
    }

    max.convertTo(max, CV_32F);
    normalize(max, max);
    return max;


}


Mat CortexLayer::getGaussianKernel(double theta) {

    Mat gaussianKernel = Mat::zeros(size.height, size.width, CV_32FC1);

    const auto y_mid = (size.height-1) / 2.0;
    const auto x_mid = (size.width-1) / 2.0;

    const auto x_spread = 1. / (pow(k*sigma, 2)*2);
    const auto y_spread = 1. / (pow(k*sigma, 2)*2);

    const auto denominator = 8 * std::atan(1) * k*sigma * k*sigma;

    std::vector<std::vector<double> > gauss(
            size.width,
            std::vector<double>(size.height));


    for (auto i = 0;  i < size.height;  ++i) {
        auto x = i - x_mid;
        for(auto j = 0; j < size.width; ++j){
            auto y = j - y_mid;
            gauss[i][j] = std::exp(-pow(x*std::cos(theta) + y*std::sin(theta), 2) * x_spread
                                   -pow(gamma,2) * pow(-x*std::sin(theta) + y*std::cos(theta), 2) * y_spread);
        }

    }


    for (auto i = 0;  i < size.height;  ++i) {
        for (auto j = 0; j < size.width; ++j) {
            gaussianKernel.at<float>(j, i) = static_cast<float>(gauss[i][j] / denominator);
        }
    }

    return gaussianKernel;
}




