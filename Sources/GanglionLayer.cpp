//
// Created by posiv on 10.02.18.
//

#include "GanglionLayer.h"

GanglionLayer::GanglionLayer(float w1, float w2, float sigma, const Mat &red, const Mat &green, const Mat &blue,
                             const Mat &yellow) : w1(w1), w2(w2), sigma(sigma), red(red), green(green), blue(blue),
                                                  yellow(yellow) {
    initBluredImages();
}

void GanglionLayer::initBluredImages() {

    GaussianBlur(red, Cr, Size(3,3), sigma, sigma);

    GaussianBlur(green, Cg, Size(3,3), sigma, sigma);

    GaussianBlur(blue, Cb, Size(3,3), sigma, sigma);

    GaussianBlur(yellow, Cy, Size(3,3), sigma, sigma);

}

void GanglionLayer::reInitImages(const Mat &redImage, const Mat &greenImage, const Mat &blueImage, const Mat &yellowImage) {
    red = redImage;
    green = greenImage;
    blue = blueImage;
    yellow = yellowImage;
}


MatExpr GanglionLayer::getSRG() {
    return w1 * Cr + w2 * Cg;
}

MatExpr GanglionLayer::getSGR() {
    return w1 * Cg + w2 * Cr;
}

MatExpr GanglionLayer::getSBY() {
    return w1 * Cb + w2 * Cy;
}

MatExpr GanglionLayer::getSYB() {
    return w1 * Cy + w2 * Cb;
}

