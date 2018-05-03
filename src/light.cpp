#include "light.h"

using namespace boost::numeric::ublas;

Light::Light()
{}

Light::Light(int strength)
	:m_strength(strength)
{}

Shade Light::getShade()
{
	return m_shade;
}

vector<double> Light::getDir(vector<double> pos)
{
	return pos; //class abstraite ne pas executer
}
