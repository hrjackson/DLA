#include "Particle.h"

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
	for (auto pointIt = next(line.begin(), 1);
		pointIt != line.end();
		++pointIt)
	{
		auto thisPoint = prev(pointIt, 1);
		if (abs(pointIt->second - thisPoint->second) > tol) {
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
	for (auto it = line.begin(); it != line.end(); ++it) {
		result.push_back(it->second);
	}
	return result;
}

Particle::~Particle()
{
}