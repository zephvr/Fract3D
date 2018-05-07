#include "camera.h"

using namespace boost::numeric::ublas;

Camera::Camera(double yam, double pitch, double roll, double ratio, double open, vector<double> position)
	:m_yaw(yam), m_pitch(pitch), m_roll(roll), m_ratio(ratio), m_open(open), m_position(position)
{
	zeroing_vector(&m_x);
	zeroing_vector(&m_y);
	zeroing_vector(&m_z);

	this->init();
	m_alpha = tanh(1 / m_open); //opening in hight
	m_beta = tanh(m_ratio / m_open); //opening in length
}

vector<double> Camera::getVector(int x, int y)
{
	matrix<double> R_yam(3, 3), R_pitch(3, 3);
	vector<double> way(3);
	R_yam = rotationalMatrix(m_z, m_beta*(1.0 - 2.0 * (double)x / (double)m_resolution[0]));
	R_pitch = rotationalMatrix(m_y, m_alpha*(2.0 * (double)y / (double)m_resolution[1] - 1.0));
	for (unsigned i(0); i < 3; ++i)
	{
		way(i) = 0;
	}
	way = prod(R_yam, m_x);
	way = prod(R_pitch, way);
	return way;
}

int* Camera::getResolution()
{
	return m_resolution;
}

vector<double> Camera::getPosition()
{
	return m_position;
}

void Camera::target(vector<double> pos)
{
	vector<double> dir = pos - m_position;
	m_x = dir / norm_2(dir);
	this->yMake();
	this->zMake();
}
void Camera::setYam(double const& yaw)
{
	m_yaw = yaw;
	this->init();
}

void Camera::setPitch(double const& pitch)
{
	m_pitch = pitch;
	this->init();
}

void Camera::setRoll(double const& roll)
{
	m_roll = roll;
	this->init();
}

void Camera::setRatio(double const& ratio)
{
	m_ratio = ratio;
	m_beta = tanh(m_ratio / m_open);
}

void Camera::setOpen(double const& open)
{
	m_open = open;
	m_alpha = tanh(1 / m_open);
	m_beta = tanh(m_ratio / m_open);
}

void Camera::setPosition(vector<double> const& position)
{
	m_position = position;
}

void Camera::setResolution(int const& x, int const& y)
{
	m_resolution[0] = x;
	m_resolution[1] = y;
}

void Camera::xMake()
{
	vector<double> x_axe(3), y_axe(3), z_axe(3);
	x_axe(0) = 1;
	x_axe(1) = 0;
	x_axe(2) = 0;
	y_axe(0) = 0;
	y_axe(1) = 1;
	y_axe(2) = 0;
	z_axe(0) = 0;
	z_axe(1) = 0;
	z_axe(2) = 1;
	matrix<double> R_yam(3, 3), R_pitch(3, 3);
	R_yam = rotationalMatrix(z_axe, m_yaw);
	R_pitch = rotationalMatrix(y_axe, m_pitch);
	m_x = prod(R_yam, x_axe);
	m_x = prod(R_pitch, m_x);
}

void Camera::yMake()
{
	m_y.resize(3);
	if (m_x(0) == 0)
	{
		m_y(0) = 1;
		m_y(1) = 0;
		m_y(2) = 0;
	}
	else
	{
		m_y(2) = 0;
		m_y(1) = 1 / sqrt(pow(m_x(1) / m_x(0), 2) + 1);
		m_y(0) = -m_x(1)*m_y(1) / m_x(0);
	}
}

void Camera::zMake()
{
	m_z.resize(3);
	if (m_x(0) == 0)
	{
		m_z(0) = 0;
		m_z(1) = 1;
		m_z(2) = 0;
	}
	else if (m_x(2) == 0)
	{
		m_z(0) = 0;
		m_z(1) = 0;
		m_z(2) = 1;
	}
	else if (m_y(0) == 0)
	{
		m_z(2) = 1 / sqrt(pow(m_x(2) / m_x(0), 2) + 1);
		m_z(1) = 0;
		m_z(0) = -m_z(2)*m_x(2) / m_x(0);
	}	
	else
	{
		m_z(1) = 1 / sqrt(pow(m_y(1) / m_y(0), 2) + 1 + pow(m_x(1) - m_x(0)*m_y(1) / m_y(0), 2) / pow(m_x(2), 2));
		m_z(0) = -m_z(1)*m_y(1) / m_y(0);
		m_z(2) = -(m_z(0)*m_x(0) + m_z(1)*m_z(1)) / m_x(2);
	}
}

void Camera::init()
{
	this->xMake();
	this->yMake();
	this->zMake();
	matrix<double> R_roll(3, 3);
	R_roll = rotationalMatrix(m_x, m_roll);
	m_y = prod(R_roll, m_y);
	m_z = prod(R_roll, m_z);
}

void zeroing_vector(vector<double> *vect)
	// fonction qui met a zero tous les composants d'un vecteur
{
	int l = vect->size(); // recupere la taille du vecteur et l'affecte a l
	for (int i(0); i < l; i++) // fait parcourir i de 0 a la taille du vecteur - 1 
	{
		(*vect)(i) = 0; // affecte la valeur 0 au i-ème element du vecteur
	}
}

matrix<double> rotationalMatrix(vector<double> const& vector, double const& angle)
	//cree une matrice de rotation autour d'un vecteur "vector" d'une rotation "angle" !!! en RADIAN !!!!
	//@return la matrice de rotation
{
	matrix<double> R(3, 3), Q(3,3);
	identity_matrix<double> I(3);
	Q(0, 0) = 0;
	Q(0, 1) = -vector(2);
	Q(0, 2) = vector(1);
	Q(1, 0) = vector(2);
	Q(1, 1) = 0;
	Q(1, 2) = -vector(0);
	Q(2, 0) = -vector(1);
	Q(2, 1) = vector(0);
	Q(2, 2) = 0;
	R = I + sin(angle)*Q + (1 - cos(angle))*prod(Q, Q);
	return R;
}

void afficher(boost::numeric::ublas::matrix<double> mat)
{
	int x = mat.size1(), y = mat.size2();
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
		{
			std::cout << mat(i, j);
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
