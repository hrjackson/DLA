#include "HLSlit.h"


HLSlit::HLSlit(double alpha,
	double d,
	double sigma,
	int numParticles,
	double tol,
	int nLoops,
	double firstLoop,
	double loopSpacing,
	long long seed)
	:HL(alpha, d, numParticles, tol, nLoops, firstLoop, loopSpacing, seed), d(d), sigma(sigma)
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
    double proposalD;
    int i = 0;
	while (i<numParticles){
		angle = twoPi*runif(generator);
        proposalD = d/lengthScale(i, angle);
        
        //if (isfinite(proposalD)) {
            lengths.push_back(proposalD);
            particles.push_back(Particle(lengths[i], tol, angle));
            maps.push_back(SlitMap(lengths[i], angle));
            cout << "Length " << i << ": " << lengths[i] << endl;
            ++i;
        //}

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
		int nThreads = 8;
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

vector<SlitMap> HLSlit::getMaps() {
    return maps;
}

cpx HLSlit::phi(int n, cpx z) {
    if (n == -1) {
        return z;
    }
    else {
        return phi(n-1, maps[n](z));
    }
}

double HLSlit::nDeriv(int n, cpx z) {
    double r = 0.0000000001;
    return abs(phi(n, z + r* polar(1.0, arg(z)) ) - phi(n, z))/r;
}

cpx HLSlit::derivative(int n, cpx z) {
	if (n == -1)
	{
		return 1;
	}
	else
	{
		return maps[n].derivative(z)*derivative(n - 1, maps[n](z));
	}
}

double HLSlit::lengthScale(int n, double angle) {
	double result = 1;
	if (alpha != 0)
	{
		cpx point = polar(exp(sigma), angle);
        cpx deriv = derivative(n - 1, point);
		result = pow(abs(deriv), alpha / 2);
	}
	return result;
}

void HLSlit::testDeriv(){
    testCase(-1, 1.0, 1.0);
    testCase(0, 1.0, 1.0);
    testCase(numParticles-1, 1.0, 0.0);
    testCase(3, 3.5, 2.0);
    testCase(30, 200, 300);
    testCase(10, -20, -800);
}

void HLSlit::testCase(int n, double real, double im){
    cpx z(real, im);
    if (n >= 0) {
        cout << "Estimate of deriviate of phi_n" << endl;
        cout << maps[n].nDeriv(z) << endl;
        cout << "Symbolic value" << endl;
        cout << maps[n].derivative(z) << endl;
    }
    cout << "The value of Phi_" << n << endl;
    cout << phi(n, z) << endl;
    cout << "Numerical estimate at " << z << " for n = " << n << endl;
    cout << nDeriv(n, z) << endl;
    cout << "Actual value " << endl;
    cout << abs(derivative(n, z)) << endl << endl;
}


HLSlit::~HLSlit()
{
}


