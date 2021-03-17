#include <ctime>
#include "Vecteur.hpp"
#include "Particule.hpp"
#include "Boite.hpp"
#include <math.h>

#include <iostream>	// pour pouvoir utiliser des objets ostreram
#include <fstream> 
#include <string>
#define PI 3.14159265
using namespace std;

int main( int argc, char * argv[] ) {
	//initialisation du générateur aleatoire
	srand (time(0));
	string earth_fileName =  "earthdata.txt";
	string sun_fileName =  "sundata.txt";
	string mercury_fileName =  "mercurydata.txt";
	string ourWorld_fileName = "ourWorld.txt";
	ofstream earth_txtOut, sun_txtOut, mercury_txtOut, ourWorld_txtOut;
	earth_txtOut.open(earth_fileName);
	sun_txtOut.open(sun_fileName);
	mercury_txtOut.open(mercury_fileName);
	ourWorld_txtOut.open(ourWorld_fileName);

	//test de la classe vecteur
	Vecteur O(3);
	Vecteur P(3, 1), Q(3, 0.1), R(3, 0.3);
	Vecteur S(3,0.2);
	Vecteur T = (-0.1)*P;
	Vecteur U(3, 2);
	Vecteur E = 0.2*U;
	// cout << "Test de la classe Vecteur--------------------------------------" << endl;
	// cout << "P et Q compatibles ?: "; Compatible(P, Q, "main"); cout << "oui" << endl;
	// cout << "O=" << O << endl;
	// cout << "P=" << P << endl;
	// cout << "Q=" << Q << endl;
	// cout << "R=" << R << endl;
	// cout << "S=" << S << endl;
	// cout << "O+P+2.*Q-R/2.=" << (O+P+2.*Q-R/2.) << endl;
	// cout << norme2(S) << endl;
	
	// test de la classe Particule
	Particule Soleil(S,R), Mercure(T, Q), Venus(Q, P), Terre(E, P), Mars(O,P);
	// cout << "Test de la classe Palorenz-phaserticule-------------------------------------" << endl;
	// cout << "-----------------Position Velocity Force " << endl;
	// cout << "Soleil: " << Soleil << endl;
	// cout << "Mercure : " << Mercure << endl;
	// cout << "Venus : " << Venus << endl;
	// cout << "Terre : " << Terre << endl;
	// cout << "Mars : " << Mars << endl;


	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% AUTO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	Vecteur X(3,1), Y(3,2), Z(3,3);	
	vector<Particule> particle_list;
	



	//GENERATE PARTICLES AND UPDATE --------------------------------------------------------------------
	clock_t begin = clock();


	int nb_particles = 5;
	Boite ourWorld(3, 20.0);
	ourWorld.coin.val[0] = -10.0; ourWorld.coin.val[1] = -10.0;ourWorld.coin.val[2] = -10.0;
	vector<Particule> myParticles;

	cout << "Number of particles generated : " << nb_particles << endl; 
	// create particles and put them in a list (dont inject in this loop, there will be an error)
	for(int i = 0; i<nb_particles; i++)
	{	
		cout << "Generating particle " << (i+1) << "..." <<endl;
		
		// pick a random number from 0 to 1
		double x1 = ((float) rand()) / (float) RAND_MAX;
		double x2 = ((float) rand()) / (float) RAND_MAX;
		double x3 = ((float) rand()) / (float) RAND_MAX;
		double r = 1.0/pow((pow((1/x1),2.0/3)-1), 0.5);
		if (r >= 10.0) r = 9.9;

		double pos_z = (1-2*x2)*r; 
		double pos_x = pow((pow(r,2) - pow(pos_z,2)),0.5)* cos(2*PI*x3);
		double pos_y = pow((pow(r,2) - pow(pos_z,2)),0.5)*sin(2*PI*x3);

		cout << "x1: " << x1 << endl; cout << "x2: " << x2 << endl; cout << "x3: " << x3 << endl;
		cout << "pos x : " << pos_x << endl; cout << "pos y : " << pos_y<< endl; cout << "pos z : " << pos_z<< endl; 
		cout << "r : " << r << endl;


		// calculation of velocity
		double x4 = ((float) rand()) / (float) RAND_MAX;
		double x5 = ((float) rand()) / (float) RAND_MAX;
		int count = 0;
		while (x5 > 10 * pow((x4),2)/pow((1-pow((x4),2)), 0.25))
		{	
			count++;
			double x4 = ((float) rand()) / (float) RAND_MAX;
			double x5 = ((float) rand()) / (float) RAND_MAX;
			if (count > 10) break;
		}
		double q = x4;
		double V = q*sqrt(2)/pow(1+ pow(r,2),0.25);

		double x6 = ((float) rand()) / (float) RAND_MAX;
		double x7 = ((float) rand()) / (float) RAND_MAX;

		double w = (1-2*x6)*V; 
		double u = pow((pow(V,2)-pow(w,2)),0.5)*cos(2*PI*x7);
		double v = pow((pow(V,2)-pow(w,2)),0.5)*sin(2*PI*x7);



		Vecteur Pos = pos_x*X + pos_y*Y + pos_z*Z;
		Vecteur Vel = u*X + v*Y + w*Z; 

		cout << "Position : " << Pos << endl;
		cout << "Velocity : " << Vel << endl;

		Particule Part(Pos,Vel);
		myParticles.push_back(Part);

	}
	vector<Particule>::iterator itp = myParticles.begin();
	for (; itp != myParticles.end(); itp++)
	{
		cout << "Injected Particle "  << "..." <<endl;
		ourWorld.Injecter(*itp);
		cout << ourWorld << endl;
	}
	cout << "%%%%%%%%%%%%%%% Particles added %%%%%%%%%%%%%% " << endl;
	cout << ourWorld << endl;
	cout << " %%%%%%%%%%%%%%%%%% UPDATING %%%%%%%%%%%%%%%%%% " <<endl;


	// run ourWorld for 1000 frames
	int nbframes = 1000;
	for (int i = 0; i < nbframes; i++)
	{

		ourWorld = returnUpdate(ourWorld);
		cout<< " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n" << ourWorld << endl;
		/*cout<< "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n" << endl;
		B = myNewBox;*/
	}




	clock_t end = clock();
  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time Passed: " << elapsed_secs << endl;
	cout << " %%%%%%%%%%%%%%%%s%% UPDATED %%%%%%%%%%%%%%%%%% " <<endl;
	//cout << ourWorld << endl;

	// cout << "----------Testing PrintParticles: -----------" << endl;
	// cout << "------------------------------------" << endl;

	ourWorld.PrintParticles(ourWorld_txtOut); 



	/*           USED FOR TESTING SOLEIL MERUCURY AND TERRE IN B 
	
	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Testing box %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	Boite B(3, 2.0);
	B.coin.val[0] = -1.0; B.coin.val[1] = -1.0;B.coin.val[2] = -1.0;
	cout << B << endl;
	B.Injecter(Soleil);
	B.Injecter(Terre);
	B.Injecter(Mercure);
	cout << "Injected Soleil and Terre end Mercury..." << endl;
	cout << B << endl;


	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Testing box %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;

	// // this works 
	int nbframes = 100;
	for (int i = 0; i < nbframes; i++)
	{

		B = returnUpdate(B);
		cout<< " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n" << B << endl;
		/*cout<< "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n" << endl;
		B = myNewBox;
	}

	cout << "Number of frames: " << (nbframes) << endl;
	

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
	
	*/




	ourWorld_txtOut.close();
	earth_txtOut.close(); 
	sun_txtOut.close();
	mercury_txtOut.close();


	return 0;
}
