//340423 : 75% 340933 : 25%
#include <iostream>
#include "graphic.h"
#include <gtkmm.h>
using namespace std;


static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);


void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr) {
	ptcr = &cr;
}


void draw_grid(const Cairo::RefPtr<Cairo::Context>& cr) {
	cr->set_source_rgb(1., 1., 1.);
	cr->set_line_width(a);
	cr->rectangle(a/2., a/2., taille_totale - a, taille_totale - a);
	cr->stroke(); 
	cr->set_source_rgb(.5, .5, .5);
	cr->set_line_width(.5);
	for (double i(0); i<=taille_totale; i+=a) {
		cr->move_to(i,0);
		cr->line_to(i,taille_totale);
	} 
	for (double j(0); j<=taille_totale; j+=a){
		cr->move_to(0,j);
		cr->line_to(taille_totale,j);
	}
	cr->stroke();
}


void dessins_Uniforme(int x, int y, array<double,6> couleur, int taille) {
	if(taille==1) {
		(*ptcr)->set_line_width(a);
		(*ptcr)->set_source_rgb(couleur[0], couleur[1], couleur[2]);
		(*ptcr)->move_to((x*a + 0.5*a), (y*a));
		(*ptcr)->line_to((x*a + 0.5*a), (y*a + a));
		(*ptcr)->stroke();
	} else { 
		(*ptcr)->set_line_width(2.5*a);
		(*ptcr)->set_source_rgb(couleur[0], couleur[1], couleur[2]);
		(*ptcr)->move_to((x*a - 0.75*a), (y*a - 2*a ));
		(*ptcr)->line_to((x*a - 0.75*a), (y*a + 3*a ));
		(*ptcr)->move_to((x*a - 2*a), (y*a + 1.75*a ));
		(*ptcr)->line_to((x*a + 3*a), (y*a + 1.75*a));
		(*ptcr)->move_to((x*a + 1.75*a), (y*a + 3*a));
		(*ptcr)->line_to((x*a + 1.75*a), (y*a - 2*a));
		(*ptcr)->move_to((x*a + 3*a), (y*a - 0.75*a));
		(*ptcr)->line_to((x*a - 2*a), (y*a - 0.75*a));
		(*ptcr)->stroke();
	}
}


void dessins_Diagonale(int x, int y, array<double,6> couleur) {
	(*ptcr)->set_line_width(a);
	(*ptcr)->set_source_rgb(couleur[0], couleur[1], couleur[2]);
	(*ptcr)->move_to((x*a + 0.5*a), (y*a));
	(*ptcr)->line_to((x*a + 0.5*a), (y*a + a));
	(*ptcr)->move_to((x*a - 0.5*a), (y*a + a));
	(*ptcr)->line_to((x*a - 0.5*a), (y*a + 2*a));
	(*ptcr)->move_to((x*a - 0.5*a), (y*a));
	(*ptcr)->line_to((x*a - 0.5*a), (y*a - a));
	(*ptcr)->move_to((x*a + 1.5*a), (y*a + a));
	(*ptcr)->line_to((x*a + 1.5*a), (y*a + 2*a));
	(*ptcr)->move_to((x*a + 1.5*a), (y*a));
	(*ptcr)->line_to((x*a + 1.5*a), (y*a - a));
	(*ptcr)->stroke();
	//----------
	(*ptcr)->set_source_rgb(couleur[3], couleur[4], couleur[5]);
	(*ptcr)->move_to((x*a + 0.5*a), (y*a + a));
	(*ptcr)->line_to((x*a + 0.5*a), (y*a + 2*a));
	(*ptcr)->move_to((x*a + 0.5*a), (y*a));
	(*ptcr)->line_to((x*a + 0.5*a), (y*a - a));
	(*ptcr)->move_to((x*a - 0.5*a), (y*a));
	(*ptcr)->line_to((x*a - 0.5*a), (y*a + a));
	(*ptcr)->move_to((x*a + 1.5*a), (y*a));
	(*ptcr)->line_to((x*a + 1.5*a), (y*a + a));
	(*ptcr)->stroke();
}


void dessins_Grille(int x, int y, array<double,6> couleur) {
	(*ptcr)->set_line_width(a);
	(*ptcr)->set_source_rgb(couleur[0], couleur[1], couleur[2]);
	(*ptcr)->move_to((x*a + 0.5*a), (y*a - a));
	(*ptcr)->line_to((x*a + 0.5*a), (y*a + 2*a));
	(*ptcr)->move_to((x*a - a), (y*a + 0.5*a));
	(*ptcr)->line_to((x*a + 2*a), (y*a + 0.5*a));
	(*ptcr)->stroke();
	//----------
	(*ptcr)->set_source_rgb(couleur[3], couleur[4], couleur[5]);
	(*ptcr)->move_to((x*a - 0.5*a), (y*a + a));
	(*ptcr)->line_to((x*a - 0.5*a), (y*a + 2*a));
	(*ptcr)->move_to((x*a - 0.5*a), (y*a));
	(*ptcr)->line_to((x*a - 0.5*a), (y*a - a));
	(*ptcr)->move_to((x*a + 1.5*a), (y*a + a));
	(*ptcr)->line_to((x*a + 1.5*a), (y*a + 2*a));
	(*ptcr)->move_to((x*a + 1.5*a), (y*a));
	(*ptcr)->line_to((x*a + 1.5*a), (y*a - a));
	(*ptcr)->stroke();
}


void dessins_Losange(int x, int y, array<double,6> couleur) {
	(*ptcr)->set_line_width(a/sqrt(2));
	(*ptcr)->set_source_rgb(couleur[0], couleur[1], couleur[2]);
	(*ptcr)->move_to((x*a + 0.25*a), (y*a + 0.25*a));
	(*ptcr)->line_to((x*a + 0.75*a), (y*a + 0.75*a));
	(*ptcr)->stroke();
}


void dessins_Vide(int x, int y, int side, array<double,6> couleur) {
	(*ptcr)->set_line_width(0.5*a);
	(*ptcr)->set_source_rgb(couleur[0], couleur[1], couleur[2]);
	(*ptcr)->move_to((x*a+(a/2)), (y*a+(a/2)));
	(*ptcr)->line_to((x*a+(a/2)), (y*a + side*a-(a/2)));
	(*ptcr)->move_to((x*a+(a/2)), (y*a + side*a-(a/2)));
	(*ptcr)->line_to((x*a + side*a-(a/2)), (y*a + side*a-(a/2)));
	(*ptcr)->move_to((x*a + side*a-(a/2)), (y*a + side*a-(a/2)));
	(*ptcr)->line_to((x*a + side*a-(a/2)), (y*a+(a/2)));
	(*ptcr)->move_to((x*a + side*a-(a/2)), (y*a+(a/2)));
	(*ptcr)->line_to((x*a+(a/2)), (y*a+(a/2)));
	(*ptcr)->stroke();
}

