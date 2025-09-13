//340423 : 50% 340933 : 50%
#include <iostream>
#include "fourmis.h"
#include "message.h"
using namespace std;


bool Fourmis::reinit = false; 


void Collector::abs_superposition_c() {
	array<int,4> tabb;
	tabb = validation_superposition(m);
	if(tabb[3]) {
		cout << message::collector_overlap(m.co.x, m.co.y, tabb[0], tabb[1]);
		set_reinit();
	}
}


void Collector::se_dessiner(array<double,6> couleur_F) {
	dessiner_square(m, "Diagonale", couleur_F);
	if(food=="LOADED") {
		array<double,6> couleur_N({1.0, 1.0, 1.0, 0.0, 0.0, 0.0});
		Square qn(m.co.x, m.co.y, 0);
		dessiner_square(qn, "Losange", couleur_N);
	}
}


void Collector::next_move(vector<Nourriture>& N, Square a) {                                          
	bool modif(false);
	int co_x(200),co_y(0);
	recup_n(N,m,co_x,co_y);     
	int x(co_x-m.co.x),y(co_y-m.co.y);                                                                
	if(co_x==200) {
		if(not(med2_is_out(m,a))) {
			if((superposition_2_carre_move(m,a)) or (carre_inclus_ouvert(m,a))) {			          
				exit_F(m,a,1); 
			}
		}
	} else {
		if((sqrt(pow(x,2))==sqrt(pow(y,2)))) {                                                        
			int dir1,dir2;
			find_direction(m,co_x,co_y,dir1,dir2,0); 
		} else {                                                                                     
			two_way(co_x,co_y,x,y,modif);
		}	
	}
}


void Collector::two_way(int co_x, int co_y, int x, int y, bool modif) {
	int compteur_1(0),compteur_2(0); 
	int nb_1((x+y)/2),nb_2((x-y)/2);
	pick_up_obstacle0(m,compteur_1,compteur_2,nb_1,nb_2);   	
	if(compteur_1==compteur_2) {
		int le_x1((x+y)/2),le_y1((x-y)/2),xx(m.co.x),yy(m.co.y);
		array<int,9> la_n1({co_x,co_y,1,le_x1,(le_y1-1),0,0,0,0});
		maj(la_n1,m,0);
		if(xx==m.co.x and yy==m.co.y) {
			modif=false;
		} else {
			modif=true;
		}
		if(not(modif))   {
			int le_x2((x-y)/2),le_y2((x+y)/2);
			array<int,9> la_n2({co_x,co_y,2,le_x2,(le_y2-1),0,0,0,0});
			maj(la_n2,m,0);
			modif=true;
		}
	}
	if(compteur_1<compteur_2 and (modif==false)) {                                         
		int le_x1((x+y)/2),le_y1((x-y)/2);
		array<int,9> la_n1({co_x,co_y,1,le_x1,(le_y1-1),0,0,0,0});                         
		maj(la_n1,m,0);                                                                    
		modif=true;                                                                       
	}
	if(compteur_1>compteur_2 and (modif==false)) {                                         
		int le_x2((x-y)/2),le_y2((x+y)/2);                                                 
		array<int,9> la_n2({co_x,co_y,2,le_x2,(le_y2-1),0,0,0,0});                          
		maj(la_n2,m,0);                
		modif=true; 													   
	}
}


