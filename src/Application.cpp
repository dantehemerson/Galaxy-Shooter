#include "Application.hpp"

#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_physfs.h>
#include <physfs.h>
#include <iostream>

using namespace std;

#include "R.hpp"
#include "AllegroException.hpp"
#include "Gallery.hpp"
#include "Menu.hpp"
#include "Peripheral.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "About.hpp"
#include "Help.hpp"
#include "Options.hpp"
#include "HighScores.hpp"
#include "Game.hpp"
#include "Sound.hpp"

Application::Application() :
display(nullptr),
eventQueue(nullptr),
timer(nullptr),
actualInterface(nullptr),
exit(false) {
}

void Application::init(int argc, char** argv) {

	if (!al_init()) {
		throw AllegroException(R::String::ERROR_ALLEGRO_INIT);
	}

	al_init_image_addon();
	al_init_font_addon();
	al_init_acodec_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	if (!al_install_keyboard()) {
		throw AllegroException(R::String::ERROR_INSTALL_KEYBOARD);
	}
	if (!al_install_mouse()) {
		throw AllegroException(R::String::ERROR_INSTALL_MOUSE);
	}
	if (!al_install_audio()) {
		throw AllegroException(R::String::ERROR_INSTALL_AUDIO);
	}
	else {
		al_reserve_samples(16);
	}

	display = al_create_display(R::Dimen::WIDTH, R::Dimen::HEIGHT);
	al_set_window_title(display, R::String::WINDOW_TITLE.c_str());

	timer = al_create_timer(1.0 / R::Constant::FPS);

	eventQueue = al_create_event_queue();

	/// Registra los eventos de los perifericos para que puedan ser escuchados.
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());

	// Cargando los recursos
	Gallery& gallery = Gallery::getSingleton();
	gallery.loadResources();


	keyboard = new Keyboard;
	mouse = new Mouse;

	menu = new Menu(this);
	about = new About(this);
	help = new Help(this);
	options = new Options(this);
	highScores = new HighScores(this);

	game = new Game(this);

	srand(static_cast<unsigned int>(time(NULL)));
	al_start_timer(timer);
}

void Application::loop() {
	actualInterface = menu;
	while (!exit && event.type != ALLEGRO_EVENT_DISPLAY_CLOSE) {
		al_wait_for_event(eventQueue, &event);
		keyboard->poll();
		mouse->poll();
		if (event.type == ALLEGRO_EVENT_TIMER) {
			actualInterface->draw();
			actualInterface->update();
			al_flip_display();

		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT) {
			game->setPause(true);
		}
	}
}

void Application::setInterface(INTERFACE_SCREEN interfaceApp, bool reinit) {
	switch (interfaceApp) {
	case INTERFACE_SCREEN::MAIN_MENU:
		actualInterface = menu;
		break;
	case INTERFACE_SCREEN::ABOUT:
		actualInterface = about;
		break;
	case INTERFACE_SCREEN::HELP:
		actualInterface = help;
		break;
	case INTERFACE_SCREEN::OPTIONS:
		actualInterface = options;
		break;
	case INTERFACE_SCREEN::HIGHSCORES:
		actualInterface = highScores;
		break;
	case INTERFACE_SCREEN::GAME:
		actualInterface = game;
		game->reinit();
		break;
	}
}

void Application::quit() {
	exit = true;
}

Keyboard* Application::getKeyboard() const {
	return keyboard;
}

Mouse* Application::getMouse() const {
	return mouse;
}

ALLEGRO_DISPLAY* Application::getDisplay() const {
	return display;
}

Application::~Application() {
	delete menu;
	delete about;
	delete help;
	delete options;
	delete highScores;
	delete game;
	al_destroy_display(display);
	al_destroy_event_queue(eventQueue);
	al_destroy_timer(timer);
}
