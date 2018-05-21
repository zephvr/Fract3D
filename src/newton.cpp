#include "newton.h"

using namespace boost::numeric::ublas;

Newton::Newton(Shade shade, double epsilon, int ordre)
	:m_epsilon(epsilon), m_ordre(ordre)
{
	m_shade = shade;
}

std::complex<double> Newton::P(std::complex<double> z)
{
	return pow(z, m_ordre) - 1;
}

std::complex<double> Newton::P_1(std::complex<double> z)
{
	return m_ordre * pow(z, m_ordre - 1);
}

std::complex<double> Newton::P_2(std::complex<double> z)
{
	return m_ordre * (m_ordre - 1) * pow(z, m_ordre - 2);
}

double Newton::DE(vector<double> pos)
{
	std::complex<double> z_n, z_np, dz_n, dz_np, ED;
        z_n = std::complex<double>(pos(0), pos(1));
	z_np = z_n - P(z_n)/P_1(z_n);
	dz_n = 0.1;
	dz_np = dz_n*P(z_n)*P_2(z_n)/pow(P_1(z_n), 2);
	int n = 0;	
	while (abs(z_np - z_n) > m_epsilon)
	{
		n += 1;
		z_n = z_np;
		z_np = z_n - P(z_n)/P_1(z_n);
		dz_n = dz_np;
		dz_np = dz_n*P(z_n)*P_2(z_n)/pow(P_1(z_n), 2);
	}
	ED = log(abs(z_np-z_n))*abs(z_np-z_n)/abs(dz_np-dz_n);
	double u = n + 1 + log(log(m_epsilon)/log(abs(z_np-z_n)))/log(2);
	ED += abs(pos(2) + 0.01/pow(u, 3));
	return ED.real();
}
