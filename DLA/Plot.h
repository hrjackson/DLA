//
//  Plot.h
//  DLA
//
//  Created by Henry Jackson on 29/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#ifndef __DLA__Plot__
#define __DLA__Plot__

#include <stdio.h>
#include <vector>
#include <complex>
#include <string>
#include <sstream>
#include <iomanip>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

using cpx = std::complex<double>;

class Plot{
private:
    Mat image;
    int width;
    int height;
    int scale;
    // origin is in matrix coords in matrix coordinates
    Point origin;
    Point currentPosition;
public:
    Plot(int width, int height, int scale);
    ~Plot();
    void drawLine(cpx point, Scalar colour);
    void drawLine(vector<cpx> points, Scalar colour);
    void drawLoop(vector<cpx> points, Scalar colour);
    void drawCircle(cpx centre, double radius, Scalar colour);
    void output(const char* filename);
    void show();
    void clear();
    Point cpxToCV (cpx z);
    cpx CVTocpx(Point pt);
    Point getOrigin();
    // Return the min/max x or y, in complex corrdinates
    double minX();
    double maxX();
    double maxY();
    int rows();
    int cols();
};

#endif /* defined(__DLA__Plot__) */
