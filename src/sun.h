#pragma once

#include "light.h"
#include <boost/numeric/ublas/vector.hpp>

class Sun : public Light
	//  sun permet de simuler le comportement du soleil
{
public:
	Sun(boost::numeric::ublas::vector<double> way, int strength);
	boost::numeric::ublas::vector<double> getDir(boost::numeric::ublas::vector<double> pos);
private:
	boost::numeric::ublas::vector<double> m_way; // direction de l'eclairage
};
