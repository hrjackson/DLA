//
//  main.cpp
//  DLA
//
//  Created by Henry Jackson on 29/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include <iostream>

#include "Plot.h"
#include "DLA.h"
#include "PlotDLA.h"

int main(int argc, const char * argv[]) {
    // Parameters for DLA
    double alpha = 0;
    double d = 0.1/10;
    int numParticles = 100*1000;
    double tol = 0.025;
    //double tol = 0.1;
    long long seed = 1;
    
    // Parameters for Plot
    int height = 5000;
    int width = 5000;
    int scale = 200;

    
    // Code starts:
    DLA dla(alpha, d, numParticles, tol, seed);
    Plot pl(width, height, scale);
    
    PlotDLA(dla, pl);
    //pl.show();
    pl.output("Adaptive100000.png");
    
    return 0;
}
