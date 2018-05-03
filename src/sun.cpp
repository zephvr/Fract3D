#include "sun.h"

using namespace boost::numeric::ublas;

Sun::Sun(vector<double> way, int strength)
{
	m_way = way;
	m_strength = strength;
}

vector<double> Sun::getDir(vector<double> pos)
{
	return -m_way;
}
