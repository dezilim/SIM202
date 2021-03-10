//#include <ctime>
#include "Vecteur.hpp"
#include "Particule.hpp"
#include "Boite.hpp"

#include <iostream>	// pour pouvoir utiliser des objets ostreram
#include <fstream> 
#include <string>
using namespace std;

int main( int argc, char * argv[] ) {
	//initialisation du générateur aleatoire
	//srand (time(0));
	string earth_fileName =  "earthdata.txt";
	string sun_fileName =  "sundata.txt";
	string mercury_fileName =  "mercurydata.txt";
	ofstream earth_txtOut, sun_txtOut, mercury_txtOut;
	earth_txtOut.open(earth_fileName);
	sun_txtOut.open(sun_fileName);
	mercury_txtOut.open(mercury_fileName);

	//test de la classe vecteur
	Vecteur O(3);
	Vecteur P(3, 1), Q(3, 0.2), R(3, 0.3);
	Vecteur S(3,0.5);
	Vecteur T = 0.5*P;
	cout << "Test de la classe Vecteur--------------------------------------" << endl;
	cout << "P et Q compatibles ?: "; Compatible(P, Q, "main"); cout << "oui" << endl;
	cout << "O=" << O << endl;
	cout << "P=" << P << endl;
	cout << "Q=" << Q << endl;
	cout << "R=" << R << endl;
	cout << "S=" << S << endl;
	cout << "O+P+2.*Q-R/2.=" << (O+P+2.*Q-R/2.) << endl;
	cout << norme2(S) << endl;
	
	// test de la classe Particule
	Particule Soleil(S,R), Mercure(T, Q), Venus(Q, P), Terre(R, P), Mars(O,P);
	cout << "Test de la classe Palorenz-phaserticule-------------------------------------" << endl;
	cout << "-----------------Position Velocity Force " << endl;
	cout << "Soleil: " << Soleil << endl;
	cout << "Mercure : " << Mercure << endl;
	cout << "Venus : " << Venus << endl;
	cout << "Terre : " << Terre << endl;
	cout << "Mars : " << Mars << endl;

	// cout << "Displaced Particles--------------------------------------" << endl;
	// for(int i=0; i<10; i++)
	// {
	// 	Terre.Deplacer(1);
	// 	Soleil.Deplacer(1);
	// } 
	
	// cout << "New positions velocity and foce--------------------------" << endl;
	// cout << "Soleil: " << Soleil << endl;
	// cout << "Mercure : " << Mercure << endl;
	// cout << "Venus : " << Venus << endl;
	// cout << "Terre : " << Terre << endl;
	// cout << "Mars : " << Mars << endl;


	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Testing box %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	Boite B(3, 1.0);
	cout << B << endl;
	B.Injecter(Soleil);
	B.Injecter(Terre);
	B.Injecter(Mercure);
	cout << "Injected Soleil and Terre..." << endl;
	cout << B << endl;

	cout << "------------------------------------------------Displaced Particles--------------------------------------" << endl;
	// for(int i=0; i<10; i++)
	// {
	// 	B.Bilan_force_complet(B);
	// 	B.Deplacer_particules_interieur(1.0);
	// } 

	// Update with timeout (total time) = 20s, timestep (number of steps in 1 s)  = 5
	B.Update(20, 5);

	cout << "\nChronograph of terre -------------" << endl;
	for (auto& curseur : Terre.chronographe) 
	{
		cout << curseur << endl;	
		earth_txtOut << curseur ;
		earth_txtOut << "\n";
	}	
	
	cout << "\nChronograph of sun -------------" << endl;
	for (auto& curseur : Soleil.chronographe) 
	{
		cout << curseur << endl;	
		sun_txtOut << curseur ;
		sun_txtOut << "\n";
	}

		cout << "\nChronograph of mercury -------------" << endl;
	for (auto& curseur : Mercure.chronographe) 
	{
		cout << curseur << endl;	
		mercury_txtOut << curseur ;
		mercury_txtOut << "\n";
	}





	earth_txtOut.close(); 
	sun_txtOut.close();
	mercury_txtOut.close();

	// test de la classe Boite
	// Boite B(3, 1.0);
	// cout << B << endl;
	// B.Injecter(Soleil);
	// B.Injecter(Mercure);
	// B.Injecter(Venus);
	// B.Injecter(Terre);
	// B.Injecter(Mars);
	// cout << B << endl;
	
	// B.Bilan_force_complet(B);
	// cout << B << endl;
	// B.Deplacer_particules_interieur(1.0);
	// cout << B << endl;
	// Reconstruire*/
	return 0;
}
