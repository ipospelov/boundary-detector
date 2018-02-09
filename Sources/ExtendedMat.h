#include <opencv2/opencv.hpp>

using namespace cv;

class ExtendedMat : public Mat {

public:
    void copyFrom(Mat& src, float b, float g, float r);

    ExtendedMat(int rows, int cols, int type);

};

