#pragma once

#include <iostream>

class Color
	// class implementant la couleur RGB
{
public:
	Color();
	Color(Color const& c);
	Color(double R, double G, double B);
	double getR();
	double getG();
	double getB();
	void afficher(std::ostream &flux) const;
	Color& operator=(Color const& a);
	Color& operator+=(Color const& a);
	Color& operator*=(Color const& a);
	Color& operator*=(double const& a);

private:
	double m_R;
	double m_G;
	double m_B;
};

std::ostream& operator<<(std::ostream &flux, Color const& color);
Color operator+(Color const& a, Color const& b);
Color operator*(Color const& a, Color const& b);
Color operator*(Color const& a, double const& b);
Color operator*(double const& a, Color const& b);

//quelques couleurs
#define WHITE Color(1, 1, 1)
#define BLACK Color(0, 0, 0)
#define RED Color(1, 0, 0)
#define GREEN Color(0, 1, 0)
#define BLUE Color(0, 0, 1)
#define GOLD Color(1, 0.8431372549019608, 0)
