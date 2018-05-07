#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include "shade.h"

class Solid
{
public:
	Solid();
	Solid(Shade shade);
	virtual double DE(boost::numeric::ublas::vector<double> ray);
	virtual void setshade(Shade const& shade);
	virtual Shade getshade() const;
	virtual void debug();

protected:
	Shade m_shade;
};