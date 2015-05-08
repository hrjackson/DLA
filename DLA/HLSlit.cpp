#include "HLSlit.h"


HLSlit::HLSlit(double alpha,
	double d,
	int numParticles,
	double tol,
	int nLoops,
	double firstLoop,
	double loopSpacing,
	long long seed)
	:HL(alpha, d, numParticles, tol, nLoops, firstLoop, loopSpacing, seed), d(d)
{

	this->numParticles = numParticles;
	this->tol = tol;
	this->nLoops = nLoops;
	this->firstLoop = firstLoop;
	this->loopSpacing = loopSpacing;
	generator.seed(seed);
	// Reserve enough memory
	particles.reserve(numParticles);
	maps.reserve(numParticles);
	lengths.reserve(numParticles);

	initLengthsAndMaps();
	moveParticles();
	moveLoops();
}


void HLSlit::initLengthsAndMaps() {
	double twoPi = 2 * arg(cpx(-1, 0));
	double angle;
	for (int i = 0; i<numParticles; ++i){
		angle = twoPi*runif(generator);
		// Change this bit soon:
		lengths.push_back(d);
		particles.push_back(Particle(lengths[i], tol, angle));
		maps.push_back(SlitMap(lengths[i], angle));
	}
}

void HLSlit::moveParticles() {
	if (numParticles < 100) {
		moveParticlesThr(0, numParticles, 0);
	}
	else {
		vector<thread> threads;
		int start;
		int end;
		int nThreads = 4;
		for (int i = 0; i<nThreads; ++i) {
			start = (double)numParticles*pow(((double)i / double(nThreads)), 0.35);
			end = (double)numParticles*pow(((double)(i + 1) / double(nThreads)), 0.35);
			threads.push_back(thread(mem_fn(&HLSlit::moveParticlesThr), this, start, end, i));
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
void HLSlit::moveParticlesThr(int startIndex, int endIndex, int threadId) {
	double done;
	int total = endIndex - startIndex;
	int i = 1;
	int n = endIndex - 1;

	// Calculate end condition
	auto end = maps.rend();
	if (startIndex != 0) {
		end = next(maps.rbegin(), numParticles - startIndex + 1);
	}

	// Iterate over the correct range
	// Add 1 because nth particle goes through n-1th map, not nth. 
	for (auto it = next(maps.rbegin(), numParticles - endIndex + 1);
		it != end;
		it++)
	{
		done = (double)i++ / (double)total * 100;
		cout << "Thread " << threadId << ": " << done << "%" << endl;
		//cout << "Updating particle " << n << endl;
		particles[n--].update(vector<SlitMap>(it, maps.rend()));
	}
}

void HLSlit::moveLoops() {
	vector<thread> threads;
	for (auto it = loops.begin(); it != loops.end(); ++it) {
		threads.push_back(thread(mem_fn(&Loop::update), it, maps));
	}
	for (auto& th : threads) th.join();
}

vector<Particle> HLSlit::getParticles() {
	return particles;
}

HLSlit::~HLSlit()
{
}


