//
//  DLA.cpp
//  DLA
//
//  Created by Henry Jackson on 29/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include "DLA.h"
#include <iostream>
#include <thread>

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
/*
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
	// Need to keep track of imaginary axis, to deal with branch cut
	bool onImAxis = (w.real() == 0);
	int sign = w.imag() / abs(w.imag());

    // Add slit of the correct size:
    w = s*sqrt(w*w + 1.0);

	// Slit is on real axis, so don't need to check if image is on im axis again
	if (onImAxis) {
		w = cpx(w.real(), sign*w.imag());
	}
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
    // First update the points already in the line:
    line[1.0] = pointUpdate(line[1.0], s);
    line[1.0 + length] = pointUpdate(line[1.0 + length], s);
    bool finished = false;
    int level = 1;
    while (!finished) {
        finished = adaptiveUpdate(s, level++);
		//cout << "Finished adaptive update level " << level - 1 << endl;
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
         ++pointIt)
    {
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
//// Loop member functions //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

Loop::Loop(double radius, double tol):tol(tol), radius(radius) {
    double twoPi = 2*arg(cpx(-1,0));
    double circumf = twoPi*radius;
    int nPoints = circumf/tol + 1;
    dTheta = twoPi/nPoints;
    for (double arg=0; arg < twoPi+dTheta; arg += dTheta) {
        loop[arg] = radius*polar(1.0, arg);
    }
}

void Loop::update(vector<SlitMap> s) {
    // First update the points already in the loop:
    for (auto it = loop.begin(); it != loop.end(); ++it) {
        loop[it->first] = pointUpdate(loop[it->first], s);
    }
    bool finished = false;
    int level = 1;
    while (!finished) {
        finished = adaptiveUpdate(s, level++);
    }
}

cpx Loop::pointUpdate(cpx z, vector<SlitMap> s) {
    for (auto mapIt = s.rbegin(); mapIt != s.rend(); ++mapIt) {
        z = (*mapIt)(z);
    }
    return z;
}

bool Loop::adaptiveUpdate(vector<SlitMap> s, int level) {
    double newTheta;
    double thetaIncrement = dTheta*pow(0.5, level);
    cpx z;
    bool finished = true;
    // Iterate over all points in the line:
    for (auto pointIt = next(loop.begin(),1);
         pointIt!= loop.end();
         ++pointIt)
    {
        auto thisPoint = prev(pointIt, 1);
        if (abs( pointIt->second - thisPoint->second ) > tol) {
            finished = false;
            newTheta = (thisPoint->first) + thetaIncrement;
            z = pointUpdate(polar(radius, newTheta), s);
            loop[newTheta] = z;
        }
    }
	cout << "Adaptive update level " << level << " finished" << endl;
    return finished;
}

vector<cpx> Loop::getLoop() {
    vector<cpx> result;
    for (auto it=loop.begin(); it!=loop.end(); ++it) {
        result.push_back(it->second);
    }
    return result;
}

*/
/////////////////////////////////////////////////////////////////////////////////
//// DLA member functions ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

DLA::DLA(double alpha,
         double d,
         int numParticles,
         double tol,
         int nLoops,
         double firstLoop,
         double loopSpacing,
         long long seed = chrono::system_clock::now().time_since_epoch().count())
:numParticles(numParticles), tol(tol), nLoops(nLoops), firstLoop(firstLoop),loopSpacing(loopSpacing)
{
    generator.seed(seed);
    lengths = vector<double>(numParticles, d);
    
    // Reserve enough memory
    particles.reserve(numParticles);
    slitMaps.reserve(numParticles);
    
    initParticlesAndLines();
    moveParticles();
    
    initLoops();
    moveLoops();
}

void DLA::initParticlesAndLines() {
    double twoPi = 2*arg(cpx(-1,0));
    double angle;
    for (int i=0; i<numParticles; ++i){
        angle = twoPi*runif(generator);
		//if (i == 0) {
		//	angle = 0;
		//}
		//else if (i == 1) {
		//	angle = twoPi - 0.1;
		//}
        particles.push_back(Particle(lengths[i], tol, angle));
        slitMaps.push_back(SlitMap(lengths[i], angle));
    }
}

void DLA::moveParticles() {
    if (numParticles < 100) {
        moveParticlesThr(0, numParticles, 0);
    }
    else {
        vector<thread> threads;
        int start;
        int end;
		int nThreads = 4;
        for (int i = 0; i<nThreads; ++i) {
            start = (double)numParticles*pow(((double)i/double(nThreads)), 0.35);
            end = (double)numParticles*pow(((double)(i+1)/double(nThreads)), 0.35);
            threads.push_back(thread(mem_fn(&DLA::moveParticlesThr), this, start, end, i));
        }
        // Wait for all threads to join:
        for (auto& th : threads) th.join();
    }
}

// Update the particles in the vector from
// startIndex (inclusive)
// to
// endIndex (not inclusive)
// Works backwards from endIndex-1 to startIndex.
void DLA::moveParticlesThr(int startIndex, int endIndex, int threadId) {
    double done;
    int total = endIndex - startIndex;
    int i = 1;
    int n = endIndex - 1;

	// Calculate end condition
	auto end = slitMaps.rend();
	if (startIndex != 0) {
		end = next(slitMaps.rbegin(), numParticles - startIndex + 1);
	}

	// Iterate over the correct range
	// Add 1 because nth particle goes through n-1th map, not nth. 
    for (auto it = next(slitMaps.rbegin(), numParticles - endIndex + 1);
         it != end;
         it++)
    {
        done = (double)i++/(double)total * 100;
        cout << "Thread " << threadId << ": " << done << "%" << endl;
		//cout << "Updating particle " << n << endl;
        particles[n--].update(vector<SlitMap>(it, slitMaps.rend()));
    }
}

void DLA::initLoops() {
    for (int i=0; i < nLoops; ++i) {
        loops.push_back(Loop(1 + firstLoop + i*loopSpacing, tol));
    }
}


void DLA::moveLoops() {
    vector<thread> threads;
    for (auto it = loops.begin(); it != loops.end(); ++it) {
        threads.push_back(thread(mem_fn(&Loop::update), it, slitMaps));
    }
    for (auto& th: threads) th.join();
}


vector<Particle> DLA::getParticles() {
    return particles;
}

vector<Loop> DLA::getLoops() {
    return loops;
}