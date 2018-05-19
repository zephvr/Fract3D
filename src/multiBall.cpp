#include "multiBall.h"

using namespace boost::numeric::ublas;

MultiBall::MultiBall(double space, double radius, Shade shade)
	:m_radius(radius), m_space(space)
{
	m_shade = shade;
}

double MultiBall::DE(vector<double> ray)
{
	double x = ray(0), y = ray(1), z = ray(2), n = 0;
	//std::cout << "before " << x << " " << y << " " << z << "\n";
	x = abs(x - m_space * (int)(x / m_space)) - m_space / 2.0;
	y = abs(y - m_space * (int)(y / m_space)) - m_space / 2.0;
	z = z - m_space / 2.0;
	//std::cout << "after1 " << x << " " << y << " " << z << "\n";
	//std::cout << "after3 " << x << " " << y << " " << z << "\n\n";
	n = sqrt(x*x + y*y + z*z) - m_radius;
	return n;
}

void MultiBall::debug()
{
	std::cout << "multiBall\n";
}