void Collector::recup_n(vector<Nourriture>& N, Square m, int& co_x, int& co_y) {		
	int x(200),y(200);
	vector<array<int,2>> les_n;                                                                    
	bool test(false);
	for(size_t i(0); i<N.size(); ++i) {
		if(test_diago(m, N[i].get_square())) {                                                    
			if(test) {
				int x1,y1;
				x1=(int)sqrt(pow((N[i].get_square().co.x-m.co.x),2));
				y1=(int)sqrt(pow((N[i].get_square().co.y-m.co.y),2));                              
				int a(0),b(0);
				a=Max(x1,y1);
				b=Max(x,y);
				if(a<b) {
					x=sqrt(pow((N[i].get_square().co.x-m.co.x),2));                                
					y=sqrt(pow((N[i].get_square().co.y-m.co.y),2)); 
					co_x=N[i].get_square().co.x;
					co_y=N[i].get_square().co.y; 
				}   
			} else {                                                                            
				test=true;  
				x=sqrt(pow((N[i].get_square().co.x-m.co.x),2));
				y=sqrt(pow((N[i].get_square().co.y-m.co.y),2));  
				co_x=N[i].get_square().co.x;
				co_y=N[i].get_square().co.y;                                                                        
			}
		}
	}
}		
			
			
void Collector::pick_up(vector<Nourriture>& N) {
	bool end(false);
	for(size_t i(0); i<N.size(); ++i) {
		if(not(end)) {
			if(food_include_in_c(N[i].get_square(), m)) {
				set_food("LOADED");
				end=true;
				occupation_str(N[i].get_square(),"null");
				swap(N[i], N.back());
				N.pop_back();
			}
		}
	}
}


void Collector::move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
								Square f, vector<Square> preys, bool libre, bool& klan) {   
	if(food=="EMPTY") {
		next_move(N,f);
	} else {                                                                                   
		come_back(m,f,1);                                                                       
	}
	if(food=="EMPTY") {
		pick_up(N);
	}
}


void Generator::abs_superposition_g() {
	array<int,4> tabb;
	tabb = validation_superposition(m);
	if(tabb[3]) {
		cout << message::generator_overlap(m.co.x, m.co.y, tabb[0], tabb[1]);
		set_reinit();
	}
}


void Generator::g_include_in_f(Square carre_F, size_t dim) {                          
	if(not(carre_inclus(m, carre_F))) {
		cout << message::generator_not_within_home(m.co.x, m.co.y, dim-1);
		set_reinit();
	}
}


void Generator::se_dessiner(array<double,6> couleur_F) {
	dessiner_square(m, "Uniforme", couleur_F);
}


bool Generator::au_coin(int x, int y, int z, int t, bool& change) {
	if((x==1) and (t==1)) {								
		if(find_space_big_diago(m.co.x-1, m.co.y+1)) {
			liberation(m);
			m.co.x-=1;
			m.co.y+=1;
			occupation(m);
			change=true;
		} else {
			return true;
		}
	} else if((x==1) and (y==1)) {						
		if(find_space_big_diago(m.co.x-1, m.co.y-1)) {
			liberation(m);
			m.co.x-=1;
			m.co.y-=1;	
			occupation(m);	
			change=true;	
		} else {
			return true;
		}
	} else if((z==1) and (t==1)) {						
		if(find_space_big_diago(m.co.x+1, m.co.y+1)) {
			liberation(m);
			m.co.x+=1;
			m.co.y+=1;	
			occupation(m);
			change=true;		
		} else {
			return true;
		}		
	} else if((z==1) and (y==1)) {						
		if(find_space_big_diago(m.co.x+1, m.co.y-1)) {
			liberation(m);
			m.co.x+=1;
			m.co.y-=1;	
			occupation(m);
			change=true;		
		} else {
			return true;
		}
	}		
	return false;
}


bool Generator::au_bord(int x, int y, int z, int t, bool& change) {
	if((x<y) and (x<z) and (x<t) and (x==1)) {        
		if(find_space_big(m.co.x-1, m.co.y)) {
			liberation(m);
			m.co.x-=1;	
			occupation(m);	
			change=true;	
		} else {
			return true;
		}
	} else if((y<x) and (y<z) and (y<t) and (y==1)) {  
		if(find_space_big(m.co.x, m.co.y-1)) {
			liberation(m);
			m.co.y-=1;	
			occupation(m);
			change=true;		
		} else {
			return true;
		}		
	} else if((z<x) and (z<y) and (z<t) and (z==1)) {  
		if(find_space_big(m.co.x+1, m.co.y)) {
			liberation(m);
			m.co.x+=1;
			occupation(m);
			change=true;			
		} else {
			return true;
		}		
	} else if((t<x) and (t<y) and (z<t) and (t==1)) {  
		if(find_space_big(m.co.x, m.co.y+1)) {
			liberation(m);
			m.co.y+=1;
			occupation(m);	
			change=true;		
		} else {
			return true;
		}		
	}
	return false;	
}


