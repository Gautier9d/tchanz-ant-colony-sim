//340423 : 50% 340933 : 50%
#include <iostream>
#include <array>
#include <cmath>
#include <string>
#include "squarecell.h"
#include "error_squarecell.h"
using namespace std;


using namespace error_squarecell;


static bool test_verif;


Square set_square(int a, int b, int c) {
	Square q(a,b,c);
	init_centre(q);
	validation_carre(q);
	return q;
}


void init_centre(Square& d) {
	if(not((d.side)%2==0)) {
		d.origine=true;
	} else {
		d.origine=false; 
	}
}


Square change_co(Square& r) {                
	Square carre;
	if(r.origine) {
		carre.co.x=(r.co.x-(r.side/2));   
        carre.co.y=(r.co.y-(r.side/2));
    } else {
		carre.co.x=r.co.x;
		carre.co.y=r.co.y;
	}
	carre.side=r.side;
	carre.origine=r.origine;
	return carre;
}


void test_inside(int x, int y, Square a) {
	if(a.side==3) {
		if(not((0 <= x) and (x <= g_max-3)) and (test_verif==false)) {
			cout << error_squarecell::print_index(a.co.x,g_max-1);                    
			set_test_verif(true);
		}
		if(not((0 <= y) and (y <= g_max-3)) and (test_verif==false)) {                 
			cout << error_squarecell::print_index(a.co.y,g_max-1);
			set_test_verif(true);
		}
	} else if(a.side==1) {
		if(not((0 <= x) and (x <= g_max-1))) {
			cout << error_squarecell::print_index(a.co.x,g_max-1);                    
			set_test_verif(true);
		}
		if(not((0 <= y) and (y <= g_max-1)) and (test_verif==false)) {                 
			cout << error_squarecell::print_index(a.co.y,g_max-1);
			set_test_verif(true);
		}
	} else if(a.side==5) {
		if(not((0 <= x) and (x <= g_max-5))) {
			cout << error_squarecell::print_index(a.co.x,g_max-1);                   
			set_test_verif(true);
		}
		if(not((0 <= y) and (y <= g_max-5)) and (test_verif==false)) {                 
			cout << error_squarecell::print_index(a.co.y,g_max-1);
			set_test_verif(true);
		}
	}
}


void validation_carre(Square a) {  
	Square u;                    
	double x,y;                  
	u=change_co(a);              
	x=u.co.x;                    
	y=u.co.y; 
	test_inside(x, y, a);
	x+=a.side;
	y+=a.side;
	if(not((0 <= x) and (x <= g_max)) and (test_verif==false)) {                    
		cout << error_squarecell::print_outside(x-a.side,a.side,g_max-1);
		set_test_verif(true);
	}
	if(not((0 <= y) and (y <= g_max)) and (test_verif==false)) {                     
		cout << error_squarecell::print_outside(y-a.side,a.side,g_max-1);
		set_test_verif(true);
	}		
}


bool adjust_F_coin1(Square a, int diff) {
	int x,y;
	x=a.co.x;                    
	y=a.co.y; 
	if(not((0 <= x) and (x <= g_max))) {
		return true;
	}
	if(not((0 <= y) and (y <= g_max))) {
		return true;
	}
	x+=(a.side+diff);
	y+=(a.side+diff);
	if(not((0 <= x) and (x <= g_max))) {
		return true;
	}
	if(not((0 <= y) and (y <= g_max))) {
		return true;
	}
	return false;
}


bool adjust_F_coin2(Square a, int diff) {
	int x,y;
	x=a.co.x;                    
	y=a.co.y-diff; 
	if(not((0 <= x) and (x <= g_max))) {
		return true;
	}
	if(not((0 <= y) and (y <= g_max))) {
		return true;
	}
	x+=(a.side+diff);
	y=(a.co.y+a.side);
	if(not((0 <= x) and (x <= g_max))) {
		return true;
	}
	if(not((0 <= y) and (y <= g_max))) {
		return true;
	}
	return false;
}


bool adjust_F_coin3(Square a, int diff) {
	int x,y;
	x=a.co.x-diff;                    
	y=a.co.y-diff; 
	if(not((0 <= x) and (x <= g_max))) {
		return true;
	}
	if(not((0 <= y) and (y <= g_max))) {
		return true;
	}
	x=a.co.x+a.side;
	y=a.co.y+a.side;
	if(not((0 <= x) and (x <= g_max))) {
		return true;
	}
	if(not((0 <= y) and (y <= g_max))) {
		return true;
	}
	return false;
}


bool adjust_F_coin4(Square a, int diff) {
	int x,y;
	x=a.co.x-diff;                    
	y=a.co.y; 
	if(not((0 <= x) and (x <= g_max))) {
		return true;
	}
	if(not((0 <= y) and (y <= g_max))) {
		return true;
	}
	x=a.co.x+a.side;
	y=a.co.y+a.side;
	if(not((0 <= x) and (x <= g_max))) {
		return true;
	}
	if(not((0 <= y) and (y <= g_max))) {
		return true;
	}
	return false;
}


bool appel_superposition_2_carre(double x1, double y1, 
							double x2, double y2, double side1, double side2) {
	if(((x1-x2)>0 and (x1-x2)<(side2)) 
			and ((y1-y2)<0 and sqrt((y1-y2)*(y1-y2))<(side1))) {
		return true;
	}
	if(((x1-x2)<0 and (sqrt((x1-x2)*(x1-x2)))<(side1)) 
			and ((y1-y2)>0 and sqrt((y1-y2)*(y1-y2))<(side2))) {
		return true;
	}
	if(((x1-x2)<0 and (sqrt((x1-x2)*(x1-x2)))<(side1)) 
			and ((y1-y2)<0 and sqrt((y1-y2)*(y1-y2))<(side1))) {
		return true;
	}
	if(((x1-x2)>0 and (x1-x2)<(side2)) 
			and ((y1-y2)>0 and sqrt((y1-y2)*(y1-y2))<(side2))) {  //x1
		return true;
	}
	if(x1==x2){
		if((y1-y2)<0 and sqrt((y1-y2)*(y1-y2))<=(side1)) {
			return true;
		}
		if((y1-y2)>0 and sqrt((y1-y2)*(y1-y2))<=(side2)) {
			return true;
		}
	}
	if(y1==y2) {
		if((x1-x2)>0 and (x1-x2)<=(side2)) {
			return true;
		}
		if((x1-x2)<0 and (sqrt((x1-x2)*(x1-x2)))<=(side1)) {
			return true;
		}
	}
	if(x1==x2 and y1==y2) {
		return true;
	}
	return false;
}


bool last_verif_sup(double x1, double y1, double x2, 
							double y2, double side1, double side2) {
	if(x1==x2){
		if((y1-y2)<0 and sqrt((y1-y2)*(y1-y2))<(side1)) {
			return true;
		}
		if((y1-y2)>0 and sqrt((y1-y2)*(y1-y2))<(side2)) {
			return true;
		}
	}
	if(y1==y2) {
		if((x1-x2)>0 and (x1-x2)<(side2)) {
			return true;
		}
		if((x1-x2)<0 and (sqrt((x1-x2)*(x1-x2)))<(side1)) {
			return true;
		}
	}
	if(x1==x2 and y1==y2) {
		return true;
	}
	return false;
}


bool appel_grow(double x1, double y1, double x2, 
							double y2, double side1, double side2) {
	if(((x1-x2)>=0 and (x1-x2)<(side2)) 
			and ((y1-y2)<=0 and sqrt((y1-y2)*(y1-y2))<(side1))) {
		return true;
	}
	if(((x1-x2)<=0 and (sqrt((x1-x2)*(x1-x2)))<(side1)) 
			and ((y1-y2)>=0 and sqrt((y1-y2)*(y1-y2))<(side2))) {
		return true;
	}
	if(((x1-x2)<=0 and (sqrt((x1-x2)*(x1-x2)))<(side1)) 
			and ((y1-y2)<=0 and sqrt((y1-y2)*(y1-y2))<(side1))) {
		return true;
	}
	if(((x1-x2)>=0 and (x1-x2)<(side2)) 
			and ((y1-y2)>=0 and sqrt((y1-y2)*(y1-y2))<(side2))) { 
		return true;
	}
	if(x1==x2){
		if((y1-y2)<=0 and sqrt((y1-y2)*(y1-y2))<(side1)) {
			return true;
		}
		if((y1-y2)>=0 and sqrt((y1-y2)*(y1-y2))<(side2)) {
			return true;
		}
	}
	if(y1==y2) {
		if((x1-x2)>=0 and (x1-x2)<(side2)) {
			return true;
		}
		if((x1-x2)<=0 and (sqrt((x1-x2)*(x1-x2)))<(side1)) {
			return true;
		}
	}
	if(x1==x2 and y1==y2) {
		return true;
	}
	return false;
}


