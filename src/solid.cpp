#include "solid.h"

using namespace boost::numeric::ublas;

Solid::Solid()
{}

Solid::Solid(Shade shade)
	:m_shade(shade)
{}

double Solid::DE(vector<double> ray)
{
	return 0.0f;
}

void Solid::setshade(Shade const& shade)
{
	m_shade = shade;
}

Shade Solid::getshade() const
{
	return m_shade;
}

void Solid::debug()
{
	std::cout << "solid\n";
}