void Generator::move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
								Square f, vector<Square> preys, bool libre, bool& klan) { 
	bool change(false);
	int x(f.co.x+f.side-1-(m.co.x+1)), y(f.co.y+f.side-1-(m.co.y+1));
	int z(m.co.x-(f.co.x+1)), t(m.co.y-(f.co.y+1));
	if(au_coin(x,y,z,t,change)==true) {
		klan=true;
	} else if(au_bord(x,y,z,t,change)==true){
		klan=true;
	} else if((x<=0) or (y<=0) or (z<=0) or (t<=0)) {
		klan=true;
	}
	if(not(klan)) {
		if(not(change)) {
			if(find_space_big_diago(m.co.x-1,m.co.y-1)) {
				if(((m.co.x-1-2)>f.co.x) and (m.co.y-1-2)>f.co.y) {
					liberation(m);
					m.co.x-=1;                                                
					m.co.y-=1;
					occupation(m);	
				}
			}	
			if(find_space_big(m.co.x,m.co.y-1)) {
				if(((m.co.x-2)==f.co.x+1) and ((m.co.y-1-2)>f.co.y)) {
					liberation(m);
					m.co.y-=1;
					occupation(m);	
				}
			}
			if(find_space_big(m.co.x-1,m.co.y)) {
				if(((m.co.x-1-2)>f.co.x) and (m.co.y-2)==f.co.y+1) {
					liberation(m);
					m.co.x-=1;         
					occupation(m);	
				}
			}	
		}
	}
	occupation(m); 
}


void Defensor::abs_superposition_d() {
	array<int,4> tabb;
	tabb=validation_superposition(m);
	if(tabb[3]) {
		cout << message::defensor_overlap(m.co.x, m.co.y, tabb[0], tabb[1]);
		set_reinit();
	}
}


void Defensor::d_include_in_f(Square carre_F, size_t dim) {                            
	if(not(carre_inclus(m, carre_F))) {
		cout << message::defensor_not_within_home(m.co.x, m.co.y, dim-1);
		set_reinit();
	}
}


void Defensor::se_dessiner(array<double,6> couleur_F) {
	dessiner_square(m, "Grille", couleur_F);
}


void Defensor::move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
								Square f, vector<Square> preys, bool libre, bool& klan) { 
	int x(0), y(0), z(0), t(0);
	x=f.co.x+f.side-1-(m.co.x+1);
	y=f.co.y+f.side-1-(m.co.y+1);
	z=m.co.x-(f.co.x+1);
	t=m.co.y-(f.co.y+1);
	if((x==y) and (y==z) and (z==t)) {
		if(find_space_med1(m.co.x, m.co.y+1)) {
			liberation(m);
			m.co.y+=1;
			occupation(m);
		}
	} else if((x<y) and (x<z) and (x<t) and (x>=0)) {
		grad_x(x);
	} else if((y<x) and (y<z) and (y<t) and (y>=0)) {
		grad_y(y);
	} else if((z<x) and (z<y) and (z<t) and (z>=0)) {
		grad_z(z);
	} else if((t<x) and (t<y) and (t<z) and (t>=0)) {
		grad_t(t);
	} else if((z==t) and (x==y) and (x>1) and (y>1) and (z>1) and (t>1)) {
		if(z<x) grad_z(z);
		else grad_x(x);
	} else if((z==y) and (x==t) and (x>1) and (y>1) and (z>1) and (t>1)) {
		if(z<t) grad_z(z);
		else grad_x(x);
	} else if((x<0) or (y<0) or (z<0) or (t<0)) {
		end_of_life=true;
	} else if((x==0) and (t==0)) {   
		end_of_life=true;			
	} else if((x==0) and (y==0)) {	
		end_of_life=true;		
	} else if((z==0) and (y==0)) {	
		end_of_life=true;			
	} else if((z==0) and (t==0)) {   
		end_of_life=true;
	}
}


