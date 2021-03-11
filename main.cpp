#include <ctime>
#include "Vecteur.hpp"
#include "Particule.hpp"
#include "Boite.hpp"

#include <iostream>	// pour pouvoir utiliser des objets ostreram
#include <fstream> 
#include <string>
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
	Vecteur T = 0.1*P;
	Vecteur U(3, 2);
	Vecteur E = 0.2*U;
	cout << "Test de la classe Vecteur--------------------------------------" << endl;
	cout << "P et Q compatibles ?: "; Compatible(P, Q, "main"); cout << "oui" << endl;
	cout << "O=" << O << endl;
	cout << "P=" << P << endl;
	cout << "Q=" << Q << endl;
	cout << "R=" << R << endl;
	cout << "S=" << S << endl;
	cout << "O+P+2.*Q-R/2.=" << (O+P+2.*Q-R/2.) << endl;
	cout << norme2(S) << endl;
	
	// // test de la classe Particule
	Particule Soleil(S,R), Mercure(T, Q), Venus(Q, P), Terre(E, P), Mars(O,P);
	// cout << "Test de la classe Palorenz-phaserticule-------------------------------------" << endl;
	// cout << "-----------------Position Velocity Force " << endl;
	// cout << "Soleil: " << Soleil << endl;
	// cout << "Mercure : " << Mercure << endl;
	// cout << "Venus : " << Venus << endl;
	// cout << "Terre : " << Terre << endl;
	// cout << "Mars : " << Mars << endl;

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

	// cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% AUTO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	Vecteur X(3,1), Y(3,2), Z(3,3);	
	vector<Particule> particle_list;
	
	Boite ourWorld(3, 1.0);
	// ourWorld.Injecter(Soleil);
	// ourWorld.Injecter(Terre);
	// ourWorld.Injecter(Mercure);
	// cout << ourWorld << endl;
	// for(int i = 0; i<3; i++)
	// {
	// 	if (i == 0)
	// 	{
	// 		ourWorld.Injecter(Soleil);
	// 	}
	// 	if (i == 1)
	// 	{
	// 		ourWorld.Injecter(Terre);
	// 	}
	// 	if (i == 2)
	// 	{
	// 		ourWorld.Injecter(Mercure);
	// 	}
	// }
	// cout << ourWorld << endl;
	// cout << " %%%%%%%%%%%%%%%%%% UPDATING %%%%%%%%%%%%%%%%%% " <<endl;
	// ourWorld.Update(20, 20);


	//int nb_particles = rand() % 10 + 1;
	// vector<Vecteur> myPositions = {S, T, E};
	// vector<Vecteur> myVelocities = {R, Q, P};



	// GENERATE PARTICLES AND UPDATE --------------------------------------------------------------------
	clock_t begin = clock();


	int nb_particles = 50;

	vector<Particule> myParticles;
	cout << "Number of particles generated : " << nb_particles << endl; 
	// create particles and put them in a list (dont inject in this loop, there will be an error)
	for(int i = 0; i<nb_particles; i++)
	{	
		cout << "Generating particle " << (i+1) << "..." <<endl;
		
		double pos_x =  (double)(((float)((int)((((float) rand()) / (float) RAND_MAX) * 10)))/10);
		double pos_y =  (double)(((float)((int)((((float) rand()) / (float) RAND_MAX) * 10)))/10);
		double pos_z =  (double)(((float)((int)((((float) rand()) / (float) RAND_MAX) * 10)))/10);
		double vel_x =  (double)(((float)((int)((((float) rand()) / (float) RAND_MAX) * 10)))/10);
		double vel_y =  (double)(((float)((int)((((float) rand()) / (float) RAND_MAX) * 10)))/10);
		double vel_z =  (double)(((float)((int)((((float) rand()) / (float) RAND_MAX) * 10)))/10);
		Vecteur Pos = pos_x*X + pos_y*Y + pos_z*Z; Vecteur Vel = vel_x*X + vel_y*Y + vel_z*Z;
		cout << "Position : " << Pos << endl;
		cout << "Velocity : " << Vel << endl;

		//Particule Part(myPositions[i],myVelocities[i]);
		Particule Part(Pos,Vel);
		myParticles.push_back(Part);

	}
	vector<Particule>::iterator itp = myParticles.begin();
	for (; itp != myParticles.end(); itp++)
	{
		cout << "Injected Particle "  << "..." <<endl;
		ourWorld.Injecter(*itp);
	}
	cout << "%%%%%%%%%%%%%%% Particles added %%%%%%%%%%%%%% " << endl;
	cout << ourWorld << endl;
	cout << " %%%%%%%%%%%%%%%%%% UPDATING %%%%%%%%%%%%%%%%%% " <<endl;
	ourWorld.Update(10, 20);

	clock_t end = clock();
  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time Passed: " << elapsed_secs << endl;
	// cout << " %%%%%%%%%%%%%%%%%% UPDATED %%%%%%%%%%%%%%%%%% " <<endl;
	// cout << ourWorld << endl;
	
	// prints out the entire chronographe
	// cout << "Final sun: "<< Soleil << endl;
	cout << "Testing PrintParticles: -----------" << endl;
	cout << "------------------------------------" << endl;

	//ourWorld.PrintParticles(ourWorld_txtOut); 



	// doesnt work even with soleil terre and mercury : i think they are just copies 
	// vector<Particule>::iterator it = particle_list.begin();
	// int i = 0; 
	// for(; it != particle_list.end(); it++, i++)
	// {
	// 	cout<< *it << endl;
	// 	cout << "Accessing particle\n" <<endl;
	// 	// string curr_fileName =  to_string(i)+ ".txt";
	// 	// ofstream curr; 
	// 	// curr.open(curr_fileName);
		
	// 	for (auto& curseur : (*it).chronographe) 
	// 	{	
	// 		cout << "Running curseur" << endl;
	// 		cout << curseur << endl;	
	// 	//	curr << curseur;
	// 	//	curr << "\n";
	// 	}	
	// }
	// 	// for (auto& curseur : (*it).chronographe) 
	// 	// {	
	// 	// 	cout << "Running curseur" << endl;
	// 	// 	cout << curseur << endl;	
	// 	// //	curr << curseur;
	// 	// //	curr << "\n";
	// 	// }	
	// 	// curr.close();

	//}
	// cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Testing box %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
	// Boite B(3, 1.0);
	// cout << B << endl;
	// B.Injecter(Soleil);
	// B.Injecter(Terre);
	// B.Injecter(Mercure);
	// cout << "Injected Soleil and Terre..." << endl;
	// cout << B << endl;

	// cout << "------------------------------------------------Displaced Particles--------------------------------------" << endl;
	// // for(int i=0; i<10; i++)
	// // {
	// // 	B.Bilan_force_complet(B);
	// // 	B.Deplacer_particules_interieur(1.0);
	// // } 

	// // Update with timeout (total time) = 20s, timestep (number of steps in 1 s)  = 5
	// B.Update(20, 20);

	// cout << "\nChronograph of terre -------------" << endl;
	// for (auto& curseur : Terre.chronographe) 
	// {
	// 	cout << curseur << endl;	
	// 	earth_txtOut << curseur ;
	// 	earth_txtOut << "\n";
	// }	
	// // cout << "velocity ---------------------------" << endl;
	// // for (auto& curseur : Terre.velocitycheck) 
	// // {
	// // 	cout << curseur << endl;	

	// // }	
	
	// cout << "\nChronograph of sun -------------" << endl;
	// for (auto& curseur : Soleil.chronographe) 
	// {
	// 	cout << curseur << endl;	
	// 	sun_txtOut << curseur ;
	// 	sun_txtOut << "\n";
	// }

	// 	cout << "\nChronograph of mercury -------------" << endl;
	// for (auto& curseur : Mercure.chronographe) 
	// {
	// 	cout << curseur << endl;	
	// 	mercury_txtOut << curseur ;
	// 	mercury_txtOut << "\n";
	// }




	ourWorld_txtOut.close();
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
