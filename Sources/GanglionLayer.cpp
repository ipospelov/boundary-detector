//
// Created by posiv on 10.02.18.
//

#include "GanglionLayer.h"

GanglionLayer::GanglionLayer(float w1, float w2, float sigma, const Mat &red, const Mat &green, const Mat &blue,
                             const Mat &yellow) : w1(w1), w2(w2), sigma(sigma), red(red), green(green), blue(blue),
                                                  yellow(yellow) {}
