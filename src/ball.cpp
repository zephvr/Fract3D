# include "ball.h"

using namespace boost::numeric::ublas;

Ball::Ball(vector<double> &center, double radius, Shade &shade)
{
	m_center = center;
	m_radius = radius;
	m_shade = shade;
}

double Ball::DE(vector<double> ray)
{
	return std::max(0.0, norm_2(ray - m_center) - m_radius);
}

void Ball::debug()
{
	std::cout << "ball";
}
