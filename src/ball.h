#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <algorithm> 
#include "solid.h"
#include "shade.h"

class Ball : public Solid
	// permet de représenter une sphere
{
public:
	Ball(boost::numeric::ublas::vector<double> &center, double radius, Shade &shade);
	double DE(boost::numeric::ublas::vector<double> ray);
	void debug();
private:
	boost::numeric::ublas::vector<double> m_center; // centre de la sphere

	double m_radius; // rayon de la sphere
};