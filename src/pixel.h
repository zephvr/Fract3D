#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "solid.h"

struct RGB
{
	char r, g, b;
};

struct Pixel
{
	double distance; //buffer
	boost::numeric::ublas::vector<double> pos; //enregistre la position de l'objet
	boost::numeric::ublas::vector<double> normal; // la normal de l'object
	bool shadow = false; //indique si le pixel est a l'ombre
	bool collision = false; // indique si collision avec un solide (true) ou un object trop loin pour afficher le "ciel" (false)
	Solid *solid; // le solide rencontré
	int numIter; // le nombre d'iteration qui a été nécessaire pour atteindre l'objet
	RGB color; // color of the final pixel
};