void Defensor::grad_x(int x) {
	if ((x-1>0) and (x!=0)) {
		if(find_space_med1(m.co.x+1, m.co.y)==true) {
			liberation(m);
			m.co.x+=1;
			occupation(m);
		}
	} else if (not(find_space_med1(m.co.x-1, m.co.y)) and (x==0)) {      
		end_of_life=true;
	} else if ((find_space_med1(m.co.x-1, m.co.y)==true) and (x==0)) {   
		liberation(m);
		m.co.x-=1;
		occupation(m);
	} 
}


void Defensor::grad_y(int y) {
	if((y-1>0) and (y!=0)) {
		if(find_space_med1(m.co.x, m.co.y+1)){
			liberation(m);
			m.co.y+=1;
			occupation(m);
		}
	} else if (not(find_space_med1(m.co.x, m.co.y-1)) and (y==0)) {      
		end_of_life=true;
	} else if ((find_space_med1(m.co.x, m.co.y-1)) and (y==0)) {   
		liberation(m);
		m.co.y-=1;
		occupation(m);
	}
}


void Defensor::grad_z(int z) {
	if((z-1>0) and (z!=0)) {
		if(find_space_med1(m.co.x-1, m.co.y)==true) {
			liberation(m);
			m.co.x-=1;
			occupation(m);
		}
	} else if (not(find_space_med1(m.co.x+1, m.co.y)) and (z==0)) {      
		end_of_life=true;
	} else if ((find_space_med1(m.co.x+1, m.co.y)==true) and (z==0)) {   
		liberation(m);
		m.co.x+=1;
		occupation(m);
	}	
}


void Defensor::grad_t(int t){
	if((t-1>0) and (t!=0)) {
		if(find_space_med1(m.co.x, m.co.y-1)==true) {
			liberation(m);
			m.co.y-=1;
			occupation(m);
		}
	} else if (not(find_space_med1(m.co.x, m.co.y+1)) and (t==0)) {      
		end_of_life=true;
	} else if ((find_space_med1(m.co.x, m.co.y+1)==true) and (t==0)) {   
		liberation(m);
		m.co.y+=1;
		occupation(m);
	}	
}


void Predator::abs_superposition_p() {
	if(validation_superposition(m)[3]) {                              
		cout << message::predator_overlap(m.co.x, m.co.y);
		set_reinit();
	}
}


void Predator::se_dessiner(array<double,6> couleur_F) {
	dessiner_square(m, "Uniforme", couleur_F);
}


bool Predator::among(vector<Square> preys, Square f) {
	for(size_t i(0); i<preys.size(); ++i) {
		if(some_body(preys[i], f)) {
			return true;
		}
	}
	return false;
}


void Predator::appel_p1(Square f, vector<Square> preys, int a, int b,
								int c , int d , int e , int fr , int g, int h,vector<double>& delta) {
	if (not(some_body(m, f))) {
		Square w(f); 
		w.co.x+=(w.side/2); 
		w.co.y+=(w.side/2);												
		size_t p(find_min_id(my_path(w, a, b, c, d, e, fr, g, h)));
		if(p!=1000000) {
			vector<array<int, 2>> gg=target(w,a, b, c, d, e, fr, g, h);
			liberation(m);
			m.co.x=gg[p][0]; 
			m.co.y=gg[p][1];
			occupation(m);
		}
	} else {														                                 
		if(preys.size()!=0) {
			for(size_t i(0); i < preys.size(); ++i) {										      	 
				double d(euclide(m.co.x, m.co.y, preys[i].co.x, preys[i].co.y));
				delta.push_back(d);
			}
			size_t k(find_min_id(delta));														    
			size_t ok(find_min_id(my_path(preys[k], a, b, c, d, e, fr, g, h))); 				    
			if(ok!=1000000) {
				vector<array<int, 2>> gg=target(preys[k], a, b, c, d, e, fr, g, h);
				liberation(m);
				m.co.x=gg[ok][0]; 
				m.co.y=gg[ok][1];
				occupation(m);
			}
		}		
	}
}


