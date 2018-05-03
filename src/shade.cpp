#include "shade.h"

Shade::Shade()
{}

Shade::Shade(const Shade &s)
{
	m_diffuse = s.m_diffuse;
	m_specular = s.m_specular;
	m_ambiante = s.m_ambiante;
	m_brillance = s.m_brillance;
}

Shade::Shade(Color ambiante, Color diffuse, Color specular, double brillance)
	:m_diffuse(diffuse), m_specular(specular), m_ambiante(ambiante), m_brillance(brillance)
{}

Shade& Shade::operator=(Shade const& a)
{
	m_ambiante = a.m_ambiante;
	m_diffuse = a.m_diffuse;
	m_specular = a.m_specular;
	m_brillance = a.m_brillance;
	return *this;
}

Color Shade::getdiffuse()
{
	return m_diffuse;
}

Color Shade::getspecular()
{
	return m_specular;
}

Color Shade::getambiante()
{
	return m_ambiante;
}

double Shade::getbrillance()
{
	return m_brillance;
}
