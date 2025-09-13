#ifndef SQUARECELL_H
#define SQUARECELL_H
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <array>
#include "error_squarecell.h"
#include "graphic.h"
using namespace std ;


constexpr short unsigned g_dim(7);


constexpr short unsigned g_max(pow(2,g_dim));


static vector<vector<bool>> grid (g_max, vector<bool>(g_max, false));  


static vector<vector<string>> grid_str (g_max, vector<string>(g_max, "null"));


struct Point {
	int x;
	int y;
};


struct Square {
	Square(int a=0, int b=0, int c=0) { Point p; p.x=a; p.y=b; co=p; side=c; origine=0;}
	int side;
	bool origine;
	Point co;
};


Square set_square(int a, int b, int c);


void init_centre(Square& d);

 
Square change_co(Square& r);


void test_inside(int x, int y, Square a);


void validation_carre(Square a);                                                                                                   


bool adjust_F_coin1(Square a, int diff);


bool adjust_F_coin2(Square a, int diff);


bool adjust_F_coin3(Square a, int diff);


bool adjust_F_coin4(Square a, int diff);


bool adjust_superpo1(Square a, Square b, int diff);


bool adjust_superpo2(Square a, Square b, int diff);


bool adjust_superpo3(Square a, Square b, int diff);


bool adjust_superpo4(Square a, Square b, int diff);


bool appel_superposition_2_carre(double x1, double y1, double x2, double y2, double side1, double side2);


bool appel_grow(double x1, double y1, double x2, double y2, double side1, double side2);


bool appel_superposition_2_carre_move(double x1, double y1, double x2, double y2, double side1, double side2);


bool superposition_2_carre(Square a, Square b);                                                                           


bool last_verif_sup(double x1, double y1, double x2, double y2, double side1, double side2);


bool superposition_2_carre_move(Square a, Square b);  


bool superposition_big_other(Square& a, Square& b);  // pas utiliser je crois 


bool carre_inclus(Square a, Square b);


bool carre_inclus_ouvert(Square a, Square b);


bool med2_is_out(Square b, Square a);


array<int,4> validation_superposition(Square a);                                                                         


void occupation(Square a);                                                                                                 


void occupation_str(Square a, string b);


void liberation(Square a);                                                                                                 


void affichage();                                                                                  


void affichage_str();


void set_grid();


void set_test_verif(bool r);


bool get_test_verif();


void dessiner_square(Square p, string style, array<double,6> couleur);


bool find_space(int j, int i);


bool out(int j, int i);


bool find_space_up(int j, int i);


void compt_space(int i, int j, int& compt);


bool find_space_down(int j, int i);


bool find_last_space(int j, int i);


bool bool_balayage(string a, Square q);


int balayage_x(string c, Square q);


int balayage_y(string p, Square q);


bool contact_carre_vide(Square a, Square b);


bool find_space_big(int x, int y);


bool find_space_big_diago(int x, int y);


bool find_space_med1(int x, int y);


bool find_space_small(int x, int y);


bool test_diago(Square& a, Square b);


int Max(int a, int b);


int find_obstacle_c(Square m, int j, int i);


int detect_obstacle(Square m, int co_x, int co_y, int nb_saut, int axe1, int axe2);


bool contact_2_carre(Square a, Square b);


bool small_contact(Square a, Square b);


bool little_contact(Square a, Square b);


void distance_coin2(Square& a, Square& b, int& coin, 
									int& coin_ref, bool& c, bool& d, bool& e, bool& f);

void distance_coin3(Square& a, Square& b, int& coin, 
									int& coin_ref, bool& c, bool& d, bool& e, bool& f);

void distance_coin4(Square& a, Square& b, int& coin, 
									int& coin_ref, bool& c, bool& d, bool& e, bool& f);

void compare_d_bordure(int& d1, int& d2, int& d3, int& d4, array<int,7>& direction);


void find_exit(Square& a, vector<array<int,3>>& c, array<int,7>& direction);


void way_exit1(Square& a, Square b, bool& change);


void way_exit2(Square& a, Square b, bool& change);


void way_exit3(Square& a, Square b, bool& change);


void way_exit4(Square& a, Square b, bool& change);


void way_exit5(Square& a, Square b, bool& change);


void enter_les_coins(bool c, bool d, bool e, bool f, 
							Square a, vector<array<int,3>>& les_coins);

void exit_F(Square& a, Square b, bool p);


void maje_1(Square&a, array<int,9> n);


void maje_2(Square&a, array<int,9> n);


void maj_for_exit(array<int,9> n, Square& a, bool k);


void appel_dir1(Square& m, int x1, int y1 );


void appel_dir2(Square& m, int x1, int y1 );


void find_direction(Square& m,int& x1, int& y1, int& dir1, int& dir2, bool food);


void pick_up_obstacle0(Square& m, int& compteur_1, int& compteur_2, int& nb_1, int& nb_2);


void appel_come_back(int x, int y, Square& m, Square b, bool& modif, bool food);


void come_back(Square& m, Square b, bool food);


bool food_include_in_c(Square a, Square b);           


void find_direction_big(Square& m, Square& b, int& dir1, int& dir2);       


void appel_maj1(Square& m);


void appel_maj2(Square& m);


void appel_maj3(Square& m);


void appel_maj4(Square& m);


void appel_maj5(Square& m);


void appel_maj6(Square& m);


void appel_maj7(Square& m);


void appel_maj8(Square& m);


void maj(array<int,9> n, Square& m, bool v);


bool out_of_map(int x, int y);


double euclide(int x1, int y1, int x2, int y2);


bool some_body(Square a, Square b);


size_t find_min_id(vector<double> delta);


#endif
