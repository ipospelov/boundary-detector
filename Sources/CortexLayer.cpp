//
// Created by posiv on 12.02.18.
//

#include "CortexLayer.h"
#define PI 3.14

CortexLayer::CortexLayer(double theta, int n, double sigma, const Size &size, int k) : n(n),
                                                                                              gamma(gamma),
                                                                                              sigma(sigma), size(size),
                                                                                              k(k) {
    for(auto i = 1; i <= n; i++){
        filters.push_back(getGaussianKernel((i - 1)*PI*2/n));
    }
}

void CortexLayer::printKernel() {
    std::cout << "kernel = "<< std::endl << " "  << gaussianKernel << std::endl << std::endl;
}

Mat& CortexLayer::getDrg() {
    
}

Mat CortexLayer::getGaussianKernel(double theta) {

    gaussianKernel = Mat::zeros(size.height, size.width, CV_32FC1);

    const auto y_mid = (size.height-1) / 2.0;
    const auto x_mid = (size.width-1) / 2.0;

    const auto x_spread = 1. / (pow(k*sigma, 2)*2);
    const auto y_spread = 1. / (pow(k*sigma, 2)*2);

    const auto denominator = 8 * std::atan(1) * k*sigma * k*sigma;

    //std::vector<double> gauss_x, gauss_y;

    std::vector<std::vector<double> > gauss(
            size.width,
            std::vector<double>(size.height));


    //gauss_x.reserve(size.height);
    for (auto i = 0;  i < size.height;  ++i) {
        auto x = i - x_mid;
        for(auto j = 0; j < size.width; ++j){
            auto y = j - y_mid;
            gauss[i][j] = std::exp(-pow(x*std::cos(theta) + y*std::sin(theta), 2) * x_spread
                                   -pow(gamma,2) * pow(-x*std::sin(theta) + y*std::cos(theta), 2) * y_spread);
        }

        //gauss_x.push_back(std::exp(-x*x * x_spread));
    }

/*
    gauss_y.reserve(rows);
    for (auto i = 0;  i < rows;  ++i) {
        auto y = i - y_mid;
        gauss_y.push_back(std::exp(-y*y * y_spread));
    }
*/

    for (auto i = 0;  i < size.height;  ++i) {
        for (auto j = 0; j < size.width; ++j) {
            gaussianKernel.at<float>(j, i) = gauss[i][j] / denominator;
        }
    }

    return gaussianKernel;
}


