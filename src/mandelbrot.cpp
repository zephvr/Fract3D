#include "mandelbrot.h"

using namespace boost::numeric::ublas;


Mandelbrot::Mandelbrot(Shade shade, int ordre)
	:m_ordre(ordre)
{
	m_shade = shade;
}

double Mandelbrot::DE(vector<double> ray)
{

}
