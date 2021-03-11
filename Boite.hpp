#ifndef Boite_hpp
#define Boite_hpp

#include "Particule.hpp"
#include "Vecteur.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Boite { // la classe des boîtes
	private:
		bool contient(const Particule& P) const;
		void construction_filles2D();
		void construction_filles3D();
		void bilan_force_unique_particule(Particule& P) const;
	public:
		// géométrie
		int niveau;
		Vecteur coin;
		double rayon;
		
		// physique
		int masse;
		Vecteur centre;
		
		// arborecence
		Particule* particule;
		vector<Boite> filles; // berk !
		
		Boite(int dim=2, double rayon=1.0);
		Boite(Vecteur coin, int niveau, double rayon);
		
		void Injecter(Particule& P);
		void Bilan_force_complet(Boite& racine) const;
		void Deplacer_particules_interieur(double dt) const;
		void MajPos(std::vector<int> & aux);
		void MajMass();
		void Update(double timeout, double timestep);
		void PrintParticles(ofstream& ofs);
};

ostream& operator<<(ostream& os, const Boite& B);

#endif

/*
void construction_filles  ();

// Créer les boîtes filles d'une boîte en pleine division, pour une dimension quelconque
void Boite::construction_filles() {
	int dim = coin.dimension();
	if (niveau > 3) exit(-1);
	filles = new Boite[pow(];
	double nv_rayon = rayon/2;
	int nv_niveau = niveau+1;
	// base
	Vecteur* base = new Vecteur[dim];
	for (int i=0; i<dim; i++) base[i] = nv_rayon*Vecteur(dim, i-1);
	int* code = new int[dim];
	for (int i=0; i<dim; i++) code[i] = 0;
	// boîtes filles
	int c = 0;
	while (c<dim) {
		c = 0;
		Vecteur nv_coin(coin);
		for (int i=0; i<dim; i++) nv_coin += code[i]*base[i];
		filles.push_back(Boite(nv_coin, nv_rayon, nv_niveau));
		for(int i=0; i<dim; i++) cout << code[i];
		cout << endl;
		code[c]++;
		while (code[c]>1 && c<dim) {
			code[c]=0;
			c++;
			code[c]++;
		}
	}
	delete[] base;
	delete[] code;
}

*/
