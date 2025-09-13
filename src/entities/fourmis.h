#ifndef FOURMIS_H
#define FOURMIS_H
#include <iostream>
#include "constantes.h"
#include "squarecell.h"
#include "nourriture.h"
#include <string>
using namespace std;


class Fourmis {
protected:
	Square m;
	int age; 
	bool end_of_life;
	string specie;
	array<int,9> direction;
	bool first_step = false;
private:
	static bool reinit; 
public:
	Fourmis(int xx=0, int yy=0, int aa=0, int s=0) {m=set_square(xx,yy,s); age=aa;}  
	~Fourmis() {liberation(m);}   
	void update();                                                   
	void upgrade_age() {++age;}                                                           
	Square get_m() {return m;}
	int get_age() {return age;}
	bool get_end_of_life() {return end_of_life;}
	string get_specie() {return specie;}
	virtual double get_total_food() {return 0;}
	virtual string get_food() {return 0;} 
	virtual string get_food_string() {return 0;} 
	virtual void set_food(string a) {}
	virtual void add_food() {}
	virtual void soustract_food(double a) {}
	static bool get_reinit() {return reinit;}
	static void set_reinit(bool d) {Fourmis::reinit=d;}
	virtual void se_dessiner(array<double,6>couleur_F) {};
	void set_reinit() {Fourmis::reinit=true;}
	void set_end(bool a) {end_of_life=a;}
	void set_direction(array<int,9> a) {direction=a;}
	virtual void move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
									Square f, vector<Square> preys, bool libre, bool& klan)  {}
};


class Collector : public Fourmis {
public:
	Collector(int xc,int yc, int ac, string i, string spc): Fourmis(xc, yc, ac, sizeC), 
									food(i) {if(not(get_test_verif())) {specie=spc; abs_superposition_c(); 
									occupation(m); end_of_life=false;}}
	Collector(int xc, int yc, int ac, string spc): Fourmis(xc, yc, ac, sizeC)
									{specie=spc; occupation(m); end_of_life=false; food="EMPTY";}
	void test_food();                                                                         	
	void test_atteignabilite();                                                               
	void distance();                                                                           
	void chemin();                                                                             
	void chemin_alternatif();                                                                 
	void fin_premature();                                                                     
	void abs_superposition_c();
	string get_food() {return food;}
	string get_food_string() {if(food=="EMPTY"){return "false"; } else { return "true"; }}
	void set_food(string a) {food=a;}
	void se_dessiner(array<double,6>couleur_F);
	void next_move(vector<Nourriture>& N, Square a);
	void two_way(int co_x, int co_y, int x, int y, bool modif);
	void recup_n(vector<Nourriture>& N, Square m, int& co_x, int& co_y);
	void pick_up(vector<Nourriture>& N);
	virtual void move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
									Square f, vector<Square> preys, bool libre, bool& klan);
private:
	string food; 
};


class Generator : public Fourmis {
public:	
	Generator(int xg, int yg, int ag, double t, Square fi, size_t di, string spg): 
									Fourmis(xg, yg, ag, sizeG), total_food(t) {specie=spg; if(not(get_test_verif())) 
									{abs_superposition_g(); g_include_in_f(fi, di); occupation(m); end_of_life=false;}} 
	void abs_superposition_g();
	void g_include_in_f(Square carre_F, size_t dim);
	double get_total_food() {return total_food;}
	void se_dessiner(array<double,6>couleur_F);
	void add_food() {total_food+=val_food;}
	void soustract_food(double a) {total_food-=a;}
	bool au_coin(int x, int y, int z, int t, bool& change);
	bool au_bord(int x, int y, int z, int t, bool& change);
	virtual void move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
									Square f, vector<Square> preys, bool libre, bool& klan);
private: 
	double total_food;
};


class Defensor: public Fourmis {
private:

public: 
	Defensor(int xd, int yd, int ad, Square de, size_t di, string spd): 
								Fourmis(xd, yd, ad, sizeD) {specie=spd; if(not(get_test_verif())) 
								{abs_superposition_d(); d_include_in_f(de, di) ; occupation(m); end_of_life=false;}}
	Defensor(int xd, int yd, int ad, string spd): 
								Fourmis(xd, yd, ad, sizeD) {specie=spd; occupation(m); end_of_life=false;} 
	void abs_superposition_d();
	void d_include_in_f(Square carre_F, size_t dim);
	void se_dessiner(array<double,6>couleur_F);
	void grad_x(int x);
	void grad_y(int y);
	void grad_z(int z);
	void grad_t(int t);
	virtual void move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
									Square f, vector<Square> preys, bool libre, bool& klan);
};


class Predator : public Fourmis {
private: 

public: 
	Predator(int xp, int yp, int ap, string spp) : Fourmis(xp, yp, ap, sizeP) 
									{specie=spp; if(not(get_test_verif())) {abs_superposition_p(); 
									occupation(m); end_of_life=false;}}
	void abs_superposition_p();
	void se_dessiner(array<double,6>couleur_F);
	void appel_p1(Square f, vector<Square> preys, int a, int b,
										int c , int d , int e , int fr , int g, int h,vector<double>& delta);
	void appel_p2(Square f, vector<Square> preys, int a, int b, 
										int c , int d , int e , int fr , int g, int h,vector<double>& delta);
	virtual void move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
									Square f, vector<Square> preys, bool libre, bool& klan);
	void appel_path(Square p, int a, int b, vector<double>& grad_l,
						int c, int d, int e, int fr, int g, int h);
	vector<double> my_path(Square p, int a, int b,
									int c, int d, int e, int fr, int g, int h);
	void appel_target(Square p, int a, int b, vector<array<int, 2>>& grad,
						int c, int d, int e, int fr, int g, int h);
	vector<array<int,2>> target(Square p, int a, int b, 
									int c, int d, int e, int fr, int g, int h);
	bool among(vector<Square> preys, Square f);
};


#endif
