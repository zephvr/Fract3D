#include "engine.h"

using namespace boost::numeric::ublas;

Engine::Engine(Camera* cam)
//constructeur
{
	//initialise des variables
	m_camera = cam;
	int x_res = m_camera->getResolution()[0];
	int y_res = m_camera->getResolution()[1];
	m_p.setNum(x_res*y_res);
	m_render.resize(x_res);
	for (int i = 0; i < x_res; i++)
	{
		m_render[i].resize(y_res);
		for (int j = 0; j < y_res; j++)
		{

			m_render[i][j] = new Pixel;
		}
	}
}

Engine::~Engine()
{
	int x_res = m_render.size(), y_res = m_render[0].size();

	for (int i = 0; i < x_res; i++)
	{
		m_render[i].resize(y_res);
		for (int j = 0; j < y_res; j++)
		{
			 //free m_render[i][j];
		}
	}
}

void Engine::addElement(Solid* element)
{
	m_element.push_back(element);
}

void Engine::addSource(Light* source)
{
	m_source.push_back(source);
}

void Engine::get_xy(int &x, int &y)
{
	mtx_xy.lock(); //on lock pour etre sur d'etre le seul thread a modifier m_x et m_y
	int *res = m_camera->getResolution();
	x = m_x;
	y = m_y;
	y++;
	m_y++;
	if (y == res[1]) //si on est au bout de la ligne on saute une ligne
	{
		m_y = 0;
		y = 0;
		m_x++;
		x++;
	}
	m_p.test(1 + m_y + res[1]*m_x);
	mtx_xy.unlock();
}

std::vector<std::vector<Pixel*>> Engine::getRender()
{
	return m_render;
}

std::vector<Light*> Engine::getSource()
{
	return m_source;
}

Pixel Engine::DE(vector<double> ray) 
/* renvoie un pixel contenant: 
distance -> la distance avec le plus proche solide
solid -> la reference de ce solide
*/
{
	Pixel data; //pixel contenant des informations
	double dist = m_element[0]->DE(ray); //distance minimal a un objet de la scene
	data.distance = dist; //distance entre la position du rayon et le premier solide
	data.solid = m_element[0]; // type de solide
	for (unsigned i = 1; i < m_element.size(); ++i)
	{
		dist = m_element[i]->DE(ray); // distance entre la pos du ray et le solide i
		if (dist < data.distance) 
			//si la distance a cet objet est inferieur
		{
			data.distance = dist;
			data.solid = m_element[i];
		}
	}
	return data;
}

Pixel Engine::track(vector<double> const& origin, vector<double> const& way)
{
	Pixel data;
	double totalDistance(0), min_range(0);
	vector<double> current_position(origin);
	//current_position.resize(3);
	//current_position = origin;
	for (unsigned iter = 1; iter < m_maxIteration; ++iter)
	{
		current_position = origin + totalDistance * way;
		data = this->DE(current_position);
		totalDistance += data.distance;
		if (data.distance < m_minDistance)
		{
			data.pos = current_position;
			data.collision = true;
			data.numIter = iter;
			break;
		}
		if (totalDistance > m_viewport)
		{
			data.numIter = iter;
			break;
		}
	}
	return data;
}

vector<double> Engine::normal(vector<double> const& pos, Solid* obj)
{
	vector<double> x_axe(3), y_axe(3), z_axe(3), norm(3);
	x_axe(0) = m_minDistance / NORME_PREC; x_axe(1) = 0; x_axe(2) = 0;
	y_axe(0) = 0; y_axe(1) = m_minDistance / NORME_PREC; y_axe(2) = 0;
	z_axe(0) = 0; z_axe(1) = 0; z_axe(2) = m_minDistance / NORME_PREC;
	norm(0) = obj->DE(pos + x_axe) - obj->DE(pos - x_axe);
	norm(1) = obj->DE(pos + y_axe) - obj->DE(pos - y_axe);
	norm(2) = obj->DE(pos + z_axe) - obj->DE(pos - z_axe);
	return norm/norm_2(norm);
}

void Engine::compute_render()
{
	int x(0), y(0);
	get_xy(x, y);
	while (x < m_camera->getResolution()[0])
	{
		Pixel *pix = m_render[x][y];
		vector<double> origin, way;
		origin = m_camera->getPosition();
		way = m_camera->getVector(x, y);
		(*pix) = track(origin, way);
		if (pix->collision == true)
		{
			pix->normal = normal(pix->pos, pix->solid);
		}
		get_xy(x, y);
	}
	
}

void Engine::compute()
{
	auto t1 = std::chrono::steady_clock::now();
	boost::thread_group tgroup;
	m_x = 0; m_y = -1;
	for (unsigned i = 0; i < CORE_USE; i++)
	{
		tgroup.create_thread(boost::bind(&Engine::compute_render, this));
	}
	tgroup.join_all();
	auto t2 = std::chrono::steady_clock::now();
	auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "\nIt took " << make_time_readable(time_span) << "to compute render\n";
}

void afficher(boost::numeric::ublas::vector<double> v)
{
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << v(i) << " ";
	}
}
