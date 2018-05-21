// Rendue 3D.cpp : définit le point d'entrée pour l'application console.
//

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "engine.h"
#include "ball.h"
#include "multiBall.h"
#include "ground.h"
#include "sun.h"
#include "light_ball.h"
#include "mandelbulb.h"
#include "newton.h"
#include "savePicture.h"

using namespace boost::numeric::ublas;

int main(int argc, const char** argv)
{
	vector<double> pos_ball(3);
	pos_ball(0) = -2; // X
	pos_ball(1) = 0; // Y
	pos_ball(2) = 0; // Z
	vector<double> way_sun(3);
	way_sun(0) = -1; // X
	way_sun(1) = 0; // Y
	way_sun(2) = -4; // Z
	way_sun /= norm_2(way_sun);
	vector<double> pos_cam(3);
	pos_cam(0) = -1; // X
	pos_cam(1) = 0; // Y
	pos_cam(2) = 4; // Z
	Shade red_shade(RED*(1.0 / 10.0), RED, WHITE, 200.0), white_shade(WHITE*0.1, WHITE, WHITE, 200.0), gold_shade(GOLD*0.1, GOLD, GOLD, 200.0);
	Camera cam(0*3.14/180, 70*3.14/180, 0*3.14/180, 16.0/9.0, 3, pos_cam);
	cam.setResolution(1920/2, 1080/2);
	Engine fract(&cam);
	Ground grd(0);
	Ball ball(pos_ball, 0.5, red_shade);
	Sun soleil(way_sun, 100);
	MultiBall mltBall(1, 0.5, red_shade);
	LightBall lampe(pos_ball, 100);
	Mandelbulb mandel(gold_shade, 40, 20);
	Newton newton(gold_shade, 1e-4, 3);
	//fract.addElement(&grd);
	//fract.addElement(&mltBall);
	fract.addElement(&newton);
	fract.addSource(&soleil);

	//fract.DE(pos_cam);
	
	fract.compute();
	SavePicture save(fract.getRender(), fract.getSource(), &cam);
	save.compute();
	return 0;
}

