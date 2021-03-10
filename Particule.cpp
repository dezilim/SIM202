#include "Particule.hpp"
#include <cmath>

// Constructeur d'une particule en position, vitesse et force nulle
// avec un chronographe de longueur=taille
Particule::Particule(int dim) {
	position = Vecteur(dim);
	vitesse = 0.0 * position;
	force = 0.0 * position;
	chronographe.resize(0);
}

// Constructeur d'une particule à une position donnée
// de vitesse et force nulle, avec un chronographe de longueur=taille
Particule::Particule(Vecteur& position) {
	this->position = position;
	vitesse = 0.0 * position;
	force = 0.0 * position;
	chronographe.resize(0);
}

// Constructeur d'une particule de position et vitesse données
// de force nulle, avec un chronographe de longueur=taille
Particule::Particule(Vecteur& position, Vecteur& vitesse) {
	Compatible(position, vitesse, "Particule(position, vitesse)");
	this->position = position;
	this->vitesse = vitesse;
	force = 0.0 * position;
	chronographe.resize(0);
}


// -----------------------------------------------------------//
void Particule::Appliquer(double mg, const Vecteur& centre) {
	force += mg / (pow(norme2(centre-position)+1.0, 1.5)) * (centre-position);
}

void Particule::Deplacer(double dt) {
	chronographe.push_back(position);
	vitesse += dt * force;
	position += dt * vitesse;
	

	// check if the next position will exit the box
	for (int i = 0; i < (position.dim); i++)
	{
		if (((float) abs(position.val[i])) > 1.0)
		{
			position -= dt * vitesse;
			vitesse = (-1)*vitesse;
		} 
	}

	force *= 0.0;
	
}

ostream& operator<<(ostream& os, const Particule& P) {
	os << "Particule: " << P.position << ", " << P.vitesse << ", " << P.force << endl;
	for (auto& curseur : P.chronographe) cout << curseur << endl;
	return os;
}