bool appel_superposition_2_carre_move(double x1, double y1, 
						double x2, double y2, double side1, double side2) {
	if(((x1-x2)>=0 and (x1-x2)<=(side2)) 
			and ((y1-y2)<=0 and sqrt((y1-y2)*(y1-y2))<=(side1))) {
		return true;
	}
	if(((x1-x2)<=0 and (sqrt((x1-x2)*(x1-x2)))<=(side1)) 
			and ((y1-y2)>=0 and sqrt((y1-y2)*(y1-y2))<=(side2))) {
		return true;
	}
	if(((x1-x2)<=0 and (sqrt((x1-x2)*(x1-x2)))<=(side1)) 
			and ((y1-y2)<=0 and sqrt((y1-y2)*(y1-y2))<=(side1))) {
		return true;
	}
	if(((x1-x2)>=0 and (x1-x2)<=(side2)) 
			and ((y1-y2)>=0 and sqrt((y1-y2)*(y1-y2))<=(side2))) {  
		return true;
	}
	if(x1==x2){
		if((y1-y2)<0 and sqrt((y1-y2)*(y1-y2))<=(side1)) {
			return true;
		}
		if((y1-y2)>0 and sqrt((y1-y2)*(y1-y2))<=(side2)) {
			return true;
		}
	}
	if(y1==y2) {
		if((x1-x2)>0 and (x1-x2)<=(side2)) {
			return true;
		}
		if((x1-x2)<0 and (sqrt((x1-x2)*(x1-x2)))<=(side1)) {
			return true;
		}
	}
	if(x1==x2 and y1==y2) {
		return true;
	}
	return false;
}


bool superposition_2_carre(Square a, Square b) {  
	if(b.side==3) {
		b.co.x-=1;
		b.co.y-=1;
	}
	if(b.side==5) {
		b.co.x-=2;
		b.co.y-=2;
	}
	if(a.side==3) {
		if(appel_superposition_2_carre(a.co.x-1, 
								a.co.y-1, b.co.x, b.co.y, a.side, b.side)) {                   
			return true;
		}
	}
	if(a.side==1) {
		if(appel_superposition_2_carre(a.co.x, 
								a.co.y, b.co.x, b.co.y, a.side, b.side)) {                     
			return true;
		}
	}
	if(a.side==5) {
		if(appel_superposition_2_carre(a.co.x-2, 
								a.co.y-2, b.co.x, b.co.y, a.side, b.side)) {                  
			return true;
		}
	}
	return false;
}


bool superposition_2_carre_move(Square a, Square b) {  
	if(b.side==3) {
		b.co.x-=1;
		b.co.y-=1;
	}
	if(b.side==5) {
		b.co.x-=2;
		b.co.y-=2;
	}
	if(a.side==3) {
		if(appel_superposition_2_carre_move(a.co.x-1, 
								a.co.y-1, b.co.x, b.co.y, a.side, b.side)) {            
			return true;
		}
	}
	if(a.side==1) { 
		if(appel_superposition_2_carre_move(a.co.x, a.co.y, 
									b.co.x, b.co.y, a.side, b.side)) {                  
			return true;
		}
	}
	if(a.side==5) {
		if(appel_superposition_2_carre_move(a.co.x-2, a.co.y-2, 
										b.co.x, b.co.y, a.side, b.side)) {              
			return true;
		}
	}
	return false;
}


bool superposition_big_other(Square& a, Square& b) {                                                           
	if(a.side==3) {
		if(appel_superposition_2_carre_move(a.co.x-1, a.co.y-1, 
							b.co.x-2, b.co.y-2, a.side, b.side)) {          
			return true;
		}
	}
	if(a.side==1) {
		if(appel_superposition_2_carre_move(a.co.x, a.co.y, 
							b.co.x-2, b.co.y-2, a.side, b.side)) {                 
			return true;
		}
	}
	if(a.side==5) {
		if(appel_superposition_2_carre_move(a.co.x-2, 
							a.co.y-2, b.co.x-2, b.co.y-2, a.side, b.side)) {           
			return true;
		}
	}
	return false;
}


bool adjust_superpo1(Square a, Square b, int diff) {
	double x1,y1,side_a;    
	x1=a.co.x;
	y1=a.co.y;
	side_a=a.side;
	Square u2;
	double x2,y2,side_b;
	x2=b.co.x;
	y2=b.co.y;
	side_b=b.side+diff;
	if(appel_grow(x1, y1, x2, y2, side_a, side_b)) {
		return true;
	} else {
		return false;
	}
}


bool adjust_superpo2(Square a, Square b, int diff) {
	double x1,y1,side_a;    
	x1=a.co.x;
	y1=a.co.y;
	side_a=a.side;
	Square u2;
	double x2,y2,side_b;
	x2=b.co.x;
	y2=b.co.y-diff;
	side_b=b.side+diff;
	if(appel_grow(x1, y1, x2, y2, side_a, side_b)) {
		return true;
	} else {
		return false;
	}
}


bool adjust_superpo3(Square a, Square b, int diff) {
	double x1,y1,side_a;    
	x1=a.co.x;
	y1=a.co.y;
	side_a=a.side;
	Square u2;
	double x2,y2,side_b;
	x2=b.co.x-diff;
	y2=b.co.y-diff;
	side_b=b.side+diff;
	if(appel_grow(x1, y1, x2, y2, side_a, side_b)) {
		return true;
	} else {
		return false;
	}
}


bool adjust_superpo4(Square a, Square b, int diff) {
	double x1,y1,side_a;    
	x1=a.co.x;
	y1=a.co.y;
	side_a=a.side;
	Square u2;
	double x2,y2,side_b;
	x2=b.co.x-diff;
	y2=b.co.y;
	side_b=b.side+diff;
	if(appel_grow(x1, y1, x2, y2, side_a, side_b)) {
		return true;
	} else {
		return false;
	}
}


bool carre_inclus(Square a, Square b) {                                 // retourne true si le carre est bien inclus dans l'autre   // rajouter passage par reference 
	bool t(false);
	Square h,k;
	h=change_co(a);
	k=change_co(b);
	double x1,y1;
	x1=h.co.x;
	y1=h.co.y;
	double x2,y2;
	x2=k.co.x;
	y2=k.co.y;
	int new_x1(x1+a.side);
	int new_y1(y1+a.side);
	int new_x2(x2+b.side);
	int new_y2(y2+b.side);
	if(((x1 > x2) and (y1 > y2)) and ((new_x1 < new_x2) and (new_y1 < new_y2))) {
		t=true;
	}
	return t;
}


bool carre_inclus_ouvert(Square a, Square b) {                          // retourne true si le carre est bien inclus dans l'autre   // rajouter passage par reference 
	if(a.side==3) {
		a.co.x-=1;
		a.co.y-=1;
	}
	if(a.side==5) {
		a.co.x-=2;
		a.co.y-=2;
	}
	if(b.side==3) {
		b.co.x-=1;
		b.co.y-=1;
	}
	if(b.side==5) {
		b.co.x-=2;
		b.co.y-=2;
	}
	int new_x1(a.co.x+a.side);
	int new_y1(a.co.y+a.side);
	int new_x2(b.co.x+b.side);
	int new_y2(b.co.y+b.side);
	if(((a.co.x >= b.co.x) and (a.co.y >= b.co.y)) and ((new_x1 <= new_x2) and (new_y1 <= new_y2))) {
		return true;
	}
	return false;
}


bool med2_is_out(Square a, Square b) {
	if(a.side==3) {
		a.co.x-=1;
		a.co.y-=1;
	}
	if(a.side==5) {
		a.co.x-=2;
		a.co.y-=2;
	}
	if((a.co.x+a.side)<=b.co.x) { 
		return true;
	}
	if(a.co.y>=(b.co.y+b.side)) {
		return true;
	}
	if(a.co.x>=(b.co.x+b.side)) {
		return true;
	}
	if((a.co.y+a.side)<=b.co.y) {
		return true;
	}
	return false;
}


array<int,4> validation_superposition(Square a) {
	Square u;
	u = change_co(a);
	double x,y;
	x=u.co.x;
	y=u.co.y;  
	array<int,4> tab;                                                            
	int g(0),h(0);
	int compteur(0); 
	for(int i(y+a.side-1); i >= y ; --i) {                                        
		for(int j(x) ; j < (x+a.side) ; ++j) {
			if((i>=0) and (i<=(g_max-1)) and (j>=0) and (j<=(g_max-1))) {
				if(grid[j][i]) {                                                        
					++compteur;
					if(compteur==1) {    
						g=j;
						h=i;
					}
				}
			}
		}
	}
	tab[0]=g;                                                                   
	tab[1]=h;                                                                      
	tab[2]=compteur;
	if(compteur >=1) {
		tab[3]=1;                                                                
	} else { 
		tab[3]=0;
	}
	return tab;
}


