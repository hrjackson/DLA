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
#include "SlitMap.h"

int main(int argc, const char * argv[]) {
    // Parameters for DLA
    double alpha = 1;
	double sigma = 0.00000001;
    double d = 0.02;
	
    int numParticles = 25000;
    double tol = 0.05;
    int nLoops = 8;
    double firstLoop = 0.005;
    double loopSpacing = 0.005;
    
    //long long seed = 2;
    long long seed = chrono::system_clock::now().time_since_epoch().count();
    
    // Parameters for Plot
    int height = 10000;
    int width = 10000;
    int scale = 130;

    
    // Code starts:
    HLSlit hls(alpha, d, sigma, numParticles, tol, nLoops, firstLoop, loopSpacing, seed);
    
    //hls.testDeriv();
    
	// Create a slit map
	//SlitMap sm(0.3, 0.0);
	//sm.testMap();
    
    Plot pl(width, height, scale);
    
    plotDLA(hls, pl);
    //pl.show();
    pl.output("alpha1sigma00000001particles25000.png");

    return 0;
}
