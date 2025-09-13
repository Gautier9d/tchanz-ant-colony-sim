//340423:60%  340933:40%
#include <iostream>
#include <string>
#include "gui.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;


static Simulation simul; 


bool MyEvent::gui_exist=false;


static Image default_frame = {-250, 250, -250, 250, 1, 500, 500}; 


static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, Image frame) {
	cr->translate(frame.width/2, frame.height/2);
	cr->scale(frame.width/(frame.xMax - frame.xMin), 
			-frame.height/(frame.yMax - frame.yMin));
	cr->translate(frame.get_min_xy(), frame.get_min_xy());
}


double Image:: get_min_xy() {
	if (xMin >= yMin) {
		return xMin; 
	} else {
		return yMin;
	}
}


MyArea::MyArea() {
	setFrame(default_frame);
}


MyArea::~MyArea() {
}


void MyArea::setFrame(Image f) {
	if((f.xMin <= f.xMax) and (f.yMin <= f.yMax) and (f.height > 0)) {
		f.asp=f.width/f.height;
		frame=f;
	} else {
		std::cout << "incorrect Model framing or window parameters" << std::endl;
	}
} 


void MyArea::adjustFrame() {
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();
	frame.width =width;
	frame.height=height;
    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > default_frame.asp) {                                           
	    frame.yMax=default_frame.yMax ;
	    frame.yMin=default_frame.yMin ;	
	    double delta(default_frame.xMax - default_frame.xMin);
	    double mid((default_frame.xMax + default_frame.xMin)/2);
	    frame.xMax=mid + 0.5*(new_aspect_ratio/default_frame.asp)*delta ;
	    frame.xMin=mid - 0.5*(new_aspect_ratio/default_frame.asp)*delta ;		  	  
    } else {                                                                               
	    frame.xMax=default_frame.xMax ;
	    frame.xMin=default_frame.xMin ;
 	    double delta(default_frame.yMax - default_frame.yMin);
	    double mid((default_frame.yMax + default_frame.yMin)/2);
	    frame.yMax=mid + 0.5*(default_frame.asp/new_aspect_ratio)*delta ;
	    frame.yMin=mid - 0.5*(default_frame.asp/new_aspect_ratio)*delta ;		  	  
    }
}


bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	if(le_bool) {
		graphic_set_context(cr);
		cr->set_source_rgb(0.,0.,0.);
		cr-> paint(); 
		adjustFrame();
		orthographic_projection(cr, frame); 
		draw_grid(cr);
	} else {
		graphic_set_context(cr);
		cr->set_source_rgb(0.,0.,0.);
		cr-> paint(); 
		adjustFrame();
		orthographic_projection(cr, frame); 
		draw_grid(cr);
		simul.dessiner();
	}
	return true;
}


