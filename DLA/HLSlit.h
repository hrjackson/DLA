#pragma once
#include "HL.h"
#include "Particle.h"

class HLSlit :
	public HL
{
private:
	/*--- Data ---*/
	double d;
	double sigma;
	vector<SlitMap> maps;
	vector<Particle> particles;
	/*--- Functions ---*/
    // Phi_n, the map to the plane minus particles [0->n]
    cpx phi(int n, cpx z);
    // Numerical esimate of abs value of the derivative of Phi_n
    double nDeriv(int n, cpx z);
	// The derivative of Phi_n, the map to the plane minus particles [0 -> n]. 
	// Phi_-1 = id, so derivative(-1, z) = 1.
	cpx derivative(int n, cpx z);
	// Returns the amount to divide d by to get length[n]
	double lengthScale(int n, double angle);
	void initLengthsAndMaps();
	void moveParticles();
	void moveParticlesThr(int startIndex, int endIndex, int threadId);
	void moveLoops();
    void testCase(int n, double real, double im);
public:
	HLSlit(double alpha,
		double d,
		double sigma,
		int numParticles,
		double tol,
		int nLoops,
		double firstLoop,
		double loopSpacing,
		long long seed);
	vector<Particle> getParticles();
    // Function compares derivative with numerical estimate.
    void testDeriv();
	~HLSlit();
};

