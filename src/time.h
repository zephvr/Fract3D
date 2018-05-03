#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <cmath>

class Time
{
public:
	Time();
	void afficher(std::ostream &flux) const;

private:
	clock_t m_t;
};

std::string make_time_readable(clock_t t);
