//
//  DLA.cpp
//  DLA
//
//  Created by Henry Jackson on 29/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include "DLA.h"

/////////////////////////////////////////////////////////////////////////////////
//// SlitMap member functions ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

SlitMap::SlitMap(const double d, const double theta)
:d(d), theta(theta) {
    // Used in the operator() function:
    s = d/(d + 2);
    r = sqrt(1/(s*s) - 1);
    
    // e^i*theta
    eiTheta = std::polar(1.0, theta);
    
    // Just so it's initialised:
    w = 0;
}

cpx SlitMap::operator()(const cpx z) {
    // Transform and scale to right half plane:
    w = r*(z - theta)/(z + theta);
    // Add slit of the correct size:
    w = s*sqrt(w*w + 1.0);
    // Invert back to outside of unit circle, and rotate.
    w = theta*(1.0 + w)/(1.0 - w);
    return w;
}

double SlitMap::getLength() {
    return d;
}

double SlitMap::getAngle() {
    return theta;
}


/////////////////////////////////////////////////////////////////////////////////
//// DLA member functions ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

DLA::DLA(double alpha,
         double d,
         int numParticles,
         double tol,
         long long seed = chrono::system_clock::now().time_since_epoch().count())
{
    generator.seed(seed);
}