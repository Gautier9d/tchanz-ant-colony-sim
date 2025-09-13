#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <gtkmm.h>
#include "simulation.h"
#include "graphic.h"
using namespace std;


struct Image {                  
	double xMin;                
	double xMax;
	double yMin;
	double yMax;
	double asp;                
	int height;                 
	int width;                 
	double get_min_xy();
};


class MyArea : public Gtk::DrawingArea {
public:
	MyArea();
	virtual ~MyArea();
	void setFrame(Image x); 
	void adjustFrame();
	void set_le_bool(bool a) { le_bool = a;}
	bool get_le_bool() {return le_bool;}
private:
	Image frame;
protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
	bool le_bool = true;      
};


class MyEvent : public Gtk::Window {
public:
	MyEvent();
	virtual ~MyEvent();
	void set_test_simu() {test_simu=true;}
	static bool get_gui_exist() {return gui_exist;}
	static void set_gui_exist(bool a) {gui_exist=a;}
	bool get_static_bool();
	void set_bool(bool c) {area.set_le_bool(c);}
	void set_test_simu(bool a) {test_simu=a;}
	MyArea& get_area() { return area;}
	void set_label();
	void set_first_label();
protected:
	void on_button_clicked_Exit();
	void appel_1_open(bool& tt);
	void appel_2_open();
	void appel_3_open();
	void appel_4_open(bool& ttt);
	void on_button_clicked_Open();
	void on_button_clicked_Save();
	void on_button_clicked_Start();
	void on_button_clicked_Step();
	void on_button_clicked_Previous();
	void on_button_clicked_Next();
	Gtk::Box m_Box_Main, m_Box1, m_Box2, m_Box3, m_Box4;
	Gtk::Separator m_Separator1;
	Gtk::Separator m_Separator2;
	Gtk::Separator m_Separator3;
	Gtk::Frame  m_Frame_General, m_Frame_Info, m_Frame_Fourmiliere;
	Gtk::Label m_Label_nbFood, m_Label_infoFourm;
	Gtk::Button m_Button_Exit;
	Gtk::Button m_Button_Open;
	Gtk::Button m_Button_Save;
	Gtk::Button m_Button_Start;
	Gtk::Button m_Button_Step;
	Gtk::Button m_Button_Previous;
	Gtk::Button m_Button_Next;
	bool on_timeout();
	bool timer_added;
	bool disconnect;
	const int timeout_value;
	bool on_key_press_event(GdkEventKey * key_event);
	MyArea area;
	int indice;
	bool test_simu=false;
	bool verif_reinit=false;
	bool test1=false;
	bool second=false;
	static bool gui_exist;

};


void reset_simul(); 


void ouvrir(MyEvent&g, char* nom_fichier);


void occupation_tot();

#endif
