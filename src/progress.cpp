#include "progress.h"

using namespace std;

Progress::Progress()
	:m_num(0)
{
	m_percent = 0;
}

Progress::Progress(int num)
	:m_num(num)
{}

void Progress::setNum(int const& num)
{
	m_num = num;
}


void Progress::test(int n)
{
	int a = (double)n / m_num * 100;

	if (a > m_percent)
	{
		string erase = "\b\b";
		float m = log10(m_percent);
		for (int i = 0; i <= m; i++)
			erase += "\b";
		if (m_percent == 0)
			cout << a << " %";
		else
			cout << erase << a << " %";
		m_percent = a;
	}
}
