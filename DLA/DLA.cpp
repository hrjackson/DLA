//
//  DLA.cpp
//  DLA
//
//  Created by Henry Jackson on 29/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include "DLA.h"
#include <iostream>

// Useful general function, creates a sequence of points at angle theta.
// Straight line starting with abs value "from" etc...
vector<double> seq(double from,
                   double by,
                   double to) {
    vector<double> result;
    for (double pos = from; pos < to; pos += by) {
        result.push_back(pos);
    }
    return result;
}

/////////////////////////////////////////////////////////////////////////////////
//// SlitMap member functions ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

SlitMap::SlitMap(double d, double theta)
:d(d), theta(theta) {
    // Used in the operator() function:
    s = d/(d + 2);
    r = sqrt(1/(s*s) - 1);
    
    // e^i*theta
    eiTheta = std::polar(1.0, theta);
    
    // Just so it's initialised:
    w = 0;
}

cpx SlitMap::operator()(cpx z) {
    // Transform and scale to right half plane:
    w = r*(z - eiTheta)/(z + eiTheta);
    // Make sure the unit circle is mapped exactly to the imag. axis
    if (w.real() < 0.0) {
        w = cpx(0, w.imag());
    }
    // Add slit of the correct size:
    w = s*sqrt(w*w + 1.0);
    // Invert back to outside of unit circle, and rotate.
    w = eiTheta*(1.0 + w)/(1.0 - w);
    return w;
}

double SlitMap::getLength() {
    return d;
}

double SlitMap::getAngle() {
    return theta;
}

/////////////////////////////////////////////////////////////////////////////////
//// Particle member functions //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

Particle::Particle(double length, double tol, double theta)
:length(length), theta(theta), tol(tol){
    eiTheta = polar(1.0, theta);
    
    // Initialise the map with keys equal to abs values of values
    initLine();
}

void Particle::initLine() {
    line[1.0] = eiTheta;
    line[1.0 + length] = eiTheta*(1 + length);
}

// Update each point in the particle by each slit map in the vector
// TODO: add adaptivity in here!
void Particle::update(vector<SlitMap> s) {
    bool finished = false;
    int level = 1;
    while (!finished) {
        finished = adaptiveUpdate(s, level++);
    }
}

cpx Particle::pointUpdate(cpx z, vector<SlitMap> s) {
    for (auto mapIt = s.begin(); mapIt != s.end(); ++mapIt) {
        z = (*mapIt)(z);
    }
    return z;
}

bool Particle::adaptiveUpdate(vector<SlitMap> s, int level) {
    double absValue;
    double absIncrement = length*pow(0.5, level);
    cpx z;
    bool finished = true;
    // Iterate over all points in the line:
    for (auto pointIt = next(line.begin(),1);
         pointIt!= line.end();
         ++pointIt) {
        auto thisPoint = prev(pointIt, 1);
        if (abs( pointIt->second - thisPoint->second ) > tol) {
            finished = false;
            absValue = (thisPoint->first) + absIncrement;
            z = pointUpdate(eiTheta*absValue, s);
            line[absValue] = z;
        }
    }
    return finished;
}

vector<cpx> Particle::getLine() {
    vector<cpx> result;
    for (auto it=line.begin(); it!=line.end(); ++it) {
        result.push_back(it->second);
    }
    return result;
}


/////////////////////////////////////////////////////////////////////////////////
//// DLA member functions ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

DLA::DLA(double alpha,
         double d,
         int numParticles,
         double tol,
         long long seed = chrono::system_clock::now().time_since_epoch().count())
:numParticles(numParticles), tol(tol)
{
    generator.seed(seed);
    lengths = vector<double>(numParticles, d);
    
    // Reserve enough memory
    particles.reserve(numParticles);
    slitMaps.reserve(numParticles);
    
    initParticlesAndLines();
    moveParticles();
}

void DLA::initParticlesAndLines() {
    double twoPi = 2*arg(cpx(-1,0));
    double angle;
    for (int i=0; i<numParticles; ++i) {
        angle = twoPi*runif(generator);
        particles.push_back(Particle(lengths[i], tol, angle));
        slitMaps.push_back(SlitMap(lengths[i], angle));
    }
}

void DLA::moveParticles() {
    int n = numParticles-1;
    for (auto it = ++slitMaps.rbegin(); it != slitMaps.rend(); ++it) {
        cout << n << endl;
        particles[n--].update(vector<SlitMap>(it, slitMaps.rend()));
    }
}

vector<Particle> DLA::getParticles() {
    return particles;
}