void occupation(Square a) {
	if(a.side==1) {
		grid[a.co.x][a.co.y]=true;
	}
	if(a.side==3) {	
		for(int i(a.co.x-1); i < (a.co.x+2) ; ++i) {
			for(int j(a.co.y-1) ; j < (a.co.y+2) ; ++j) {
				grid[i][j]=true;
			}
		}
	}
	if(a.side==5) {
		for(int i(a.co.x-2); i < (a.co.x+3) ; ++i) {
			for(int j(a.co.y-2) ; j < (a.co.y+3) ; ++j) {
				grid[i][j]=true;
			}
		}
	}
}


void occupation_str(Square a, string b) {
	if(a.side==1) {
		if((a.co.x>=0) and (a.co.x<=(g_max-2)) and (a.co.y>=0) and (a.co.y<=(g_max-2))) {
			grid_str[a.co.x][a.co.y]=b;
		}
	}
	if(a.side==3) {	
		for(int i(a.co.x-1); i < (a.co.x+2) ; ++i) {
			for(int j(a.co.y-1) ; j < (a.co.y+2) ; ++j) {
				if((i>=0) and (i<=(g_max-1)) and (j>=0) and (j<=(g_max-1))) {
					grid_str[i][j]=b;
				}
			}
		}
	}
	if(a.side==5) {
		for(int i(a.co.x-2); i < (a.co.x+3) ; ++i) {
			for(int j(a.co.y-2) ; j < (a.co.y+3) ; ++j) {
				if((i>=0) and (i<=(g_max-1)) and (j>=0) and (j<=(g_max-1))) {
					grid_str[i][j]=b;
				}
			}
		}
	}
}


void liberation(Square a) {   
	if(a.side==1) {
		grid[a.co.x][a.co.y]=false;
	}
	if(a.side==3) {
		for(int i(a.co.x-1); i < (a.co.x+2) ; ++i) {
			for(int j(a.co.y-1) ; j < (a.co.y+2) ; ++j) {
				grid[i][j]=false;
			}
		}
	}
	if(a.side==5) {
		for(int i(a.co.x-2); i < (a.co.x+3) ; ++i) {
			for(int j(a.co.y-2) ; j < (a.co.y+3) ; ++j) {
				grid[i][j]=false;
			}
		}
	}
}


void affichage() { 
	for (size_t i(g_max-1); i > 0; --i) {
		for (size_t j(0); j < g_max; ++j) {
			if (grid[j][i] == true)
				cout << "■ ";
			else 
				cout << "_ ";
		}
	cout << endl;
	}
}


void affichage_str() { 
	for (size_t i(0); i < g_max; ++i) {
		for (size_t j(0); j < g_max; ++j) {
			if (grid_str[i][j] == "null")
				cout << "_ ";
			else 
				cout << grid_str[i][j];
		}
		cout << endl;
	}
}


void set_grid() {
	for(size_t i(0); i < grid[0].size() ; ++i) {
		for(size_t j(0) ; j < grid[i].size() ; ++j) {
			grid[j][i]=false;
		}
	}
	for(size_t i(0); i < grid_str[0].size() ; ++i) {
		for(size_t j(0) ; j < grid_str[i].size() ; ++j) {
			grid_str[j][i]="null";
		}
	}
}


void set_test_verif(bool r) {
	test_verif=r;
}


bool get_test_verif() {
	return test_verif;
}


void dessiner_square(Square p, string style, array<double,6> couleur) {
	if(style=="Uniforme") {
		if(p.side==5) {
			dessins_Uniforme(p.co.x, p.co.y, couleur,5);
		} else {
			dessins_Uniforme(p.co.x, p.co.y, couleur,1);
		}
	}
	if(style=="Diagonale") {
		dessins_Diagonale(p.co.x, p.co.y, couleur);
	}
	if(style=="Grille") {
		dessins_Grille(p.co.x, p.co.y, couleur);
	}
	if(style=="Losange") {
		dessins_Losange(p.co.x, p.co.y, couleur);
	}
	if(style=="Vide") {
		dessins_Vide(p.co.x, p.co.y, p.side, couleur);
	}
}


bool find_space(int j, int i) {                                         // trouve 9 cases adjacentes pour pouvoir mettre un collector ou denfensor
	if(not(grid[j][i])) {
		if(not(grid[j+1][i])) {
			if(not(grid[j+2][i])) {
				if(not(grid[j][i+1])) {
					if(not(grid[j+1][i+1])) {
						if(not(grid[j+2][i+1])) {
							if(not(grid[j][i+2])) {
								if(not(grid[j+1][i+2])) {
									if(not(grid[j+2][i+2])) {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}


bool out(int j, int i) {                                  // retourne true si le collector en deplacement va sortir de la map pour eviter le seg fault 
	if((j<0) or (i<0) or (j+2>=g_max) or (i+2>=g_max)) {
		return true;
	} else {
		return false;
	}
}


bool find_space_up(int j, int i) {      // trouve 9 cases adjacentes pour pouvoir mettre un collector ou denfensor  // j=x, i=y et b est la co x du collector pour verifier si elle est sur la meme diago que la nourriture
	if(out(j,i)) {
		return false;
	} else {
		int compt(0);
		compt_space(i,j,compt);
		if(compt==4) {
			return true;
		} else {
			return false;
		}
	}
}


void compt_space(int i, int j, int& compt) {
	if(grid[j][i]) {
		if(not(grid_str[j][i]=="N")) {
			compt++;
		}
	}
	if(grid[j+1][i]) {
		compt++;
	}
	if(grid[j+2][i]) {
		if(not(grid_str[j+2][i]=="N")) {
			compt++;
		}
	}
	if(grid[j][i+1]) {
		compt++;
	}
	if(grid[j+1][i+1]) {
		compt++;
	}
	if(grid[j+2][i+1]) {
		compt++;
	}
	if(grid[j][i+2]) {
		if(not(grid_str[j][i+2]=="N")) {
			compt++;
		}
	}
	if(grid[j+1][i+2]) {
		compt++;
	}
	if(grid[j+2][i+2]) {
		if(not(grid_str[j+2][i+2]=="N")) {
			compt++;
		}	
	}	
}


bool find_space_down(int j, int i) {      // trouve 9 cases adjacentes pour pouvoir mettre un collector ou denfensor  // j=x, i=y et b est la co x du collector pour verifier si elle est sur la meme diago que la nourriture
	if(out(j,i)) {
		return false;
	} else {
		int compt(0);
		if(grid[j][i]) {
			compt++;
		}
		if(grid[j+1][i]) {
			compt++;
		}
		if(grid[j+2][i]) {
			compt++;
		}
		if(grid[j][i+1]) {
			compt++;
		}
		if(grid[j+1][i+1]) {
			compt++;
		}
		if(grid[j+2][i+1]) {
			compt++;
		}
		if(grid[j][i+2]) {
			compt++;
		}
		if(grid[j+1][i+2]) {
			compt++;
		}
		if(grid[j+2][i+2]) {
			compt++;	
		}	
		if(compt==4) {
				return true;
		} else {
			return false;
		}
	}
}


bool find_last_space(int j, int i) {      // trouve 9 cases adjacentes pour pouvoir mettre un collector ou denfensor
	int compt(0);
	if(grid[j][i]) {
		compt++;
	}
	if(grid[j+1][i]) {
		compt++;
	}
	if(grid[j+2][i]) {
		compt++;
	}
	if(grid[j][i+1]) {
		compt++;
	}
	if(grid[j+1][i+1]) {
		compt++;
	}
	if(grid[j+2][i+1]) {
		compt++;
	}
	if(grid[j][i+2]) {
		compt++;
	}
	if(grid[j+1][i+2]) {
		compt++;
	}
	if(grid[j+2][i+2]) {
		compt++;
	}		
	if(compt==5) {
			return true;
	} else {
		return false;
	}
	return false;
}


bool bool_balayage(string a, Square q) {                                //q est le carre de la fourmilier 
	if(a=="PREDATOR") {	
		for(int i(q.co.x+1); i < (q.co.x+q.side-1) ; ++i) {
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-1) ; ++j) {
					if(not(grid[i][j])) {
						return true;
				}
			}
		}
	} else if(a=="COLLECTOR") {
		for(int i(q.co.x+1); i < (q.co.x+q.side-3) ; ++i) {             // -3 car a chaque tour il test les 2 cases au dessus et il ne faut pas qu'il test au dessus de la fourmiliere 
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-3) ; ++j) {        // a voir si c'est pas -2 au lieu de -3
				if(find_space(i,j)) {
					return true;
				}
			}
		}
	} else if(a=="DEFENSOR") {
		for(int i(q.co.x+1); i < (q.co.x+q.side-3) ; ++i) {             // -3 car a chaque tour il test les 2 cases au dessus et il ne faut pas qu'il test au dessus de la fourmiliere 
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-3) ; ++j) {
				if(find_space(i,j)) {
					return true;
				}
			}											
		}
	}
	return false;
}


int balayage_x(string c, Square q) {
	if(c=="PREDATOR") {	
		for(int i(q.co.x+1); i < (q.co.x+q.side-1) ; ++i) {
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-1) ; ++j) {
					if(not(grid[i][j])) {
						return i;
				}
			}
		}
	} else if(c=="COLLECTOR") {
		for(int i(q.co.x+1); i < (q.co.x+q.side-3) ; ++i) {             // -3 car a chaque tour il test les 2 cases au dessus et il ne faut pas qu'il test au dessus de la fourmiliere 
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-3) ; ++j) {        // a voir si c'est pas -2 au lieu de -3
				if(find_space(i,j)) {
					return i;
				}
			}
		}
	} else if(c=="DEFENSOR") {
		for(int i(q.co.x+1); i < (q.co.x+q.side-3) ; ++i) {             // -3 car a chaque tour il test les 2 cases au dessus et il ne faut pas qu'il test au dessus de la fourmiliere 
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-3) ; ++j) {
				if(find_space(i,j)) {
					return i;
				}
			}											
		}
	}
	return 0;
}


