#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <math.h>
#include "solid.h"
#include "shade.h"

class Mandelbrot : public Solid
	// http://bugman123.com/Hypercomplex/
{
public:
	Mandelbrot(Shade shade, int ordre);
	double DE(boost::numeric::ublas::vector<double> ray);
private:
	int m_iter;
	int m_ordre = 3;
};