#include "color.h"

Color::Color()
	:m_R(1), m_G(1), m_B(1)
{}

Color::Color(Color const& c)
{
	m_R = c.m_R;
	m_G = c.m_G;
	m_B = c.m_B;
}

Color::Color(double R, double G, double B)
{
	m_R = R;
	m_G = G;
	m_B = B;
}

double Color::getR()
{
	return m_R;
}

double Color::getG()
{
	return m_G;
}

double Color::getB()
{
	return m_B;
}

void Color::afficher(std::ostream &flux) const
{
	 flux << "R " << m_R << " G " << m_G << " B " << m_B;
}

Color& Color::operator=(Color const& c)
{
	m_R = c.m_R;
	m_G = c.m_G;
	m_B = c.m_B;
	return *this;
}

Color& Color::operator+=(Color const& a)
{
	m_R += a.m_R;
	m_G += a.m_G;
	m_B += a.m_B;
	if (m_R > 1) { m_R = 1; }
	if (m_G > 1) { m_G = 1; }
	if (m_B > 1) { m_B = 1; }
	return *this;
}

Color& Color::operator*=(Color const& a)
{
	m_R *= a.m_R;
	m_G *= a.m_G;
	m_B *= a.m_B;
	if (m_R > 1) { m_R = 1; }
	if (m_G > 1) { m_G = 1; }
	if (m_B > 1) { m_B = 1; }
	return *this;
}

Color& Color::operator*=(double const& a)
{
	m_R *= a;
	m_G *= a;
	m_B *= a;
	if (m_R > 1) { m_R = 1; }
	if (m_G > 1) { m_G = 1; }
	if (m_B > 1) { m_B = 1; }
	return *this;
}

std::ostream& operator<<(std::ostream &flux, Color const& color)
{
	color.afficher(flux);
	return flux;
}

Color operator+(Color const& a, Color const& b)
{
	Color result(a);
	result += b;
	return result;
}

Color operator*(Color const& a, Color const& b)
{
	Color copie(a);
	copie *= b;
	return copie;
}

Color operator*(Color const& a, double const& b)
{
	Color copie(a);
	copie *= b;
	return copie;
}

Color operator*(double const& a, Color const& b)
{
	return b * a;
}