int balayage_y(string p, Square q) {
	if(p=="PREDATOR") {	
		for(int i(q.co.x+1); i < (q.co.x+q.side-1) ; ++i) {
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-1) ; ++j) {
					if(not(grid[i][j])) {
						return j;
				}
			}
		}
	} else if(p=="COLLECTOR") {
		for(int i(q.co.x+1); i < (q.co.x+q.side-3) ; ++i) {             // -3 car a chaque tour il test les 2 cases au dessus et il ne faut pas qu'il test au dessus de la fourmiliere 
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-3) ; ++j) {        // a voir si c'est pas -2 au lieu de -3
				if(find_space(i,j)) {
					return j;
				}
			}
		}
	} else if(p=="DEFENSOR") {
		for(int i(q.co.x+1); i < (q.co.x+q.side-3) ; ++i) {             // -3 car a chaque tour il test les 2 cases au dessus et il ne faut pas qu'il test au dessus de la fourmiliere 
			for(int j(q.co.y+1) ; j < (q.co.y+q.side-3) ; ++j) {
				if(find_space(i,j)) {
					return j;
				}
			}											
		}
	}
	return 0;
}


bool contact_carre_vide(Square a, Square b) {                                // return true si le collector est en contact avec la fourmiliere  //    Square a est un collector attention a le mettre au bon endroit des parametre car il faut remettre  les co en bas a gauche 
	double x1,y1,x2,y2;
	x1=a.co.x-1;
	y1=a.co.y-1;
	x2=b.co.x;
	y2=b.co.y;
	if((y1<=y2+b.side) and (y1>=y2-a.side)) {                           // en contact avec les bords gauche et droit
		if((x1+a.side==x2) or (x1==x2+b.side)) {
			return true;
		}
	}
	if((x1>=x2-a.side) and (x1<=x2+b.side)) {                           // en contact avec les bords haut et bas 
		if((y1==y2+b.side) or (y1+a.side==y2)) {
			return true;
		}
	}
	return false;
}


bool find_space_big(int x, int y) {			                         	//on regarde si le generator va se super poser avec une autre entitie s'il se deplace
	int compt(0);
	x-=2;
	y-=2;
	if((x>=0) and (x<=g_max-4) and (y>=0) and (y<=g_max-4)) {
		for(int i(x); i < x+5; ++i){
			for(int j(y); j < y+5; ++j){
				if(grid[i][j]==true){
					++compt;
				}
			}
		}
	}
	if(compt==20) {
		return true;
	} else {
		return false;
	}
	return false;
}


bool find_space_big_diago(int x, int y) {				                //on regarde si le generator va se super poser avec une autre entitie s'il se deplace
	int compt(0);
	x-=2;
	y-=2;
	if((x>=0) and (x<=g_max-4) and (y>=0) and (y<=g_max-4)) {
		for(int i(x); i < x+5; ++i){
			for(int j(y); j < y+5; ++j){
				if(grid[i][j]==true){
					++compt;
				}
			}
		}
	}
	if(compt==16) {
		return true;
	} else {
		return false;
	}
	return false;
}


bool find_space_med1(int x, int y) {				                        //on regarde si le generator va se superposer avec une autre entitie s'il se deplace
	x-=1;
	y-=1;
	bool s(true);
	if((x>=0) and (x<=(g_max-4)) and (y>=0) and (y<=(g_max-4))) {
		for(int i(x); i < x+3; ++i){
			for(int j(y); j < (y+3); ++j){
				if(grid[i][j]){
					s = false;
				}
			}
		}
	}
	return s;
}


bool find_space_small(int x, int y) {				                        //on regarde si le generator va se superposer avec une autre entitie s'il se deplace
	if(not(grid[x][y])){
		return true;
	} else {
		return false;
	}
}


bool test_diago(Square& a, Square b) {         // a est carre du collector et b est carre de le nourriture 
	if(((a.co.x%2)==(b.co.x%2)) and ((a.co.y%2)==(b.co.y%2))) {
		return true;
	} else if(((a.co.x%2)!=(b.co.x%2)) and ((a.co.y%2)!=(b.co.y%2))) {
		return true;
	}
	return false;
}


int Max(int a, int b) {
	if(a<b) {
		return b;
	} else {
		return a;
	}
}


int find_obstacle_c(Square m, int j, int i) {
	int compt(0);
	j-=1;                                                               //Reajuste les co du collector en bas a gauche
	i-=1;								                                //Reajuste les co du collector en bas a gauche 
	if((j>=0) and (j<=g_max-3) and (i>=0) and (i<=g_max-3)) {
		if(grid[j][i]) {
			++compt;
		}
		if(grid[j+1][i]) {
			++compt;
		}
		if(grid[j+2][i]) {
			++compt;
		}
		if(grid[j][i+1]) {
			++compt;
		}
		if(grid[j+1][i+1]) {
			++compt;
		}
		if(grid[j+2][i+1]) {
			++compt;
		}
		if(grid[j][i+2]) {
			++compt;
		}
		if(grid[j+1][i+2]) {
			++compt;
		}
		if(grid[j+2][i+2]) {
			++compt;
		}
		return compt;
	} else {
		return 0;
	}
}


int detect_obstacle(Square m, int co_x, int co_y, int nb_saut, int axe1, int axe2) {
	int nb_obstacle(0);
	if(axe1==1 and axe2==1) {
		if(nb_saut>0) {
			for(int i(0); i<nb_saut; ++i) {
				nb_obstacle+=find_obstacle_c(m,co_x+i+1,co_y+i+1);      // i + 1 car le i commence a 0 et on sait deja qu'il n'y a pas de superposition a l'etat initiale 
			}
		}
		if(nb_saut<0) {
			for(int i(0); i<sqrt(pow(nb_saut,2)); ++i) {
 				nb_obstacle+=find_obstacle_c(m,co_x-i-1,co_y-i-1);      // i + 1 car le i commence a 0 et on sait deja qu'il n'y a pas de superposition a l'etat initiale 	
			}
		}
	}
	if(axe1==1 and axe2==(-1)) {
		if(nb_saut>0) {
			for(int i(0); i<nb_saut; ++i) {
				nb_obstacle+=find_obstacle_c(m,co_x+i+1,co_y-i-1);      // i + 1 car le i commence a 0 et on sait deja qu'il n'y a pas de superposition a l'etat initiale 	
			}
		}
		if(nb_saut<0) {
			for(int i(0); i<sqrt(pow(nb_saut,2)); ++i) {
				nb_obstacle+=find_obstacle_c(m,co_x-i-1,co_y+i+1);      // i + 1 car le i commence a 0 et on sait deja qu'il n'y a pas de superposition a l'etat initiale 		
			}
		}
	}
	return nb_obstacle;
}