void Predator::appel_p2(Square f, vector<Square> preys, int a, int b , 
							int c , int d , int e , int fr , int g, int h,vector<double>& delta) {
	if(preys.size()!=0) {											                               
		for(size_t i(0); i < preys.size(); ++i) {												     
			double d(euclide(m.co.x, m.co.y, preys[i].co.x, preys[i].co.y));
			delta.push_back(d);
		}					
		size_t k(find_min_id(delta));															
		size_t ok(find_min_id(my_path(preys[k], a, b, c, d, e, fr, g, h))); 					
		if(ok!=1000000) {
			vector<array<int, 2>> gg=target(preys[k], a, b, c, d, e, fr, g, h);
			liberation(m);
			m.co.x=gg[ok][0]; 
			m.co.y=gg[ok][1];
			occupation(m);
		}
	} else if((preys.size()==0) and (not(some_body(m, f))))	{	
		size_t p(find_min_id(my_path(f, a, b, c, d, e, fr, g, h)));
		if(p!=1000000) {
			vector<array<int, 2>> gg=target(f, a, b, c, d, e, fr, g, h);
			liberation(m);
			m.co.x=gg[p][0]; 
			m.co.y=gg[p][1];
			occupation(m);	
		}
	} else if(among(preys, f) and (not(some_body(m,f)))) {							
		size_t p(find_min_id(my_path(f, a, b, c, d, e, fr, g, h)));
		if(p!=1000000) {
			vector<array<int, 2>> gg=target(f, a, b, c, d, e, fr, g, h);
			liberation(m);			
			m.co.x=gg[p][0]; 
			m.co.y=gg[p][1];
			occupation(m);
		}	
	}
}


void Predator::move(vector<Nourriture>& N, vector<unique_ptr<Fourmis>>& F, 
								Square f, vector<Square> preys, bool libre, bool& klan) {
	int a(m.co.x+1), b(m.co.y+2), c(m.co.x+2), d(m.co.y+1);
	int e(m.co.y-1), fr(m.co.y-2), g(m.co.x-1), h(m.co.x-2);
	vector<double> delta;
	if(libre==true) {													                             
		appel_p1(f,preys,a,b,c,d,e,fr,g,h,delta);
	} else if(libre==false) {											                                	
		appel_p2(f,preys,a,b,c,d,e,fr,g,h,delta);
	}
}


void Predator::appel_path(Square p, int a, int b, vector<double>& grad_l,
						int c, int d, int e, int fr, int g, int h) {
	if(((a>0) and (a<g_max-1)) and ((b>0) and (b<g_max-1))) {
		double d1(euclide(a, b, p.co.x, p.co.y)); 
		if(find_space_small(a,b) or ((d1==1) or d1==sqrt(2))) {
			grad_l.push_back(d1);
		}
	}
	if(((c>0) and (c<g_max-1)) and ((d>0) and (d<g_max-1))) {
		double d2(euclide(c, d, p.co.x, p.co.y)); 
		if(find_space_small(c,d) or ((d2==1) or d2==sqrt(2))) {
			grad_l.push_back(d2);
		}
	}
	if(((c>0) and (c<g_max-1)) and ((e>0) and (e<g_max-1))) {
		double d3(euclide(c, e, p.co.x, p.co.y)); 
		if(find_space_small(c,e) or ((d3==1) or d3==sqrt(2))) {
			grad_l.push_back(d3);
		}
	}
	if(((a>0) and (a<g_max-1)) and ((fr>0) and (fr<g_max-1))) {
		double d4(euclide(a, fr, p.co.x, p.co.y)); 
		if(find_space_small(a,fr) or ((d4==1) or d4==sqrt(2))) {
			grad_l.push_back(d4);
		}
	}
	if(((g>0) and (g<g_max-1)) and ((b>0) and (b<g_max-1))) {
		double d5(euclide(g, b, p.co.x, p.co.y)); 
		if(find_space_small(g,b) or ((d5==1) or d5==sqrt(2))) {
			grad_l.push_back(d5);
		}
	}
	if(((h>0) and (h<g_max-1)) and ((d>0) and (d<g_max-1))) {
		double d6(euclide(h, d, p.co.x, p.co.y)); 
		if(find_space_small(h,d) or ((d6==1) or d6==sqrt(2))) {
			grad_l.push_back(d6);
		}
	}
}