MyEvent::MyEvent() :
	m_Box_Main(Gtk::ORIENTATION_HORIZONTAL, 3),
	m_Box1(Gtk::ORIENTATION_VERTICAL, 3),
	m_Box2(Gtk::ORIENTATION_VERTICAL, 3),
	m_Box3(Gtk::ORIENTATION_VERTICAL, 3),
	m_Box4(Gtk::ORIENTATION_VERTICAL, 3),
	m_Frame_General("General"),
	m_Frame_Info("Info"),
	m_Frame_Fourmiliere("Fourmiliere"),
	m_Label_nbFood("nb food : 0"), 
	m_Label_infoFourm("None selected"),
	m_Button_Exit("exit"),
	m_Button_Open("open"),
	m_Button_Save("save"),
	m_Button_Start("start"),
	m_Button_Step("step"),
	m_Button_Previous("previous"),
	m_Button_Next("next"),
	timer_added(false),
	disconnect(false),
	timeout_value(10)
	{
	indice=-1;
	set_title("Interface utilisateur");
	set_border_width(5);
	add(m_Box_Main);
	area.set_size_request(500,500);
	m_Box_Main.pack_start(m_Box1,Gtk::PACK_SHRINK);
	m_Box1.pack_start(m_Frame_General, Gtk::PACK_SHRINK);
	m_Frame_General.add(m_Box2);
	m_Box2.pack_start(m_Button_Exit, false, false);
	m_Box2.pack_start(m_Button_Open, false, false);
	m_Box2.pack_start(m_Button_Save, false, false);
	m_Box2.pack_start(m_Button_Start, false, false);
	m_Box2.pack_start(m_Button_Step, false, false);
	m_Box1.pack_start(m_Box3, false, false);
	m_Box3.pack_start(m_Frame_Info, Gtk::PACK_SHRINK);
	m_Frame_Info.add(m_Label_nbFood);
	m_Box1.pack_start(m_Frame_Fourmiliere, Gtk::PACK_SHRINK);
	m_Frame_Fourmiliere.add(m_Box4);
	m_Box_Main.pack_start(area);
	m_Box4.set_border_width(5);
	m_Box3.set_border_width(5);
	m_Box2.set_border_width(5);
	m_Box1.set_border_width(5);
	m_Box4.pack_start(m_Button_Previous, false, false);
	m_Box4.pack_start(m_Button_Next, false, false);
	m_Box4.pack_start(m_Label_infoFourm);
	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this,
			  &MyEvent::on_button_clicked_Exit) ); 
	m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this,
			  &MyEvent::on_button_clicked_Open) );
	m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this,
			  &MyEvent::on_button_clicked_Save) );
	m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this,
			  &MyEvent::on_button_clicked_Start) );
	m_Button_Step.signal_clicked().connect(sigc::mem_fun(*this,
			  &MyEvent::on_button_clicked_Step) );
	m_Button_Previous.signal_clicked().connect(sigc::mem_fun(*this,
			  &MyEvent::on_button_clicked_Previous) );
	m_Button_Next.signal_clicked().connect(sigc::mem_fun(*this,
			  &MyEvent::on_button_clicked_Next) );
	show_all_children();
}


MyEvent::~MyEvent() {
}


void MyEvent::on_button_clicked_Exit() {
	hide();
}


void MyEvent::appel_1_open(bool &tt) {
	if(m_Button_Start.get_label()=="stop") { 
		m_Button_Start.set_label("start");
		tt = true;
		if(not timer_added) {
			std::cout << "Sorry, there is no active timer at the moment." << std::endl;
		} else {
			std::cout << "manually disconnecting the timer " << std::endl;
			disconnect=true;   
			timer_added=false;
		}
	}
}


void MyEvent::appel_2_open() {
	if(not(get_gui_exist())){
		reset_simul();
		area.set_le_bool(true);
		area.queue_draw();
		area.set_le_bool(false);
		area.queue_draw();
	} else {
		set_gui_exist(false);
	}
}


void MyEvent::appel_3_open() {
	if(simul.get_test_simul_is()){
		m_Label_nbFood.set_text("nb food : " + to_string(0));
		reset_simul();
		area.set_le_bool(true);
		area.queue_draw();
		test_simu=false; 
	} else {
		area.set_le_bool(false);
		area.queue_draw();
	}
}	


void MyEvent::appel_4_open(bool &ttt) {
	if((m_Button_Start.get_label()=="start") and (ttt==true)) {
		m_Button_Start.set_label("stop");
		if(not timer_added){	  
			Glib::signal_timeout().connect( sigc::mem_fun(*this, &MyEvent::on_timeout),
				timeout_value );
			timer_added=true;
			std::cout << "Timer added" << std::endl;
		} else { 
			std::cout << "The timer already exists : nothing more is created" << std::endl;
		}
	}
}


void MyEvent::on_button_clicked_Open() {	  
	bool ttest(false);
	appel_1_open(ttest);
	Gtk::FileChooserDialog dialog("Please choose a file",
		Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	int result = dialog.run();
	switch(result) {
		case(Gtk::RESPONSE_OK): {	
			std::string filename = dialog.get_filename();
			test_simu=true; 
			appel_2_open();
			simul.lecture_de_fichier(&filename[0]);
			m_Label_nbFood.set_text("nb food : " + to_string(simul.get_nb_food()));
			m_Label_infoFourm.set_text("None selected");
			indice=-1;
			appel_3_open();
			break;
		}
		case(Gtk::RESPONSE_CANCEL) : {
			appel_4_open(ttest);
			break;
		}
		default : {
		  std::cout << "Unexpected button clicked." << std::endl;
		  break;
		}
	}
}


void MyEvent::on_button_clicked_Save(){
	bool testt(false);
	appel_1_open(testt);
	Gtk::FileChooserDialog dialog("Please choose a file",
		Gtk::FILE_CHOOSER_ACTION_SAVE);
	dialog.set_transient_for(*this);
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);
	int result = dialog.run();
	switch(result) {
		case(Gtk::RESPONSE_OK) : {
			appel_4_open(testt);
			string filename;
			filename=dialog.get_filename();
			bool een(test_simu);
			simul.ecriture(filename, een);
			break;
		}
		case(Gtk::RESPONSE_CANCEL) : {
			appel_4_open(testt);
			break;
		}
		default : {
		  std::cout << "Unexpected button clicked." << std::endl;
		  break;
		}
	}
}


