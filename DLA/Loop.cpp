#include "Loop.h"

Loop::Loop(double radius, double tol) :tol(tol), radius(radius) {
	double twoPi = 2 * arg(cpx(-1, 0));
	double circumf = twoPi*radius;
	int nPoints = (int)(circumf / tol + 1);
	dTheta = twoPi / nPoints;
	for (double arg = 0; arg < twoPi + dTheta; arg += dTheta) {
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
	for (auto pointIt = next(loop.begin(), 1);
		pointIt != loop.end();
		++pointIt)
	{
		auto thisPoint = prev(pointIt, 1);
		if (abs(pointIt->second - thisPoint->second) > tol) {
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
	for (auto it = loop.begin(); it != loop.end(); ++it) {
		result.push_back(it->second);
	}
	return result;
}