#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <math.h>
#include "solid.h"
#include "shade.h"

class Mandelbulb : public Solid
	// http://bugman123.com/Hypercomplex/
{
public:
	Mandelbulb(Shade shade, int iter, int ordre);
	double DE(boost::numeric::ublas::vector<double> ray);
private:
	int m_iter;
	int m_ordre = 3;
};