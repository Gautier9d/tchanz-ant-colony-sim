#include <iostream> 
#include <fstream>
#include <string>
#include "simulation.h"
#include "gui.h"
using namespace std;


int main(int argc, char* argv[]) {
	auto app=Gtk::Application::create();
	MyEvent event;
	if(argc==2) {
		ouvrir(event, argv[1]);
	}	
	event.set_default_size(500,500);
	event.set_title("Interface utilisateur");
	return app->run(event); 
}
