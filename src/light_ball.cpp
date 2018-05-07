#include "light_ball.h"

using namespace boost::numeric::ublas;

LightBall::LightBall(vector<double> center, int strength)
	:m_center(center)
{
	m_strength = strength;
}

vector<double> LightBall::getDir(vector<double> pos)
{
	vector<double> dir;
	dir = m_center - pos;
	dir = dir / norm_1(dir);
	return dir;
}
