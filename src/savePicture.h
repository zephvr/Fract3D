#pragma once

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include "camera.h"
#include "pixel.h"
#include "light.h"
#include "color.h"
#include "defines.h"
#include "time.h"
#include "progress.h"


class SavePicture
	// class permettant la sauvegarde dans une image de la boite de collision generer avec le moteur
{
public:
	SavePicture(std::vector<std::vector<Pixel*>> render, std::vector<Light*> source, Camera* camera);
	void get_xy(int &x, int &y);
	Color get_color(int const& x, int const& y);
	void thread_save();
	void compute();
private:
	boost::mutex mtx_xy; //
	std::vector<std::vector<Pixel*>> m_render;
	std::vector<Light*> m_source; // liste des sources lumineuse
	int m_x, m_y; // 
	Camera* m_camera; // pointeur vers la camera de la scene
	Progress m_p;
};

bool exists_test(const std::string& name);
