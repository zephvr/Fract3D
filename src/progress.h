#pragma once
#include <iostream>
#include <boost/thread.hpp>
#include <cmath>

class Progress
{
public:
	Progress();
	Progress(int num);
	void setNum(int const& num);
	void test(int n);
private:
	int m_percent=0;
	int m_num;
};
