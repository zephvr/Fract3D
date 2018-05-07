#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <cmath>

typedef std::chrono::duration<double> Durdur;

std::string make_time_readable(Durdur t);