// on a modifier les superieur ou egal 
bool contact_2_carre(Square a, Square b) {
	a.co.x-=1;
	a.co.y-=1;
	b.co.x-=1;
	b.co.y-=1;
	if((a.co.x+a.side)==(b.co.x)) {                                                //contact avec coté gauche du b
		if(((a.co.y+a.side)>=b.co.y) and ((a.co.y)<=(b.co.y+b.side))) {
			return true;
		}
	}
	if((b.co.x+b.side)==a.co.x) {                                                  // contact avec coté droit du b
		if(((a.co.y+a.side)>=b.co.y) and ((a.co.y)<=(b.co.y+b.side))) {
			return true;
		}
	}
	if(a.co.y==(b.co.y+b.side)) {                                                  // contact avec le coté haut du b
		if(((a.co.x+a.side)>=b.co.x) and (a.co.x<=(b.co.x+b.side))) {
			return true;
		}
	}
	if((a.co.y+a.side)==b.co.y) {
		if(((a.co.x+a.side)>=b.co.x) and (a.co.x<=(b.co.x+b.side))) {
			return true;
		}
	}
	return false;
}


bool small_contact(Square a, Square b) {
	b.co.x-=1;
	b.co.y-=1;
	if((a.co.x+a.side)==(b.co.x)) {                                                //contact avec coté gauche du b
	if(((a.co.y+a.side)>=b.co.y) and ((a.co.y)<=(b.co.y+b.side))) {
			return true;
		}
	}
	if((b.co.x+b.side)==a.co.x) {                                                  // contact avec coté droit du b
		if(((a.co.y+a.side)>=b.co.y) and ((a.co.y)<=(b.co.y+b.side))) {
			return true;
		}
	}
	if(a.co.y==(b.co.y+b.side)) {                                                  // contact avec le coté haut du b
		if(((a.co.x+a.side)>=b.co.x) and (a.co.x<=(b.co.x+b.side))) {
			return true;
		}
	}
	if((a.co.y+a.side)==b.co.y) {
		if(((a.co.x+a.side)>=b.co.x) and (a.co.x<=(b.co.x+b.side))) {
			return true;
		}
	}
	return false;
}


bool little_contact(Square a, Square b) {
	if((a.co.x+a.side)==(b.co.x)) {                                                //contact avec coté gauche du b
	if(((a.co.y+a.side)>=b.co.y) and ((a.co.y)<=(b.co.y+b.side))) {
			return true;
		}
	}
	if((b.co.x+b.side)==a.co.x) {                                                  // contact avec coté droit du b
		if(((a.co.y+a.side)>=b.co.y) and ((a.co.y)<=(b.co.y+b.side))) {
			return true;
		}
	}
	if(a.co.y==(b.co.y+b.side)) {                                                  // contact avec le coté haut du b
		if(((a.co.x+a.side)>=b.co.x) and (a.co.x<=(b.co.x+b.side))) {
			return true;
		}
	}
	if((a.co.y+a.side)==b.co.y) {
		if(((a.co.x+a.side)>=b.co.x) and (a.co.x<=(b.co.x+b.side))) {
			return true;
		}
	}
	return false;
}


void distance_coin2(Square& a, Square& b, int& coin, 
								int& coin_ref, bool& c, bool& d, bool& e, bool& f) {
	if(sqrt(pow(((b.co.x+b.side)-(a.co.x+a.side-1)),2))<=sqrt(pow(((b.co.y+b.side)-(a.co.y+a.side-1)),2))) {
		coin=sqrt(pow(((b.co.x+b.side)-(a.co.x+a.side-1)),2));
		if(coin<coin_ref) {
			coin_ref=coin;
			c=true;
			d=false;
			e=false;
			f=false;
		}
		if(coin==coin_ref) {
			c=true;
		}
	} else {
		coin=sqrt(pow(((b.co.y+b.side)-(a.co.y+a.side-1)),2));
		if(coin<coin_ref) {
			coin_ref=coin;
			c=true;
			d=false;
			e=false;
			f=false;
		}
		if(coin==coin_ref) {
			c=true;
		}
	}
}


void distance_coin3(Square& a, Square& b, int& coin, 
								int& coin_ref, bool& c, bool& d, bool& e, bool& f) {
	if(sqrt(pow(((b.co.x+b.side)-(a.co.x+a.side-1)),2))<=sqrt(pow((a.co.y-b.co.y),2))) {
		coin=sqrt(pow(((b.co.x+b.side)-(a.co.x+a.side-1)),2));
		if(coin<coin_ref) {
			coin_ref=coin;
			c=true;
			d=false;
			e=false;
			f=false;
		}
		if(coin==coin_ref) {
			c=true;
		}
	} else {
		coin=sqrt(pow((a.co.y-b.co.y),2));
		if(coin<coin_ref) {
			coin_ref=coin;
			c=true;
			d=false;
			e=false;
			f=false;
		}
		if(coin==coin_ref) {
			c=true;
		}
	}
}


void distance_coin4(Square& a, Square& b, int& coin, 
								int& coin_ref, bool& c, bool& d, bool& e, bool& f) {
	if(sqrt(pow((a.co.y-b.co.y),2))<=sqrt(pow((a.co.x-a.co.y),2))) {
		coin=sqrt(pow((a.co.y-b.co.y),2));
		if(coin<coin_ref) {
			coin_ref=coin;
			c=true;
			d=false;
			e=false;
			f=false;
		}
		if(coin==coin_ref) {
			c=true;
		}
	} else {
		coin=sqrt(pow((a.co.x-a.co.y),2));
		if(coin<coin_ref) {
			coin_ref=coin;
			c=true;
			d=false;
			e=false;
			f=false;
		}
		if(coin==coin_ref) {
			c=true;
		}
	}
}


void compare_d_bordure(int& d1, int& d2, int& d3, int& d4, array<int,9>& direction) {               // compare les distances entre les coins du collector et les bordure pour mettre les direction de déplacement dans le array direction 
	if(d1>d2) {
		if(d1>d3) {
			if(d1>d4) {
				direction[5]=-1;
				direction[6]=1;
			}
		}
	}
	if(d2>d3) {
		if(d2>d4) {
			if(d2>d1) {
				direction[5]=1;
				direction[6]=1;
			}
		}
	}
	if(d3>d1) {
		if(d3>d2) {
			if(d3>d4) {
				direction[5]=1;
				direction[6]=-1;
			}
		}
	}
	if(d4>d1) {
		if(d4>d2) {
			if(d4>d3) {
				direction[5]=-1;
				direction[6]=-1;
			}
		}
	}
}


void find_exit(Square& a, vector<array<int,3>>& c, array<int,9>& direction) {          //trouve la meilleurs direction a prendre pour sortir de la fourmiliere 
	int d1(0),d2(0),d3(0),d4(0);                                                      // peut etre a modifier si qql chose est vrmt a 0 de distance du bord 
	for(size_t i(0); i<c.size(); ++i) {
		if(c[i][2]==1){
			if(a.co.x>(g_max-(a.co.y+a.side))) {
				d1=(g_max-(a.co.y+a.side));
			} else {
				d1=a.co.x;
			}
		}
		if(c[i][2]==2){
			if((g_max-(a.co.x+a.side))>(g_max-(a.co.y+a.side))) {
				d2=(g_max-(a.co.y+a.side));
			} else {
				d2=(g_max-(a.co.x+a.side));
			}
		}
		if(c[i][2]==3){
			if(a.co.y>(g_max-(a.co.x+a.side))) {
				d3=(g_max-(a.co.x+a.side));
			} else {
				d3=a.co.y;
				
			}
		}
		if(c[i][2]==4){
			if(a.co.x>a.co.y) {
				d4=a.co.y;
			} else {
				d4=a.co.x;
			}
		}
	}
	compare_d_bordure(d1, d2, d3, d4, direction);
}


void way_exit1(Square& a, Square b, bool& change) {                // a carre du collector et b carre de la fourmiliere 
	if((b.co.x>a.co.x) and (b.co.x<(a.co.x+a.side))) {
		if(a.co.y < ((g_max-2)-a.co.y)) {
			if(find_space_down(a.co.x-1,a.co.y+1)) {
				liberation(a);
				a.co.x-=1;
				a.co.y+=1;
				occupation(a);
				change=true;
			}
		} else {
			if(find_space_down(a.co.x-1,a.co.y-1)) {
				liberation(a);
				a.co.x-=1;
				a.co.y-=1;
				occupation(a);
				change=true;
			}
		}
	}
	if((a.co.y<(b.co.y+b.side)) and ((b.co.y+b.side)<(a.co.y+a.side))) {
		if(a.co.x < ((g_max-2)-a.co.x)) {
			if(find_space_down(a.co.x+1,a.co.y+1)) {
				liberation(a);
				a.co.x+=1;
				a.co.y+=1;
				occupation(a);
				change=true;
			}
		} else {
			if(find_space_down(a.co.x-1,a.co.y+1)) {
				liberation(a);
				a.co.x-=1;
				a.co.y+=1;
				occupation(a);
				change=true;
			};
		}
	}
}