void MyEvent::on_button_clicked_Start() {
	if(m_Button_Start.get_label()=="start") {
		m_Button_Start.set_label("stop");
		if(not timer_added) {	  
			Glib::signal_timeout().connect( sigc::mem_fun(*this, &MyEvent::on_timeout),
				timeout_value );
			timer_added=true;
			std::cout << "Timer added" << std::endl;
		} else { 
			std::cout << "The timer already exists : nothing more is created" << std::endl;
		}
	} else if(m_Button_Start.get_label()=="stop") { 
		m_Button_Start.set_label("start");
		if(not timer_added) {
			std::cout << "Sorry, there is no active timer at the moment." << std::endl;
		} else {
			std::cout << "manually disconnecting the timer " << std::endl;
			disconnect=true;   
			timer_added=false;
		}
		on_button_clicked_Previous();
	}
}


void MyEvent::on_button_clicked_Step() {
	if(m_Button_Start.get_label()=="start") {
		if(not timer_added) {
			on_timeout();
		}	
	}
	occupation_tot();
}


void MyEvent::on_button_clicked_Previous() {
	if(not(simul.get_vect_F().size()==0)) {
		if(test_simu==true) {
			if(indice==-1) {
				indice=(simul.get_vect_F().size()-1);
				m_Label_infoFourm.set_text("id : " + to_string(indice) + "\nTotal food: " + 
					to_string(simul.get_vect_F()[indice].get_vect_fourmis()[0]->get_total_food()) 
					+ "\n" + "\nnbc: " + to_string(simul.get_vect_F()[indice].get_nbC()) + "\nnbd: "
					+ to_string(simul.get_vect_F()[indice].get_nbD()) + "\nnbp: " 
					+ to_string(simul.get_vect_F()[indice].get_nbP()) );
				second=true;
			} else {
				--indice;
				if(indice < 0){
					if(indice==-1) {
						m_Label_infoFourm.set_text("None selected");
					} else {
						indice=(simul.get_vect_F().size()-1);
						m_Label_infoFourm.set_text("id : " + to_string(indice) + "\nTotal food: " + 
							to_string(simul.get_vect_F()[indice].get_vect_fourmis()[0]->get_total_food())
							+ "\n" + "\nnbc: " + to_string(simul.get_vect_F()[indice].get_nbC()) + "\nnbd: " 
							+ to_string(simul.get_vect_F()[indice].get_nbD()) + "\nnbp: " 
							+ to_string(simul.get_vect_F()[indice].get_nbP()) );
					}
				} else {
					m_Label_infoFourm.set_text("id : " + to_string(indice) + "\nTotal food: " +
					to_string(simul.get_vect_F()[indice].get_vect_fourmis()[0]->get_total_food()) 
					+ "\n" + "\nnbc: " + to_string(simul.get_vect_F()[indice].get_nbC()) + "\nnbd: " 
					+ to_string(simul.get_vect_F()[indice].get_nbD()) + "\nnbp: " 
					+ to_string(simul.get_vect_F()[indice].get_nbP()) );
				}	
				second=true;		
			}
		}
	} else {
		m_Label_infoFourm.set_text("None selected");
		indice=-1;
	}
}


