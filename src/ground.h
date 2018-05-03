#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "solid.h"

class Ground: public Solid
{
public:
	Ground(double hight);
	double DE(boost::numeric::ublas::vector<double> ray);
	void debug();
private:
	double m_hight;
};