void way_exit2(Square& a, Square b, bool& change) {  
	if(((b.co.x+b.side)>a.co.x) and ((b.co.x+b.side)<(a.co.x+a.side))) {
		if(a.co.y < ((g_max-2)-a.co.y)) {
			if(find_space_down(a.co.x+1,a.co.y+1)) {
				liberation(a);
				a.co.x+=1;
				a.co.y+=1;
				occupation(a);
				change=true;
			}
		} else {
			if(find_space_down(a.co.x+1,a.co.y-1)) {
				liberation(a);
				a.co.x+=1;
				a.co.y-=1;
				occupation(a);
				change=true;
			}
		}
	}
}


void way_exit3(Square& a, Square b, bool& change) { 
	if((b.co.x>a.co.x) and (b.co.x<(a.co.x+a.side))) {
		if(a.co.y < ((g_max-2)-a.co.y)) {
			if(find_space_up(a.co.x-1,a.co.y+1)) {
				liberation(a);
				a.co.x-=1;
				a.co.y+=1;
				occupation(a);
				change=true;
			}
		} else {
			if(find_space_up(a.co.x-1,a.co.y-1)) {
				liberation(a);
				a.co.x-=1;
				a.co.y-=1;
				occupation(a);
				change=true;
			}
		}
	}
	if((a.co.y<(b.co.y+b.side)) and ((b.co.y+b.side)<(a.co.y+a.side))) {
		if(a.co.x < ((g_max-2)-a.co.x)) {
			if(find_space_up(a.co.x+1,a.co.y+1)) {
				liberation(a);
				a.co.x+=1;
				a.co.y+=1;
				occupation(a);
				change=true;
			}
		} else {
			if(find_space_up(a.co.x-1,a.co.y+1)) {
				liberation(a);
				a.co.x-=1;
				a.co.y+=1;
				occupation(a);
				change=true;
			};
		}
	}
}


void way_exit4(Square& a, Square b, bool& change) { 
	if(((b.co.x+b.side)>a.co.x) and ((b.co.x+b.side)<(a.co.x+a.side))) {
		if(a.co.y < ((g_max-2)-a.co.y)) {
			if(find_space_up(a.co.x+1,a.co.y+1)) {
				liberation(a);
				a.co.x+=1;
				a.co.y+=1;
				occupation(a);
				change=true;
			}
		} else {
			if(find_space_up(a.co.x+1,a.co.y-1)) {
				liberation(a);
				a.co.x+=1;
				a.co.y-=1;
				occupation(a);
				change=true;
			}
		}
	}
}


void way_exit5(Square& a, Square b, bool& change) {
	if((a.co.y<b.co.y) and (b.co.y<(a.co.y+a.side))) {
		if(a.co.x < ((g_max-2)-a.co.x)) {
			if(find_space_up(a.co.x+1,a.co.y-1)) {
				liberation(a);
				a.co.x+=1;
				a.co.y-=1;
				occupation(a);
				change=true;
			}
		} else {
			if(find_space_up(a.co.x-1,a.co.y-1)) {
				liberation(a);
				a.co.x-=1;
				a.co.y-=1;
				occupation(a);
				change=true;
			}
		}
	}
}


void enter_les_coins(bool c, bool d, bool e, bool f, 
								Square a, vector<array<int,3>>& les_coins) {
	if(c) {
		array<int,3> c1({a.co.x,(a.co.y+a.side),1});
		les_coins.push_back(c1);
	}
	if(d) {
		array<int,3> c2({(a.co.x+a.side),(a.co.y+a.side),2});
		les_coins.push_back(c2);
	}
	if(e) {
		array<int,3> c3({(a.co.x+a.side),a.co.y,3});
		les_coins.push_back(c3);
	}
	if(f) {
		array<int,3> c4({a.co.x,a.co.y,4});
		les_coins.push_back(c4);
	}
}


void exit_F(Square& a, Square b, bool p) {         // p est le boolen, il est a true si le collector est Loaded                             // a carre du collector et b carre de la Fourmiliere 
	bool change(false);
	if(p) {
		way_exit1(a,b,change);
		way_exit2(a,b,change);
	} else {
		way_exit3(a,b,change);
		way_exit4(a,b,change);
	}
	way_exit5(a,b,change);
	if(not(change)) {
		int coin_ref(0);
		int coin1,coin2,coin3,coin4;                                        // pt 1 est en haut a gauche, pt 2 est en haut a droite, pt 3 est en bas a droite et pt 4 est en bas a gauche 
		bool c(false),d(false),e(false),f(false);
		if((sqrt(pow((a.co.x-b.co.x),2)))<=(sqrt(pow(((b.co.y+b.side)-(a.co.y+a.side-1)),2)))) {           
			coin1=sqrt(pow((a.co.x-b.co.x),2));
			coin_ref=coin1; 
			c=true;                                          
		} else {
			coin1=sqrt(pow(((b.co.y+b.side)-(a.co.y+a.side-1)),2));
			coin_ref=coin1; 
			c=true; 
		}
		distance_coin2(a,b,coin2,coin_ref,d,c,e,f);
		distance_coin3(a,b,coin3,coin_ref,e,c,d,f);
		distance_coin4(a,b,coin4,coin_ref,f,c,d,e);
		vector<array<int,3>> les_coins;
		enter_les_coins(c,d,e,f,a,les_coins);
		array<int,9> dir({a.co.x+coin_ref+3,a.co.y+coin_ref+3,0,coin_ref+3,coin_ref+3,0,0,0,0});
		find_exit(a,les_coins,dir);
		maj_for_exit(dir,a,p);
	}
}


void maje_1(Square&a, array<int,9> n) {
	if((n[5]==1) and (n[6]==1)) {                                       // Rentre si le déplacement est selon les axes (1,-1)                                //Rentre si le collector va se déplacer en haut a droite 	
		if(find_space_down(a.co.x,a.co.y)) {		
			liberation(a);
			a.co.x+=1;
			a.co.y+=1;
			//n[3]-=1;
			occupation(a);
		}
	}
	if((n[5]==1) and (n[6]==-1)) {                                      // Rentre si le déplacement est selon les axes (1,-1)                               //Rentre si le collector va se déplacer en haut a droite 
		if(find_space_down(a.co.x,a.co.y-2)) {
			liberation(a);
			a.co.x+=1;
			a.co.y-=1;
			//n[3]-=1;
			occupation(a);
		}
	}
	if((n[5]==-1) and (n[6]==1)) { 
		if(find_space_down(a.co.x-2,a.co.y)) {
			liberation(a);
			a.co.x-=1;
			a.co.y+=1;
			//n[3]-=1;
			occupation(a);
		}
	}	
	if((n[5]==-1) and (n[6]==-1)) { 
		if(find_space_down(a.co.x-2,a.co.y-2)) {
			liberation(a);
			a.co.x-=1;
			a.co.y-=1;
			//n[3]-=1;
			occupation(a);
		}
	}
}


void maje_2(Square&a, array<int,9> n) {
	if((n[5]==1) and (n[6]==1)) {                                       // Rentre si le déplacement est selon les axes (1,-1)                                //Rentre si le collector va se déplacer en haut a droite 	
		if(find_space_up(a.co.x,a.co.y)) {	
			liberation(a);
			a.co.x+=1;
			a.co.y+=1;
			occupation(a);
		}
	}
	if((n[5]==1) and (n[6]==-1)) {                                      // Rentre si le déplacement est selon les axes (1,-1)                               //Rentre si le collector va se déplacer en haut a droite 
		if(find_space_up(a.co.x,a.co.y-2)) {
			liberation(a);
			a.co.x+=1;
			a.co.y-=1;
			occupation(a);
		}
	}
	if((n[5]==-1) and (n[6]==1)) { 
		if(find_space_up(a.co.x-2,a.co.y)) {
			liberation(a);
			a.co.x-=1;
			a.co.y+=1;
			occupation(a);
		}
	}	
	if((n[5]==-1) and (n[6]==-1)) { 
		if(find_space_up(a.co.x-2,a.co.y-2)) {
			liberation(a);
			a.co.x-=1;
			a.co.y-=1;
			occupation(a);
		}
	}
}


void maj_for_exit(array<int,9> n, Square& a, bool k) {
	if(k) {
		maje_1(a,n);
	} else {
		maje_2(a,n);
	}
}


