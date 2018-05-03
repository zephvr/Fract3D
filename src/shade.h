#pragma once
#include "color.h"

class Shade
{
public:
	Shade();
	Shade(const Shade &s);
	Shade(Color diffuse, Color specular, Color ambiante, double brillance);
	Shade& operator=(const Shade& s);
	Color getdiffuse();
	Color getspecular();
	Color getambiante();
	double getbrillance();
private:
	Color m_diffuse;
	Color m_specular;
	Color m_ambiante;
	double m_brillance;
};
