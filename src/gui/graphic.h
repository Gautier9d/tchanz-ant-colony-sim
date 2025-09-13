#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <iostream>
#include <gtkmm.h>
#include <array>
using namespace std;


constexpr unsigned taille_totale(500);


constexpr double a(taille_totale/128.);


void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);


void draw_grid(const Cairo::RefPtr<Cairo::Context>& cr);


void dessins_Uniforme(int x, int y, array<double,6> couleur, int taille);


void dessins_Diagonale(int x, int y, array<double,6> couleur);


void dessins_Grille(int x, int y, array<double,6> couleur);


void dessins_Losange(int x, int y, array<double,6> couleur);


void dessins_Vide(int x, int y, int side, array<double,6> couleur);


#endif