void appel_dir1(Square& m, int x1, int y1 ) {
	if((x1>(m.co.x)) and (y1>(m.co.y))) {                                         // on a mis des -1 sur chaque co pour les placer en bas a gauche 
		if(find_space_down(m.co.x,m.co.y)) {
			liberation(m);
			m.co.x+=1;
			m.co.y+=1;
			occupation(m);
		}
	}
	if((x1>(m.co.x)) and (y1<m.co.y)) {
		if(find_space_down(m.co.x,m.co.y-2)) {
			liberation(m);
			m.co.x+=1;
			m.co.y-=1;
			occupation(m);
		}
	}
	if((x1<m.co.x) and (y1>(m.co.y))) {
		if(find_space_down(m.co.x-2,m.co.y)) {
			liberation(m);
			m.co.x-=1;
			m.co.y+=1;
			occupation(m);
		}
	}
	if((x1<m.co.x) and (y1<m.co.y)) {
		if(find_space_down(m.co.x-2,m.co.y-2)) {
			liberation(m);
			m.co.x-=1;
			m.co.y-=1;
			occupation(m);
		}
	}
}


void appel_dir2(Square& m, int x1, int y1 ) {
	if((x1>(m.co.x)) and (y1>(m.co.y))) {                                         // on a mis des -1 sur chaque co pour les placer en bas a gauche 
		if(find_space_up(m.co.x,m.co.y)) {
			liberation(m);
			m.co.x+=1;
			m.co.y+=1;
			occupation(m);
		}
	}
	if((x1>(m.co.x)) and (y1<m.co.y)) {
		if(find_space_up(m.co.x,m.co.y-2)) {
			liberation(m);
			m.co.x+=1;
			m.co.y-=1;
			occupation(m);
		}
	}
	if((x1<m.co.x) and (y1>(m.co.y))) {
		if(find_space_up(m.co.x-2,m.co.y)) {
			liberation(m);
			m.co.x-=1;
			m.co.y+=1;
			occupation(m);
		}
	}
	if((x1<m.co.x) and (y1<m.co.y)) {
		if(find_space_up(m.co.x-2,m.co.y-2)) {
			liberation(m);
			m.co.x-=1;
			m.co.y-=1;
			occupation(m);
		}
	}
}


void find_direction(Square& m, int& x1, int& y1, int& dir1, int& dir2, bool d) {      // m est le square du collector et x1,y1 les co de la nourriture 
	if(d) {
		appel_dir1(m,x1,y1);
	} else {
		appel_dir2(m,x1,y1);
	}
}


void pick_up_obstacle0(Square& m, int& compteur_1, int& compteur_2, int& nb_1, int& nb_2) { 
	liberation(m);                                              	
	compteur_1+=detect_obstacle(m, m.co.x,m.co.y,nb_1,1,1);                                                //test selon (1,1) avec (vx+vy)/2 sauts                                                      // ici c'est le seg fault 
	if(nb_1>0) { 
		if(nb_2>0) {
			compteur_1+=detect_obstacle(m, m.co.x+nb_1,m.co.y+nb_1,nb_2-1,1,-1);                           //test selon (1,-1)  avec (vx-vy)/2 sauts
		} else {
			compteur_1+=detect_obstacle(m, m.co.x+nb_1,m.co.y+nb_1,nb_2+1,1,-1);
		}
	} else {
		if(nb_2>0) {
			compteur_1+=detect_obstacle(m, m.co.x-nb_1,m.co.y-nb_1,nb_2-1,1,-1);
		} else {
			compteur_1+=detect_obstacle(m, m.co.x-nb_1,m.co.y-nb_1,nb_2+1,1,-1);
		}
	} 			                  
	compteur_2+=detect_obstacle(m,m.co.x,m.co.y,nb_2,1,-1);                                            // attention au moins 1              //test selon (1,-1)  avec (vx-vy)/2 sauts                    
	if(nb_2>0) {
		if(nb_1>0) {
			compteur_2+=detect_obstacle(m,m.co.x+abs(nb_2),m.co.y-abs(nb_2),nb_1-1,1,1);       //test selon (1,1)   avec (vx+vx)/2 sauts
		} else {
			compteur_2+=detect_obstacle(m,m.co.x+abs(nb_2),m.co.y-abs(nb_2),nb_1+1,1,1);
		}
	} else {
		if(nb_1>0) {
			compteur_2+=detect_obstacle(m,m.co.x-abs(nb_2),m.co.y+abs(nb_2),nb_1-1,1,1);
		} else {
			compteur_2+=detect_obstacle(m,m.co.x-abs(nb_2),m.co.y+abs(nb_2),nb_1+1,1,1);
		}
	}	
	occupation(m);
}


void appel_come_back(int x, int y, Square& m, Square b, bool& modif, bool food) {
	int compteur_1(0),compteur_2(0); 														
	int nb_1((x+y)/2),nb_2((x-y)/2);
	pick_up_obstacle0(m,compteur_1,compteur_2,nb_1,nb_2);  
	if(compteur_1==compteur_2) {
		int le_x1,le_y1;
		le_x1=(x+y)/2;
		le_y1=(x-y)/2;
		array<int,9> la_n1({b.co.x,b.co.y,2,le_y1,(le_x1-1),0,0,0,0});
		int xx(m.co.x),yy(m.co.y);
		maj(la_n1,m,food); 
		if(xx==m.co.x and yy==m.co.y) {
			modif=false;
		} else {
			modif=true;
		}
		if(not(modif))   {
			int le_x2((x-y)/2),le_y2((x+y)/2);
			array<int,9> la_n2({b.co.x,b.co.y,2,le_x2,(le_y2-1),0,0,0,0});
			maj(la_n2,m,food);
			modif=true;
		}
	}
	if(compteur_1<compteur_2 and (modif==false)) {                        //chemin 1 choisis 
		int le_x1((x+y)/2),le_y1((x-y)/2);
		array<int,9> la_n1({b.co.x,b.co.y,1,le_x1,(le_y1-1),0,0,0,0});    //Cet array contient les co x et y de la nourriture a allez chercher, puis le chemin, 1 ou 2, 
		maj(la_n1,m,food);                                                     //qui permet de savoir sur quel axe faire les déplacements, (1,1) puis (1,-1) pour le chemin 1, 
		modif=true;                                                   
	}
	if(compteur_1>compteur_2 and (modif==false)) {                        //chemin 2  choisis
		int le_x2,le_y2;                                                  //Cet array contient les co x et y de la nourriture a allez chercher, puis le chemin, 1 ou 2, 
		le_x2=(x-y)/2;                                                    //de sauts a effectuer sur chaque axe
		le_y2=(x+y)/2;  
		array<int,9> la_n2({b.co.x,b.co.y,2,le_x2,(le_y2-1),0,0,0,0});    // on a mis un saut en moins pour le_y car il faut qu'il ne soit que partiellement en superposition a verifier       
		maj(la_n2,m,food); 
		modif=true; 													   
	}
}


void come_back(Square& m, Square b, bool food) {                                   //a est le carre du collector et b le carre de la fourmiliere
	if(test_diago(m,b)) {
		b.co.x=b.co.x+(b.side/2);
		b.co.y=b.co.y+(b.side/2);
	} else {
		b.co.x=b.co.x+(b.side/2)-1;
		b.co.y=b.co.y+(b.side/2);
	}
	int x,y;
	x=(b.co.x-m.co.x);
	y=(b.co.y-m.co.y);
	bool modif(false);
	if((sqrt(pow(x,2))==sqrt(pow(y,2)))) {                              // si les nourritures sont sur les diagonales 
		int dir1,dir2;
		find_direction(m,b.co.x,b.co.y,dir1,dir2,food);  
	} else {
		appel_come_back(x,y,m,b,modif,food);
	}
}


bool food_include_in_c(Square a, Square b) {           // retourne true si le carre est bien inclus dans l'autre 
	bool t(false);
	Square h,k;
	h=change_co(a);
	k=change_co(b);
	double x1,y1;
	x1=h.co.x; 
	y1=h.co.y;
	double x2,y2;
	x2=k.co.x;
	y2=k.co.y;
	int new_x1(x1+a.side);
	int new_y1(y1+a.side);
	int new_x2(x2+b.side);
	int new_y2(y2+b.side);
	if(((x1 >= x2) and (y1 >= y2)) and ((new_x1 <= new_x2) and (new_y1 <= new_y2))) {
		t=true;
	}
	return t;
}


