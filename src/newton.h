#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <math.h>
#include <complex>
#include "solid.h"
#include "shade.h"

class Newton : public Solid
	// http://images.math.cnrs.fr/La-methode-de-Newton-et-son-fractal-en-3D.html?lang=fr
{
public:
	Newton(Shade shade, double epsilon, int ordre);
	std::complex<double> P(std::complex<double> z);
	std::complex<double> P_1(std::complex<double> z);
	std::complex<double> P_2(std::complex<double> z);
	double DE(boost::numeric::ublas::vector<double> ray);
private:
	double m_epsilon;
	int m_ordre = 3;
};
