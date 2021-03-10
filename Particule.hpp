#ifndef Particule_hpp
#define Particule_hpp

#include "Vecteur.hpp"
#include <iostream>
#include <vector>
using namespace std;

/*
Chronographe holds the positions
*/


class Particule {
	public:
		Vecteur vitesse;
		Vecteur force; // force massique
		vector<Vecteur> chronographe; // berk !
	// public:
		Vecteur position;
		
		Particule(int dim=2);
		Particule(Vecteur& position);
		Particule(Vecteur& position, Vecteur& vitesse);
		
		void Appliquer(double mg, const Vecteur& centre);
		void Deplacer(double dt);
		
		friend ostream& operator<<(ostream& os, const Particule& P);
};

#endif
