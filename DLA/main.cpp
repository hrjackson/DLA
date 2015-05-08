//
//  main.cpp
//  DLA
//
//  Created by Henry Jackson on 29/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include <iostream>

#include "Plot.h"
#include "HLSlit.h"
#include "PlotDLA.h"

int main(int argc, const char * argv[]) {
    // Parameters for DLA
    double alpha = 0.3;
	double sigma = 0.1;
    double d = 0.2;
	
    int numParticles = 250;
    double tol = 0.025;
    int nLoops = 0;
    double firstLoop = 0.1;
    double loopSpacing = 0.0005;
    //double tol = 0.1;
    long long seed = 2;
    
    // Parameters for Plot
    int height = 500;
    int width = 500;
    int scale = 20;

    
    // Code starts:
    HLSlit hls(alpha, d, sigma, numParticles, tol, nLoops, firstLoop, loopSpacing, seed);
    Plot pl(width, height, scale);
    
    plotDLA(hls, pl);
    pl.show();
    pl.output("alpha03particles25000.png");
    
    return 0;
}
