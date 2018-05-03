#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "shade.h"

class Light
	//class abstraite regroupant toutes les sources lumineuse pouvant etre utilisée
{
public:
	Light();
	Light(int strength);
	virtual Shade getShade();
	virtual boost::numeric::ublas::vector<double> getDir(boost::numeric::ublas::vector<double> pos);

protected:
	int m_strength; // puissance de l'eclairage
	Shade m_shade; // cara lumineuse de la lumiere
};