vector<double> Predator::my_path(Square p, int a, int b,
												int c, int d, int e, int fr, int g, int h) {
	vector<double> grad_l;	
	appel_path(p,a,b,grad_l,c,d,e,fr,g,h);
	if(((h>0) and (h<g_max-1)) and ((e>0) and (e<g_max-1))) {
		double d7(euclide(h, e, p.co.x, p.co.y)); 
		if(find_space_small(h,e) or ((d7==1) or d7==sqrt(2))) {
			grad_l.push_back(d7);
		}
	}
	if(((g>0) and (g<g_max-1)) and ((fr>0) and (fr<g_max-1))) {
		double d8(euclide(g, fr, p.co.x, p.co.y)); 
		if(find_space_small(g,fr) or ((d8==1) or d8==sqrt(2))) {
			grad_l.push_back(d8);
		}
	}
	return grad_l;	
}


void Predator::appel_target(Square p, int a, int b, vector<array<int, 2>>& grad,
						int c, int d, int e, int fr, int g, int h) {
	if(((a>0) and (a<g_max-1)) and ((b>0) and (b<g_max-1))) {
		double d1(euclide(a, b, p.co.x, p.co.y)); 
		if(find_space_small(a,b) or ((d1==1) or d1==sqrt(2))) {
			array<int, 2> d11={a,b}; 
			grad.push_back(d11);
		}
	}
	if(((c>0) and (c<g_max-1)) and ((d>0) and (d<g_max-1))) {
		double d2(euclide(c, d, p.co.x, p.co.y)); 
		if(find_space_small(c,d) or ((d2==1) or d2==sqrt(2))) {
			array<int, 2> d22={c,d}; 
			grad.push_back(d22);
		}
	}
	if(((c>0) and (c<g_max-1)) and ((e>0) and (e<g_max-1))) {
		double d3(euclide(c, e, p.co.x, p.co.y)); 
		if(find_space_small(c,e) or ((d3==1) or d3==sqrt(2))) {
			array<int, 2> d33={c,e}; 
			grad.push_back(d33);
		}
	}
	if(((a>0) and (a<g_max-1)) and ((fr>0) and (fr<g_max-1))) {
		double d4(euclide(a, fr, p.co.x, p.co.y)); 
		if(find_space_small(a,fr) or ((d4==1) or d4==sqrt(2))) {
			array<int, 2> d44={a,fr}; 
			grad.push_back(d44);
		}
	}
	if(((g>0) and (g<g_max-1)) and ((b>0) and (b<g_max-1))) {
		double d5(euclide(g, b, p.co.x, p.co.y)); 
		if(find_space_small(g,b) or ((d5==1) or d5==sqrt(2))) {
			array<int, 2> d55={g,b}; 
			grad.push_back(d55);
		}
	}					
}


vector<array<int, 2>> Predator::target(Square p, int a, int b, 
					int c, int d, int e, int fr, int g, int h) {
	vector<array<int, 2>> grad;	
	appel_target(p,a,b,grad,c,d,e,fr,g,h);
	if(((h>0) and (h<g_max-1)) and ((d>0) and (d<g_max-1))) {
		double d6(euclide(h, d, p.co.x, p.co.y)); 
		if(find_space_small(h,d) or ((d6==1) or d6==sqrt(2))) {
			array<int, 2> d66={h,d}; grad.push_back(d66);
		}
	}
	if(((h>0) and (h<g_max-1)) and ((e>0) and (e<g_max-1))) {
		double d7(euclide(h, e, p.co.x, p.co.y)); 
		if(find_space_small(h,e) or ((d7==1) or d7==sqrt(2))) {
			array<int, 2> d77={h,e}; grad.push_back(d77);
		}
	}
	if(((g>0) and (g<g_max-1)) and ((fr>0) and (fr<g_max-1))) {
		double d8(euclide(g, fr, p.co.x, p.co.y)); 
		if(find_space_small(g,fr) or ((d8==1) or d8==sqrt(2))) {
			array<int, 2> d88={g,fr}; grad.push_back(d88);
		}
	}
	return grad;	
}











