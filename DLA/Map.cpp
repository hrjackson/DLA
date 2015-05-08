#include "Map.h"


Map::Map(double d, double theta) 
	:d(d), theta(theta){};

double Map::getLength() {
	return d;
}

double Map::getAngle() {
	return theta;
}

Map::~Map()
{
}
