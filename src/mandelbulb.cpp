#include "mandelbulb.h"

using namespace boost::numeric::ublas;

Mandelbulb::Mandelbulb(Shade shade, int iter, int ordre)
	:m_iter(iter), m_ordre(ordre)
{
	m_shade = shade;
}

double Mandelbulb::DE(vector<double> ray)
{
	vector<double> pos(ray), bis;
	bis.resize(3);
	bis(0) = 0; bis(1) = 0; bis(2) = 0;
	double dr(1), r(0), theta(0), phi(0), x(0), y(0), z(0);
	for (int i = 1; i < m_iter; i++)
	{
		x = pos(0); y = pos(1); z = pos(2);
		r = norm_2(pos);
		if (r > 1000.0) { break; }
		theta = m_ordre * atan(y / x);
		phi = m_ordre * asin(z / r);
		bis(0) = cos(theta)*cos(phi);
		bis(1) = sin(theta)*cos(phi);
		bis(2) = -sin(phi);
		pos = pow(r, m_ordre) * bis + ray;
		dr = m_ordre*dr*pow(r, m_ordre - 1) + 1;
	}
	dr = 1.0 / 2.0 * r * log(r) / dr;
	return dr;
}
