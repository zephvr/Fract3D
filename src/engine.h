#pragma once

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include <vector>
#include "solid.h"
#include "light.h"
#include "camera.h"
#include "pixel.h"
#include "defines.h"
#include "time.h"
#include "progress.h"


class Engine
	// permet de calculer une boite de collision pour chaque pixel de l'ecran
{
public:
	//Constructeur(s)
	Engine(Camera* m_cam);

	//Destructeur
	~Engine();

	void addElement(Solid* element);
	//Ajoute un solide a la scene

	void addSource(Light* source);
	//Ajoute une source lumineuse a la scene

	std::vector<std::vector<Pixel*>> getRender();
	//Renvoie m_render (matrice contenant le resultat du rendu)

	std::vector<Light*> getSource();
	//Renvoie m_source (liste des sources lumineuse)
		
	void compute();
	//Calcule les donnees de chaques pixels

private:
	/*** methodes ***/
	Pixel track(boost::numeric::ublas::vector<double> const& origin, boost::numeric::ublas::vector<double> const& way);
	//calcul le trajet du rayon jusqu'a un objet
	//@renvoie un pixel contenant les informations de l'impact

	boost::numeric::ublas::vector<double> normal(boost::numeric::ublas::vector<double> const& pos, Solid* object);
	//calcul la normal du solide "object" a la position "pos"
	//@renvoie un vecteur

	void compute_render();
	//thread utiliser par la fonction compute il permet de calculer un par un les pixels de m_render

	Pixel DE(boost::numeric::ublas::vector<double> ray);
	//calcul le minimum des DE des elements de la scene
	//@renvoie un pixel detenant les informations necessaire (la distance, l'objet le plus proche)

	void get_xy(int &x, int &y);
	//methode utilisee par "compute_render" pour obtenir un couple x,y de pixel non deja traite
	//ne renvoie rien mais modifie la valeur des entree (c'est mauvais mais bon ): )

	/*** variables ***/
	boost::mutex mtx_xy; // lock pour le multi-tread
	std::vector<Solid*> m_element;	// liste des elements a considere
	std::vector<Light*> m_source;	// liste des sources lumineuse
	std::vector<std::vector<Pixel*>> m_render; 	// matrice de donner pour chaque pixel de l'image
	Camera* m_camera; 	// pointeur vers la camera de la scene
	double m_viewport = VIEWPORT, m_minDistance = MIN_DISTANCE; 
	// portée de vue de la scene (distance a laquel on considere etre trop loin de la scene) 
	// distance minimal pour considerer avoir toucher l'objet
	unsigned m_maxIteration = MAX_ITERATION;	// nombre maximum d'iteration
	int m_x, m_y; 	// utiliser pour le multi-thead pour connaitre la position actuel du plus recent thread
	Progress m_p;
};

void afficher(boost::numeric::ublas::vector<double> v);
