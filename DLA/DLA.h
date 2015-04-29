//
//  DLA.h
//  DLA
//
//  Created by Henry Jackson on 29/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#ifndef __DLA__DLA__
#define __DLA__DLA__

#include <stdio.h>
#include <complex>
#include <cmath>
#include <random>

using namespace std;

using cpx = complex<double>;

class SlitMap {
private:
    double d;
    double theta;
    cpx eiTheta;
    double s;
    double r;
    // So we don't have to keep re-initialising cpx values
    cpx w;
public:
    SlitMap(const double d, const double theta);
    //SlitMap();
    cpx operator()(const cpx z);
    //cpx inverse(cpx w);
    double getLength();
    double getAngle();
};

class DLA {
private:
    mt19937_64 generator;
    uniform_real_distribution<double> runif;
public:
    DLA(double alpha, double d, double tol, long long seed);
};

#endif /* defined(__DLA__DLA__) */
