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
		w = cpx(w.real(), sign*abs(w.imag()));
	}
	// Invert back to outside of unit circle, and rotate.
	w = eiTheta*(1.0 + w) / (1.0 - w);
	return w;
}

cpx SlitMap::DtoH(cpx z){
	// Transform and scale to right half plane:
	cpx result = r*(z - eiTheta) / (z + eiTheta);
	// Make sure the unit circle is mapped exactly to the imag. axis
	if (result.real() < 0.0) {
		result = cpx(0, w.imag());
	}
	return result;
}

cpx SlitMap::slit(cpx z){
	cpx result;
	// Need to keep track of imaginary axis, to deal resultith branch cut
	bool onImAxis = (z.real() == 0);
	int sign = z.imag() / abs(z.imag());

	// Add slit of the correct size:
	result = s*sqrt(z*z + 1.0);

	// Slit is on real axis, so don't need to check if image is on im axis again
	if (onImAxis) {
		result = cpx(result.real(), sign*result.imag());
	}
	return result;
}

cpx SlitMap::HtoD(cpx z){
	return eiTheta*(1.0 + z) / (1.0 - z);
}

// TODO: write this properly.
cpx SlitMap::derivative(cpx z){
	cpx f = DtoH(z);
	cpx gf = slit(f);
	cpx fPrime = r*(1.0 / (z + eiTheta) - (z - eiTheta) / ((z + eiTheta)*(z + eiTheta)));
	cpx gPrimeF = s*(f / sqrt(f*f + 1.0));
	cpx hPrimeGF = eiTheta*(1.0 / (1.0 + gf) + (1.0 + gf) / ((1.0 - gf)*(1.0 - gf)));
	return fPrime*gPrimeF*hPrimeGF;
}

cpx SlitMap::nDeriv(cpx z) {
    double r = 0.00000000001;
    return (this->operator()(z + r*polar(1.0, arg(z))) - this->operator()(z))/r;
}

SlitMap::~SlitMap()
{
}
