#include "Boite.hpp"
#include <iostream>	// pour pouvoir utiliser des objets ostreram
#include <fstream> 
#include <string>
using namespace std;

Boite::Boite(int dim, double rayon) {
	this->niveau = 0;
	this->coin = Vecteur(dim);
	this->rayon = rayon;
	
	masse = 0;
	centre = Vecteur(dim);
	
	particule = NULL;
	filles.resize(0);
}

Boite::Boite(Vecteur coin, int niveau, double rayon) {
	this->niveau = niveau;
	this->coin = coin;
	this->rayon = rayon;
	
	masse = 0;
	centre = 0.0 * coin;
	
	particule = NULL;
	filles.resize(0);
}

bool Boite::contient(const Particule& P) const {
	return (coin <= P.position && P.position <= coin+rayon);
}


// Créer les boîtes filles d'une boîte en pleine division, pour la diension 2
void Boite::construction_filles2D() {
	if (niveau > 3) exit(-1);
	double nv_rayon = rayon/2;
	int nv_niveau = niveau+1;
	// base
	Vecteur u(2,1); u *= nv_rayon;
	Vecteur v(2,2); v *= nv_rayon;
	// boîtes filles
	filles.push_back(Boite(coin+0+0, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+0+u, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+v+0, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+v+u, nv_niveau, nv_rayon));
}

// Créer les boîtes filles d'une boîte en pleine division, pour la diension 3
void Boite::construction_filles3D() {
	//if (niveau >50) exit(-1);
	double nv_rayon = rayon/2;
	int nv_niveau = niveau+1;
	// base
	Vecteur u(3,1); u *= nv_rayon;
	Vecteur v(3,2); v *= nv_rayon;
	Vecteur w(3,3); w *= nv_rayon;
	// boîtes filles
	filles.push_back(Boite(coin+0+0+0, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+0+0+u, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+0+v+0, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+0+v+u, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+w+0+0, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+w+0+u, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+w+v+0, nv_niveau, nv_rayon));
	filles.push_back(Boite(coin+w+v+u, nv_niveau, nv_rayon));
}

// Calcul le bilan des forces (approximé)
// que toutes les particules contenues dans la boîte appliques sur P
void Boite::bilan_force_unique_particule(Particule& P) const {
	if (this->contient(P)) {
		if (filles.size()!=0) {
			for (auto& curseur : filles) {
				curseur.bilan_force_unique_particule(P);
			}
		}
	} else {
		P.Appliquer(masse*1.0, centre);
	}
}

// Injecter une particule dans la boîte
// ! Suppose que P est contenue dedans ! Sinon ça n'a aucun sens...
// Divise la boîte au besoin
// Met à jour le centre de gravité et la masse de la boîte
void Boite::Injecter(Particule& P) {
	// le centre de gravité des centres de gravité est le centre de gravité :)
	centre = ((double) masse * centre + P.position) / (masse + 1.0);
	masse += 1;
	if (filles.size()==0) {
		if (particule==NULL) {
			particule = &P;
		} else {
			// division
			if (coin.dimension()==2) construction_filles2D();
			else construction_filles3D();
			centre *= 0.0;
			masse = 0;
			//--------------- Injection des particules
			Injecter(*particule);
			Injecter(P);
			particule = NULL;
		}
	} else {
		for (auto& curseur : filles) {
			if (curseur.contient(P)) return curseur.Injecter(P);
		}
	}
}

// Parcours toutes les particules de l'arbre.
// Applique à chacune le bilan des forces.
void Boite::Bilan_force_complet(Boite& racine) const {
	if (filles.size()==0) {
		if (particule!=NULL) {
			racine.bilan_force_unique_particule(*particule);
		}
	} else {
		for (auto& curseur : filles) {
			curseur.Bilan_force_complet(racine);
		}
	}
}

// Parcours toutes les particules de l'arbre.
// Déplace chacune en fonction de la force appliquée
void Boite::Deplacer_particules_interieur(double dt) const {
	if (filles.size()==0) {
		if (particule!=NULL) {
			particule->Deplacer(dt);
		}
	} else {
		for (auto& curseur : filles) {
			curseur.Deplacer_particules_interieur(dt);
		}
	}
}

// Mettre à jour notre système pendant timeout secondes.
void Boite::Update(double timeout, double timestep)
{
	for (int i = 0; i < timeout*timestep; i++)
	{
		Bilan_force_complet(*this);
		Deplacer_particules_interieur(1/(timestep));
	}
	cout << "Number of frames: " << (timeout*timestep) << endl;
}

// Write all data for all particles into one single file
void Boite::PrintParticles(ofstream& ofs)
{
	if (filles.size()==0) {
		if (particule!=NULL) {
			cout << *particule << "\n" <<endl;
			for (auto& curseur : (*particule).chronographe) 
			{	
				// cout << "Running curseur" << endl;
				// cout << curseur << endl;	
				// write in file
				ofs << curseur ;
			 	ofs << "\n";
			}	
		}
	} else {
		for (auto& curseur : filles) {
			curseur.PrintParticles(ofs);
		}
	}
}
ostream& operator<<(ostream& os, const Boite& B) {
	for(int i=0; i<B.niveau; i++) os << '\t';
	os<<"Boite: " << "niveau: " <<B.niveau<<", "<<"rayon: " <<B.rayon<<", "<<"coin: " <<B.coin<<", "<<"centre: " <<B.centre<<", "<<"mass: " << B.masse << endl;
	for (auto& curseur : B.filles) os << curseur;
	
	if (B.particule!=NULL) {
		os << "--------------------------------------------------\n";
		for(int i=0; i<B.niveau+1; i++) os << '\t';
		os << *(B.particule);
		os << "--------------------------------------------------\n";
	}
	return os;	
}
