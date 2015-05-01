//
//  main.cpp
//  DLATest
//
//  Created by Henry Jackson on 30/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include <iostream>

#include "DLA.h"
#include "Plot.h"
#include "PlotDLA.h"

using namespace std;
using cpx = complex<double>;

int main(int argc, const char * argv[]) {
    // Parameters
    double dTheta = 0.1;
    int width = 1000;
    int height = 1000;
    int scale = 200;
    
    double twoPi = 2*arg(cpx(-1,0));
    // Construct the unit circle
    vector<cpx> circle;
    for (double arg = 0; arg < twoPi; arg += dTheta) {
        circle.push_back(cpx(polar(1.0, arg)));
    }
    
    SlitMap s(0.2, -0.1);
    SlitMap t(0.2, 0.0);
    vector<cpx> circImage;
    for (auto it=circle.begin(); it!= circle.end(); ++it) {
        circImage.push_back(t(*it, true));
    }
    
    // And the plot
    Plot pl(width, height, scale);
    pl.drawLoop(circle, Scalar(0,0,0));
    pl.drawLoop(circImage, Scalar(255,0,0));
    pl.show();
    
    
    
    return 0;
}
