#include "Menu.hpp"

#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <iostream>

using namespace std;

#include "Gallery.hpp"
#include "Application.hpp"
#include "Button.hpp"
#include "ControlManager.hpp"
#include "ActorManager.hpp"
#include "StageManager.hpp"
#include "Control.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"
#include "Sound.hpp"
#include "Background.hpp"

Menu::Menu(Application*const app) : Interface(app),
controlManager(nullptr),
actorManager(nullptr),
stageManager(nullptr)
{

	int inity = 260;
	buttons.push_back(new Button(400, inity, R::String::PLAY_GAME));
	buttons.push_back(new Button(400, inity + 55, R::String::HIGHSCORES));
	buttons.push_back(new Button(400, inity + 110, R::String::OPTIONS));
	buttons.push_back(new Button(400, inity + 165, R::String::HELP));
	buttons.push_back(new Button(400, inity + 220, R::String::ABOUT));
	buttons.push_back(new Button(400, inity + 275, R::String::QUIT));

	controlManager = new ControlManager;
	actorManager = new ActorManager;
	stageManager = new StageManager(actorManager);

	Control* control = new Control;
	control->addActionName(ActionMenu::DOWN, "Bajar");
	control->addActionName(ActionMenu::UP, "Subir");
	control->addActionName(ActionMenu::ENTER, "Enter");
	control->addActionName(ActionMenu::MOUSE_MICKEY_LEFT, "Raton Izquierdo");
	control->setActionPeripheral(ActionMenu::DOWN, app->getKeyboard(), ALLEGRO_KEY_DOWN, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::UP, app->getKeyboard(), ALLEGRO_KEY_UP, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::ENTER, app->getKeyboard(), ALLEGRO_KEY_ENTER, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::MOUSE_MICKEY_LEFT, app->getMouse(), Mouse::buttons::MICKEY_LEFT, Peripheral::ON_PRESS);

	/** Esta clase sera controlada por este control*/
	control->setOwner(this);
	controlManager->addControl(control);
	controlManager->addPeripheral(app->getKeyboard());
	controlManager->addPeripheral(app->getMouse());

	actorManager->add(new Background(0, 0));
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		actorManager->add(*it);
	}
	index = 0;
	useMouse = true;
	buttons.at(index)->isFocused(true);

}

void Menu::draw() const {
    al_clear_to_color(R::Color::BLACK);
    stageManager->update();
    al_draw_bitmap(Gallery::getSingleton().getImage(R::Image::ARKANOID_LOGO), 100, 0, NULL);
}

void Menu::update() {
    actorManager->update();
	controlManager->update();

	if (app->getMouse()->changedPosition()) {
		al_show_mouse_cursor(app->getDisplay());
		useMouse = true;
		app->getMouse()->updateLastPosition();
	}

	if (useMouse) {
		insideIndex = insideButton();
		if (insideIndex != -1 && insideIndex != index) {
			Sound::playSample(R::Sample::CLICK);
			buttons.at(index)->isFocused(false);
			index = insideIndex;
			buttons.at(index)->isFocused(true);
		}
	}
}

void Menu::doAction(ControllableObject::action_t action, int magnitute) {
	buttons.at(index)->isFocused(false);
	switch (action) {
	case ActionMenu::UP:
		Sound::playSample(R::Sample::CLICK);
		al_hide_mouse_cursor(app->getDisplay());
		index = (index + buttons.size() - 1) % buttons.size();
		useMouse = false;
		break;
	case ActionMenu::DOWN:
		Sound::playSample(R::Sample::CLICK);
		al_hide_mouse_cursor(app->getDisplay());
		index = (index + 1) % buttons.size();
		useMouse = false;
		break;
	case ActionMenu::ENTER:
		switch (index) {
		case 0: /*START GAME*/
			app->setInterface(Application::INTERFACE_SCREEN::GAME);
			break;
		case 1: /*HIGHSCORES*/
			app->setInterface(Application::INTERFACE_SCREEN::HIGHSCORES);
			break;
		case 2:/*OPTIONS*/
			app->setInterface(Application::INTERFACE_SCREEN::OPTIONS);
			break;
		case 3:	/*HELP*/
			app->setInterface(Application::INTERFACE_SCREEN::HELP);
			break;
		case 4:	/*ABOUT*/
			app->setInterface(Application::INTERFACE_SCREEN::ABOUT);
			break;
		case 5: /*QUIT*/
			app->quit();
			break;
		default:
			break;
		}
		al_show_mouse_cursor(app->getDisplay());
		break;
	case ActionMenu::MOUSE_MICKEY_LEFT:
		if (useMouse) {
			insideIndex = insideButton();
			switch (insideIndex) {
			case 0: /*START GAME*/
				app->setInterface(Application::INTERFACE_SCREEN::GAME);
				break;
			case 1: /*HIGHSCORES*/
				app->setInterface(Application::INTERFACE_SCREEN::HIGHSCORES);
				break;
			case 2:/*OPTIONS*/
				app->setInterface(Application::INTERFACE_SCREEN::OPTIONS);
				break;
			case 3:	/*HELP*/
				app->setInterface(Application::INTERFACE_SCREEN::HELP);
				break;
			case 4: /*ABOUT*/
				app->setInterface(Application::INTERFACE_SCREEN::ABOUT);
				break;
			case 5:	/*QUIT*/
			    cout << "ES SALIR" << endl;
				app->quit();
				break;
			default:
				break;
			}
		}
		break;
	}

	buttons.at(index)->isFocused(true);
}

int Menu::insideButton() const {
	for (size_t i = 0; i < buttons.size(); i++) {
		if (app->getMouse()->inside(buttons.at(i)->getXInit(), buttons.at(i)->getYInit(), buttons.at(i)->getXEnd(), buttons.at(i)->getYEnd())) {
			return i;
		}
	}
	return -1;
}

Menu::~Menu() {
	delete controlManager;
	delete actorManager;
	delete stageManager;
}
