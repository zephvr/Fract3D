#pragma once

#include <boost/thread.hpp>

//couleur du fond
#define SKY_R 126
#define SKY_G 192
#define SKY_B 238

//config engine
#define VIEWPORT 100 //porte de vue
#define MIN_DISTANCE 1e-3
#define NORME_PREC 100
#define MAX_ITERATION 200


#define SAVE_FILE "3D fract"

#define CORE_USE boost::thread::hardware_concurrency()

