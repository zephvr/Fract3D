#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "light.h"

class LightBall : public Light
	// lightball est tout simplement une boule de lumiere agit comme une source lumineuse secondaire apres sun
{
public:
	LightBall(boost::numeric::ublas::vector<double> center, int strength);
	boost::numeric::ublas::vector<double> getDir(boost::numeric::ublas::vector<double> pos);
private:
	boost::numeric::ublas::vector<double> m_center; // centre de la boule lumineuse
};
