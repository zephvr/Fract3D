#include "ground.h"

using namespace boost::numeric::ublas;

Ground::Ground(double hight)
{
	m_hight = hight;
}
double Ground::DE(vector<double> ray)
{
	return ray(2) - m_hight;
}

void Ground::debug()
{
	std::cout << "ground\n";
}