void find_direction_big(Square& m, Square& b, int& dir1, int& dir2) {        // m est le square du collector et b est le square du du generator 
	if((m.co.x-1>=(b.co.x-2+b.side)) and (m.co.y-1>=(b.co.y-2+b.side))) {          // On a mis des -1 pour mettre les oc du collector en bas a gauche et -2 pour mettre celles du generator en bas a gauche 
		dir1=1;                                                                  
		dir2=1;
	}
	if((m.co.x-1>=(b.co.x-2+b.side)) and ((m.co.y+2)<=b.co.y-2)) {                 // attention le m.co.y+2 est pour se mettre en haut du collector 
		dir1=1;
		dir2=-1;
	}
	if((m.co.x-1<=b.co.x-2) and (m.co.y-1>=(b.co.y-2+b.side))) {
		dir1=-1;
		dir2=1;
	}
	if((m.co.x-1<=b.co.x-2) and ((m.co.y-1+1)<=b.co.y-2)) {
		dir1=-1;
		dir2=-1;
	}
}


void appel_maj1(Square& m) {
	if(out_of_map(m.co.x+1, m.co.y+1)) {
		if((m.co.y/m.co.x)>=1) {                            //division entiere 
			if(find_space_down(m.co.x,m.co.y-2)) {
				liberation(m);
				m.co.x+=1;
				m.co.y-=1;
				occupation(m);
			}
		} else {
			if(find_space_down(m.co.x-2,m.co.y)) {
				liberation(m);
				m.co.x-=1;
				m.co.y+=1;
				occupation(m);
			}
		}
	} else {
		if(find_space_down(m.co.x,m.co.y)) {
			liberation(m);
			m.co.x+=1;
			m.co.y+=1;
			occupation(m);
		}
	}
}


void appel_maj2(Square& m) {
	if(out_of_map(m.co.x-1, m.co.y-1)) {
		if((m.co.y/m.co.x)>=1) { 
			if(find_space_down(m.co.x,m.co.y-2)) {
				liberation(m);
				m.co.x+=1;
				m.co.y-=1;
				occupation(m);
			}
		} else {
			if(find_space_down(m.co.x-2,m.co.y)) {
				liberation(m);
				m.co.x-=1;
				m.co.y+=1;
				occupation(m);
			}
		}
	} else {
		if(find_space_down(m.co.x-2,m.co.y-2)) {
			liberation(m);
			m.co.x-=1;
			m.co.y-=1;
			occupation(m);
		}
	}
}


void appel_maj3(Square& m) {
	if(out_of_map(m.co.x+1, m.co.y-1)) {
		if(((m.co.y/(g_max-m.co.x))>=1)) { 
			if(find_space_down(m.co.x-2,m.co.y-2)) {
				liberation(m);
				m.co.x-=1;
				m.co.y-=1;
				occupation(m);
			}
		} else {
			if(find_space_down(m.co.x,m.co.y)) {
				liberation(m);
				m.co.x+=1;
				m.co.y+=1;
				occupation(m);
			}
		}
	} else {
		if(find_space_down(m.co.x,m.co.y-2)) {
			liberation(m);
			m.co.x+=1;
			m.co.y-=1;
			occupation(m);
		}
	}
}


void appel_maj4(Square& m) {
	if(out_of_map(m.co.x-1, m.co.y+1)) {
		if(((m.co.y/(g_max-m.co.x))>=1)) {
			if(find_space_down(m.co.x-2,m.co.y-2)) {
				liberation(m);
				m.co.x-=1;
				m.co.y-=1;
				occupation(m);
			}
		} else {
			if(find_space_down(m.co.x,m.co.y)) {
				liberation(m);
				m.co.x+=1;
				m.co.y+=1;
				occupation(m);
			}
		}
	} else {
		if(find_space_down(m.co.x-2,m.co.y)) {
			liberation(m);
			m.co.x-=1;
			m.co.y+=1;
			occupation(m);
		}
	}
}


void appel_maj5(Square& m) {
	if(out_of_map(m.co.x+1, m.co.y+1)) {
		if((m.co.y/m.co.x)>=1) {                            //division entiere 
			if(find_space_up(m.co.x,m.co.y-2)) {
				liberation(m);
				m.co.x+=1;
				m.co.y-=1;
				occupation(m);
			}
		} else {
			if(find_space_up(m.co.x-2,m.co.y)) {
				
				liberation(m);
				m.co.x-=1;
				m.co.y+=1;
				occupation(m);
			}
		}
	} else {
		cout << endl;
		if(find_space_up(m.co.x,m.co.y)) {
			liberation(m);
			m.co.x+=1;
			m.co.y+=1;
			occupation(m);
		}
	}
}


void appel_maj6(Square& m) {
	if(out_of_map(m.co.x-1, m.co.y-1)) {
		if((m.co.y/m.co.x)>=1) { 
			if(find_space_up(m.co.x,m.co.y-2)) {
				liberation(m);
				m.co.x+=1;
				m.co.y-=1;
				occupation(m);
			}
		} else {
			if(find_space_up(m.co.x-2,m.co.y)) {
				liberation(m);
				m.co.x-=1;
				m.co.y+=1;
				occupation(m);
			}
		}
	} else {
		if(find_space_up(m.co.x-2,m.co.y-2)) {
			liberation(m);
			m.co.x-=1;
			m.co.y-=1;
			occupation(m);
		}
	}
}


void appel_maj7(Square& m) {
	if(out_of_map(m.co.x+1, m.co.y-1)) {
		if(((m.co.y/(g_max-m.co.x))>=1)) { 
			if(find_space_up(m.co.x-2,m.co.y-2)) {
				liberation(m);
				m.co.x-=1;
				m.co.y-=1;
				occupation(m);
			}
		} else {
			if(find_space_up(m.co.x,m.co.y)) {
				liberation(m);
				m.co.x+=1;
				m.co.y+=1;
				occupation(m);
			}
		}
	} else {
		if(find_space_up(m.co.x,m.co.y-2)) {
			liberation(m);
			m.co.x+=1;
			m.co.y-=1;
			occupation(m);
		}
	}
}


void appel_maj8(Square& m) {
	if(out_of_map(m.co.x-1, m.co.y+1)) {
		if(((m.co.y/(g_max-m.co.x))>=1)) {
			if(find_space_up(m.co.x-2,m.co.y-2)) {
				liberation(m);
				m.co.x-=1;
				m.co.y-=1;
				occupation(m);
			}
		} else {
			if(find_space_up(m.co.x,m.co.y)) {
				liberation(m);
				m.co.x+=1;
				m.co.y+=1;
				occupation(m);
			}
		}
	} else {
		if(find_space_up(m.co.x-2,m.co.y)) {
			liberation(m);
			m.co.x-=1;
			m.co.y+=1;
			occupation(m);
		}
	}
}


void maj(array<int,9> n, Square& m, bool v) {
	if(v) {
		if(n[2]==1) {
			if(n[3]>0) {
				appel_maj1(m);
			} else {
				appel_maj2(m);
			}
		}		
		if(n[2]==2) {
			if(n[3]>0) {
				appel_maj3(m);
			} else {
				appel_maj4(m);
			}
		}
	} else {
		if(n[2]==1) {
			if(n[3]>0) {
				appel_maj5(m);
			} else {
				appel_maj6(m);
			}
		}		
		if(n[2]==2) {
			if(n[3]>0) {
				appel_maj7(m);
			} else {
				appel_maj8(m);
			}
		}
	}
	occupation(m);	
}


bool out_of_map(int x, int y) {
	x-=1;
	y-=1;
	if((x==0) or ((x+2)==g_max) or (y==0) or ((y+2)==g_max)) {              // peut etre faire g_max-1 si  seg fault
		return true;
	} else {
		return false;
	}	
}


double euclide(int x1, int y1, int x2, int y2) {
	double d(0.);
	d=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	return d;
}


bool some_body(Square a, Square b) {    //a est inclus ou partiellement inclus dans b
	int x(0), y(0), z(0), t(0);
	x=b.co.x+b.side-1-(a.co.x+1);
	y=b.co.y+b.side-1-(a.co.y+1);
	z=a.co.x-(b.co.x+1);
	t=a.co.y-(b.co.y+1);
	if(a.side==3) {
		if ((x>=-2) and (y>=-2) and (z>=-2) and (t>=-2)) {
			return true;
		}
	} else if(a.side==1) {
		if((x>=0) and (y>=0) and (z>=0) and (t>=0)) {
			return true;
		}
	}
	return false;
}


size_t find_min_id(vector<double> delta) {
	size_t j(0); 
	if(delta.size()==0) {
		j=1000000;
	} else {
		for ( size_t i (1); i < delta.size() ; i++){
			if (delta[i] < delta[j]){
				j = i; 
			}
		}
	}
	return j;
}






























