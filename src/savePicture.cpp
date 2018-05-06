#include "savePicture.h"

SavePicture::SavePicture(std::vector<std::vector<Pixel*>> render, std::vector<Light*> source, Camera* camera)
	:m_render(render), m_source(source), m_camera(camera)
{
	m_x = 0;
	m_y = 0;
}

void SavePicture::get_xy(int &x, int &y)
{
	mtx_xy.lock();
	int *res = m_camera->getResolution();
	x = m_x;
	y = m_y;
	y++;
	m_y++;
	if (y == res[1])
	{
		m_y = 0;
		y = 0;
		m_x++;
		x++;
	}
	mtx_xy.unlock();
}

Color SavePicture::get_color(int const& x, int const& y)
{
	//https://fr.wikipedia.org/wiki/Ombrage_de_Phong
	using namespace boost::numeric::ublas;
	Pixel pix = *(m_render[x][y]);
	Solid *sol = m_render[x][y]->solid;
	Color I_ambiante(0, 0, 0), I_diffuse(0, 0, 0), I_spectral(0, 0, 0);
	for (unsigned int i = 0; i < m_source.size(); i++)
	{
		I_ambiante += sol->getshade().getambiante() * m_source[i]->getShade().getambiante();
		vector<double> L(3), N(3);
		N = pix.normal;
		L = m_source[i]->getDir(pix.pos);
		
		double angle = std::max(0.0, inner_prod(L, N));
		I_diffuse += sol->getshade().getdiffuse() * m_source[i]->getShade().getdiffuse() * angle;
		vector<double> R(3), V(3);
		R = m_camera->getPosition() - pix.pos; //vecteur pointant vers la camera a partir du solide
		R /= norm_2(R);
		matrix<double> reflechit = rotationalMatrix(N, 3.14);
		V = prod(reflechit, L);  //vecteur diriger vers la camera
		angle = inner_prod(R, V);
		if (angle > 0)
			I_spectral += sol->getshade().getspecular() * m_source[i]->getShade().getspecular() * pow(angle, sol->getshade().getbrillance());
	}
	return I_ambiante + I_diffuse + I_spectral;

}

void SavePicture::thread_save()
{
	int x(0), y(0);
	get_xy(x, y);
	while (x < m_camera->getResolution()[0])
	{
		if (m_render[x][y]->collision)
		{
			Color c = get_color(x, y);
			//std::cout << "R " << c.getR() << " G " << c.getG() << " B " << c.getB() << "\n";
			m_render[x][y]->color.b = (char) (c.getB()*255 + 0.5);     //B
			m_render[x][y]->color.g = (char) (c.getG()*255 + 0.5); //G
			m_render[x][y]->color.r = (char) (c.getR()*255 + 0.5); //R
		}
		else
		{ //sky color
			m_render[x][y]->color.b = SKY_B;     //B
			m_render[x][y]->color.g = SKY_G; //G
			m_render[x][y]->color.r = SKY_R; //R
		}
		get_xy(x, y);
	}
}

void SavePicture::compute()
{
	auto t1 = std::chrono::steady_clock::now();
	boost::thread_group tgroup;
	int *res = m_camera->getResolution();
	m_x = 0; m_y = -1;
	for (unsigned i = 0; i < boost::thread::hardware_concurrency(); i++)
	{
		tgroup.create_thread(boost::bind(&SavePicture::thread_save, this));
	}
	tgroup.join_all();
	int i = 0;
	while (exists_test("3D fract " + std::to_string(i) + ".ppm"))
	{
		i++;
	}
	std::string path = "3D fract " + std::to_string(i) + ".ppm";
	std::wstring pathw = std::wstring(path.begin(), path.end());
	std::ofstream img((char*)pathw.c_str(), std::ios::binary);
	std::string s_width = std::to_string(res[0]);
	std::string s_heigth = std::to_string(res[1]);

	img.write("P6 ", 3);
	img.write(s_width.c_str(), s_width.length());
	img.write(" ", 1);
	img.write(s_heigth.c_str(), s_heigth.length());
	img.write(" ", 1);
	img.write("255 ", 4);

	for (int y = 0; y < res[1]; y++)
	{
		for (int x = 0; x < res[0]; x++)
		{
			img.write(reinterpret_cast<char*>(&m_render[x][y]->color), sizeof(RGB));
		}
	}
	auto t2 = std::chrono::steady_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "\nIt took " << make_time_readable(time_span) << "to save the pic\n";
}

bool exists_test(const std::string& name) 
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
