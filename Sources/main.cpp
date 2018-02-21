#include <iostream>
#include <opencv2/opencv.hpp>
#include "CortexLayer.h"
#include "ConeLayer.h"
#include "GanglionLayer.h"

#define PI 3.14
#define SIGMA 0.3
#define W1 1
#define W2 (-0.6)
#define N0 16
#define GAMMA 0.5

using namespace cv;
using namespace std;

Mat perElementMax(std::initializer_list<Mat> list){
    Mat max;
    list.begin()->copyTo(max);
    for(const auto &elem : list){
        cv::max(max, elem, max);
    }
    return max;
}

int main() {

    Mat img = imread( "../pictures/1.jpg", CV_LOAD_IMAGE_COLOR);

    if(! img.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }


    ConeLayer coneLayer(img);

    Mat red = coneLayer.get_red_image();
    Mat green = coneLayer.get_green_image();
    Mat blue = coneLayer.get_blue_image();
    Mat yellow = coneLayer.get_yellow_image();


    GanglionLayer ganglionLayer(W1, W2, SIGMA, red, green, blue, yellow);

    Mat Srg = ganglionLayer.getSRG();//W1 * Cr + W2 * Cg;
    Mat Sgr = ganglionLayer.getSGR();//W1 * Cg + W2 * Cr;
    Mat Sby = ganglionLayer.getSBY();//W1 * Cb + W2 * Cy;
    Mat Syb = ganglionLayer.getSYB();//W1 * Cy + W2 * Cb;

//    imshow( "Display Srg", Srg);                   // Show our image inside it.
//    imshow( "Display Sgr", Sgr);                   // Show our image inside it.
//    imshow( "Display Sby", Sby);                   // Show our image inside it.
//    imshow( "Display Syb", Syb);                   // Show our image inside it.
//    waitKey(0);

    CortexLayer cortexLayer(GAMMA, N0, SIGMA, Size(7,7), 2);

    //TODO: DO из двух SO с противоположными ориентациями
    //f - мера, ROC кривые

    Mat Drg = cortexLayer.getDrg(Srg);
    Mat Dgr = cortexLayer.getDgr(Sgr);
    Mat Dby = cortexLayer.getDby(Sby);
    Mat Dyb = cortexLayer.getDyb(Syb);

    //normalize(Dyb, Dyb, 255, 0);

    Mat finalResponse = perElementMax({Drg, Dgr, Dby, Dyb});
    normalize(finalResponse, finalResponse, 255, 0);


    imshow( "Display final", finalResponse);                   // Show our image inside it.
    waitKey(0);

    return 0;

}

