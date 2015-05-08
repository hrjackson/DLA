#pragma once
#include "HL.h"
#include "Particle.h"

class HLSlit :
	public HL
{
private:
	/*--- Data ---*/
	double d;
	vector<SlitMap> maps;
	vector<Particle> particles;
	/*--- Functions ---*/
	void initLengthsAndMaps();
	void moveParticles();
	void moveParticlesThr(int startIndex, int endIndex, int threadId);
	void moveLoops();
public:
	HLSlit(double alpha,
		double d,
		int numParticles,
		double tol,
		int nLoops,
		double firstLoop,
		double loopSpacing,
		long long seed);
	vector<Particle> getParticles();
	~HLSlit();
};

