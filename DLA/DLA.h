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
/*
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
    cpx pointUpdate(cpx z, vector<SlitMap> s);
    bool adaptiveUpdate(vector<SlitMap> s, int level);
public:
    Particle(double length, double tol, double theta);
    void update(vector<SlitMap> s);
    vector<cpx> getLine();
};


class Loop {
private:
    // Key = original argument
    // Value = translated position
    map<double, cpx> loop;
    double tol;
    cpx pointUpdate(cpx z, vector<SlitMap> s);
    bool adaptiveUpdate(vector<SlitMap> S, int level);
    double dTheta;
    double radius;
public:
    Loop(double radius, double tol);
    void update(vector<SlitMap> s);
    vector<cpx> getLoop();
};
*/
class DLA {
private:
    mt19937_64 generator;
    uniform_real_distribution<double> runif;
    vector<double> lengths;
    vector<Particle> particles;
    vector<SlitMap> slitMaps;
    vector<Loop> loops;
    int numParticles;
    double tol;
    int nLoops;
    double firstLoop;
    double loopSpacing;
    void initParticlesAndLines();
    void moveParticles();
    void initLoops();
    void moveLoops();
    void moveParticlesThr(int startIndex, int endIndex, int threadId);
public:
    DLA(double alpha,
        double d,
        int numParticles,
        double tol,
        int nLoops,
        double firstLoop,
        double loopSpacing,
        long long seed);
    vector<Particle> getParticles();
    vector<Loop> getLoops();
};

#endif /* defined(__DLA__DLA__) */
