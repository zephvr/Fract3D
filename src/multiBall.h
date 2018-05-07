#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "solid.h"
#include "shade.h"

class MultiBall : public Solid
{
public:
	MultiBall(double space, double radius, Shade shade);
	double DE(boost::numeric::ublas::vector<double> ray);
	void debug();
private:
	double m_radius, m_space;
};