#pragma once

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <math.h>

class Camera
	// il s'agit de la class gérant la dispertion des rayons partant de la camera
{
public:
	Camera(double yam, double pitch, double roll, double ratio, double open, boost::numeric::ublas::vector<double> position);
	boost::numeric::ublas::vector<double> getVector(int x, int y);
	int* getResolution();
	boost::numeric::ublas::vector<double> getPosition();
	void target(boost::numeric::ublas::vector<double> pos);
	void setYam(double const& yaw);
	void setPitch(double const& pitch);
	void setRoll(double const& roll);
	void setRatio(double const& ratio);
	void setOpen(double const& open);
	void setPosition(boost::numeric::ublas::vector<double> const& position);
	void setResolution(int const& x, int const& y);
private:
	int m_resolution[2]; // resolution de la scene
	double m_yaw, m_pitch, m_roll; // 3 angles de rotation de la camera en radian
	double m_ratio, m_open; // ratio donne le ratio de l'ecran (doit etre le meme que celui de la resolution) // open donne l'ouverture de la focale (permet des effets visuel)
	double m_alpha, m_beta; // variable de calcule
	boost::numeric::ublas::vector<double> m_x, m_y, m_z; // vecteurs de la nouvelle base orthonorme ayant pour origine la camera
	boost::numeric::ublas::vector<double> m_position; // vecteur position de la camera
	void xMake();
	void yMake();
	void zMake();
	void init();
};

void zeroing_vector(boost::numeric::ublas::vector<double> *vect);
boost::numeric::ublas::matrix<double> rotationalMatrix(boost::numeric::ublas::vector<double> const& vector, double const& angle);
void afficher(boost::numeric::ublas::matrix<double> mat);