void MyEvent::on_button_clicked_Next() {
	if(not(simul.get_vect_F().size()==0)) {
		if(test_simu==true) {
			if(indice==-1) {
				++indice;
				m_Label_infoFourm.set_text("id : " + to_string(indice) + "\nTotal food: " + 
					to_string(simul.get_vect_F()[indice].get_vect_fourmis()[0]->get_total_food()) + "\n" + "\nnbc: " 
					+ to_string(simul.get_vect_F()[indice].get_nbC()) + "\nnbd: " 
					+ to_string(simul.get_vect_F()[indice].get_nbD()) + "\nnbp: " 
					+ to_string(simul.get_vect_F()[indice].get_nbP()) );
				second=true;
			} else {
				++indice;
				int id=indice;
				if(id < (int)simul.get_vect_F().size()) {
					m_Label_infoFourm.set_text("id : " + to_string(indice) + "\nTotal food: " + 
						to_string(simul.get_vect_F()[indice].get_vect_fourmis()[0]->get_total_food()) + "\n" + "\nnbc: " 
						+ to_string(simul.get_vect_F()[indice].get_nbC()) + "\nnbd: " 
						+ to_string(simul.get_vect_F()[indice].get_nbD()) + "\nnbp: " 
						+ to_string(simul.get_vect_F()[indice].get_nbP()) );
				} else {
					m_Label_infoFourm.set_text("None selected");
					indice=-1;
				}
			}
		}
	} else {
		m_Label_infoFourm.set_text("None selected");
		indice=-1;
	}
}


bool MyEvent::on_timeout() {
	MyEvent::on_button_clicked_Next();
	static unsigned int val(1);
	if(disconnect)  {
		disconnect=false; 
	    return false; 
	}
	simul.execution(simul.get_vect_F(), simul.get_vect_N());
	std::cout << "This is simulation update number : " << val << std::endl;
	++val;
	MyEvent::set_label();
	area.queue_draw();
	MyEvent::on_button_clicked_Previous();
	return true; 
}


bool MyEvent::on_key_press_event(GdkEventKey * key_event) {
	if(key_event->type==GDK_KEY_PRESS) {
		switch(gdk_keyval_to_unicode(key_event->keyval)) {
			case 's': {
				on_button_clicked_Start();
				return true;
			}
			case '1': {
				on_button_clicked_Step();
				return true;
			}	
			case 'n' : {
				on_button_clicked_Next();
				return true;
			}					
			case 'p': {
				on_button_clicked_Previous();
				return true;
			}
			case 'q' : {
				on_button_clicked_Exit();
				return true;
			}
		}
	}
	return Gtk::Window::on_key_press_event(key_event);
}


bool MyEvent::get_static_bool() { 
	return simul.get_test_simul_is();
}


void MyEvent::set_label() {
	if(simul.get_vect_F().size()==0) {
		m_Label_nbFood.set_text("nb food : " + to_string(simul.get_nb_food()));
		m_Label_infoFourm.set_text("None selected");
	} else {
		if(not(indice<0)) {
			m_Label_nbFood.set_text("nb food : " + to_string(simul.get_vect_N().size()));
			m_Label_infoFourm.set_text("id : " + to_string(indice) + "\nTotal food: " + 
						to_string(simul.get_vect_F()[indice].get_vect_fourmis()[0]->get_total_food()) + "\n" + "\nnbc: " 
						+ to_string(simul.get_vect_F()[indice].get_nbC()) + "\nnbd: " 
						+ to_string(simul.get_vect_F()[indice].get_nbD()) + "\nnbp: " 
						+ to_string(simul.get_vect_F()[indice].get_nbP()));
		} 
	}
}


void MyEvent::set_first_label() {
	m_Label_nbFood.set_text("nb food : " + to_string(simul.get_nb_food()));
	m_Label_infoFourm.set_text("None selected");
}


void ouvrir(MyEvent& g, char* nom_fichier) {
	g.set_test_simu(true); 
	simul.lecture_de_fichier(nom_fichier);
	MyEvent::set_gui_exist(false);
	if(simul.get_test_simul_is()) {
		reset_simul();
		g.get_area().set_le_bool(true);
		g.get_area().queue_draw();
		g.set_test_simu(false); 
	} else {
		g.get_area().set_le_bool(false);
		g.set_first_label();
		g.get_area().queue_draw();
	}
}


void reset_simul() {
	simul.reset();
}


void occupation_tot() {
	for(size_t i(0); i<simul.get_vect_F().size(); ++i) {
		for(size_t j(0); j<simul.get_vect_F()[i].get_vect_fourmis().size(); ++j) {
			occupation(simul.get_vect_F()[i].get_vect_fourmis()[j]->get_m());
		}
	}
}
	
