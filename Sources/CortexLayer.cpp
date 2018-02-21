#include "CortexLayer.h"

CortexLayer::CortexLayer(double gamma, unsigned long n, double sigma, const Size &size, int k) : n(n),
                                                                                                 gamma(gamma),
                                                                                                 sigma(sigma), size(size),
                                                                                                  k(k) {
    double theta;
    for(auto i = 1; i <= n; i++){
        theta = (i - 1)*360/n;
        filters.push_back(getFilterKernel(theta));
        //derivativeGaussianKernel(theta, i - 1);
    }
}

void CortexLayer::printMat(Mat mat) {
    std::cout << "kernel = " << std::endl << " "  << mat << std::endl << std::endl;
}

Mat CortexLayer::getDrg(Mat srg) { return getMax(std::move(srg)); }
Mat CortexLayer::getDgr(Mat sgr) { return getMax(std::move(sgr)); }
Mat CortexLayer::getDby(Mat sby) { return getMax(std::move(sby)); }
Mat CortexLayer::getDyb(Mat syb) { return getMax(std::move(syb)); }


Mat CortexLayer::getMax(Mat src) {

    std::vector<Mat> arr(n);
    Mat max(src.rows, src.cols, CV_32FC1);
    src.convertTo(src, CV_32FC1);


    for(auto i = 0; i < n; i++){
        getD(i, src).copyTo(arr[i]);

    }

    arr[0].copyTo(max);

    for(auto i = 1; i < n; i++){
        cv::max(arr[i], max, max);
    }

    max.convertTo(max, CV_32FC1);
    normalize(max, max);
    return max;

}

Mat CortexLayer::getD(int index, Mat s) {

    Mat filtered(s.rows, s.cols, CV_32FC1);
    Mat filtered2(s.rows, s.cols, CV_32FC1);
    cv::filter2D(s, filtered,s.depth(), filters[index]);

    filtered.copyTo(filtered2);
    threshold(filtered, filtered, 0.0, 255,THRESH_TOZERO);

    filtered2 *= -1;
    threshold(filtered2, filtered2, 0.0, 255,THRESH_TOZERO);
    Mat rez = filtered - filtered2;

    return rez;

}


Mat CortexLayer::getFilterKernel(double theta) {

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
            gauss[i][j] = std::exp(-pow(x, 2) * x_spread
                                   -pow(gamma,2) * pow(y, 2) * y_spread);

            /*gauss[i][j] = std::exp(-pow(x*std::cos(0) + y*std::sin(0), 2) * x_spread
                                   -pow(gamma,2) * pow(-x*std::sin(0) + y*std::cos(0), 2) * y_spread);*/

        }

    }


    for (auto i = 0;  i < size.height;  ++i) {
        for (auto j = 0; j < size.width; ++j) {
            gaussianKernel.at<float>(j, i) = static_cast<float>(gauss[i][j] / denominator);
        }
    }

    derivativeGaussianKernel(gaussianKernel, theta);

    return gaussianKernel;
}

void CortexLayer::derivativeGaussianKernel(Mat& img,double theta) {

    Sobel(img, img, img.type(), 1, 0, 3);
    Point2f src_center(img.cols/2.0F, img.rows/2.0F);
    Mat rot_mat = getRotationMatrix2D(src_center, theta, 1.0);
    warpAffine(img, img, rot_mat, img.size());

}




