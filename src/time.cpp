#include "time.h"

using namespace std;

Time::Time()
{
	m_t = clock();
}

void Time::afficher(std::ostream &flux) const
{
	//flux << 
}

string make_time_readable(clock_t clock)
{
	float t = (float)clock / CLOCKS_PER_SEC;
	string s("");
	int temp;
	for (int i = 0; i < 2; i++)
	{
		if (1e-3 > t)
			return s;
		else if (1.0 > t && t >= 1e-3)
		{
			temp = trunc(t * 1e3);
			s += to_string(temp) + " ms ";
			t -= temp;
			return s;
		}
		else if (60.0 > t && t >= 1.0)
		{
			temp = trunc(t);
			s += to_string(temp) + " s ";
			t -= temp;
		} 
		else if (3600.0 > t && t >= 60.0)
		{
			temp = trunc(t / 60);
			s += to_string(temp) + " min ";
			t -= temp * 60;
		}
		else if (86400.0 > t && t >= 3600.0)
		{
			temp = trunc(t / 3600);
			s += to_string(temp) + " h ";
			t -= temp * 3600;
		}
		else
		{
			temp = trunc(t / 86400);
			s += to_string(temp) + " j ";
			t -= temp * 86400;
		}
	}
	return s;
}
