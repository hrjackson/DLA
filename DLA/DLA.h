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
#include <map>
#include <vector>
#include <algorithm>

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
    SlitMap(double d, double theta);
    cpx operator()(cpx z);
    double getLength();
    double getAngle();
};

class Particle {
private:
    // Key = original abs. value
    // Value = translated position
    map<double, cpx> line;
    double length;
    double tol;
    double theta;
    cpx eiTheta;
    // Initialise the line
    void initLine();
public:
    Particle(double length, double tol, double theta);
    void update(vector<SlitMap> s);
};

class DLA {
private:
    mt19937_64 generator;
    uniform_real_distribution<double> runif;
    vector<double> lengths;
    vector<Particle> particles;
    vector<SlitMap> slitMaps;
    int numParticles;
    double tol;
    void initParticlesAndLines();
    void moveParticles();
public:
    DLA(double alpha,
        double d,
        int numParticles,
        double tol,
        long long seed);
};

#endif /* defined(__DLA__DLA__) */
