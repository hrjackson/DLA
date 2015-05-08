#include "SlitMap.h"


SlitMap::SlitMap(double d, double theta)
	:Map(d, theta)
{
	// Used in the operator() function:
	s = d / (d + 2);
	r = sqrt(1 / (s*s) - 1);

	// e^i*theta
	eiTheta = std::polar(1.0, theta);

	// Just so it's initialised:
	w = 0;
}

cpx SlitMap::operator()(cpx z) {
	// Transform and scale to right half plane:
	w = r*(z - eiTheta) / (z + eiTheta);
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
	w = eiTheta*(1.0 + w) / (1.0 - w);
	return w;
}


// TODO: write this properly.
cpx derivative(cpx z){
	return 0;
}

SlitMap::~SlitMap()
{
}
