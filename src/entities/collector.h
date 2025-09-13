#include <iostream>
#include "Fichier_include.h"


using namespace std ;

class Collector : public Fourmis {
	public:
	void test_food();             // test si la nourriture est allignée sur les memes diagonales 	
	void test_atteignabilité();   // vérifie : même parité des 2 coordonnées de fourmi et nourriture,  ou parité différente des 2 coordonnées
	void distance();              // calcule la distance entre la fourmi et l'élément de nourriture
	void chemin();                // evaluation du meilleurs chemin a prendre (celui avec le moins de virage)
	void chemin_alternatif();     // etablilt un chemin symetrique si la fourmi sort du monde 
	void fin_prématuré();         // passe le end_of_life a true si la fourmi est LOADED et si un predator est sur elle
	
	
	private:		
	string food;      // LOADED or EMPTY 
	int val_food;     // un element de nourriture mais ne contient pas forcement la meme quantité
};






















string food;  // LOADED = 1  or EMPTY 
int val_food;     // un element de nourriture mais ne contient pas forcement la meme quantité
void test_food();    // test si la nourriture est allignée sur les memes diagonales 
