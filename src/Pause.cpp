#include "Pause.hpp"

#include <allegro5\allegro_primitives.h>

#include "Button.hpp"
#include "Mouse.hpp"
#include "R.hpp"
#include "Gallery.hpp"
#include "ControlManager.hpp"
#include "Control.hpp"
#include "Game.hpp"
#include "Keyboard.hpp"
#include "Sound.hpp"

Pause::Pause(float x, float y, Game* g, Mouse* m, Keyboard* k) :
	game(g),
	mouse(m),
	keyboard(k),
	controlM(nullptr) {
	position.setPosition(x, y);
	float initY = 330;

	/* Botones del menu pausa. */
	buttons.push_back(new Button(400, initY, R::String::CONTINUE));
	buttons.push_back(new Button(400, initY + 55, R::String::RESTART));
	buttons.push_back(new Button(400, initY + 110, R::String::QUIT));

	controlM = new ControlManager;

	Control* controlPause = new Control;
	controlPause->addActionName(ActionMenu::UP, "Subir");
	controlPause->addActionName(ActionMenu::DOWN, "Bajar");
	controlPause->addActionName(ActionMenu::ENTER, "Enter");
	controlPause->addActionName(ActionMenu::ESCAPE, "Escape");
	controlPause->addActionName(ActionMenu::BACKSPACE, "Backspace");
	controlPause->addActionName(ActionMenu::MOUSE_MICKEY_LEFT, "Raton Izquierdo");

	controlPause->setActionPeripheral(ActionMenu::UP, keyboard, ALLEGRO_KEY_UP, Peripheral::ON_PRESS);
	controlPause->setActionPeripheral(ActionMenu::DOWN, keyboard, ALLEGRO_KEY_DOWN, Peripheral::ON_PRESS);
	controlPause->setActionPeripheral(ActionMenu::ENTER, keyboard, ALLEGRO_KEY_ENTER, Peripheral::ON_PRESS);
	controlPause->setActionPeripheral(ActionMenu::ESCAPE, keyboard, ALLEGRO_KEY_ESCAPE, Peripheral::ON_PRESS);
	controlPause->setActionPeripheral(ActionMenu::BACKSPACE, keyboard, ALLEGRO_KEY_BACKSPACE, Peripheral::ON_PRESS);

	controlPause->setActionPeripheral(ActionMenu::MOUSE_MICKEY_LEFT, mouse, Mouse::buttons::MICKEY_LEFT, Peripheral::ON_PRESS);


	controlPause->setOwner(this);

	controlM->addControl(controlPause);
	controlM->addPeripheral(keyboard);
	controlM->addPeripheral(mouse);

	index = 0;
	useMouse = true;
	buttons.at(index)->isFocused(true);
}

void Pause::draw() const {
	al_draw_filled_rectangle(0, 0, 800, 600, al_map_rgba(10, 10, 10, 150));
	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_TITLES), R::Color::SHADOWN_TITLE, 404, 234, ALLEGRO_ALIGN_CENTER, R::String::PAUSE.c_str());

	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_TITLES), R::Color::WHITE, 400, 230, ALLEGRO_ALIGN_CENTER, R::String::PAUSE.c_str());
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		(*it)->draw();
	}
}

void Pause::update() {
	controlM->update();

	if (mouse->changedPosition()) {
		useMouse = true;
		mouse->updateLastPosition();
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

void Pause::doAction(action_t action, int magnitute) {
	buttons.at(index)->isFocused(false);
	switch (action) {
	case ActionMenu::DOWN:
		Sound::playSample(R::Sample::CLICK);
		index = (index + 1) % buttons.size();
		useMouse = false;
		break;
	case ActionMenu::UP:
		Sound::playSample(R::Sample::CLICK);
		index = (index + buttons.size() - 1) % buttons.size();
		useMouse = false;
		break;
	case ActionMenu::ENTER:
		switch (index) {
		case 0:	/* CONTINUE*/
			game->setPause(false);
			break;
		case 1: /*RESTART*/

			break;
		case 2:	/*QUIT, sale del juego*/
			game->backToMenu();
			break;
		default:
			break;
		}
		break;
	case ActionMenu::ESCAPE:
	case ActionMenu::BACKSPACE:
		game->setPause(false);
		break;
	case ActionMenu::MOUSE_MICKEY_LEFT:
		if (useMouse) {
			insideIndex = insideButton();
			switch (insideIndex) {
			case 0:	/* CONTINUE*/
				game->setPause(false);
				break;
			case 1: /*RESTART, reinicia el juego al nivel 1*/
				break;
			case 2:	/*QUIT, sale del juego*/
				game->backToMenu();
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
	buttons.at(index)->isFocused(true);
}

int Pause::insideButton() {
	for (size_t i = 0; i < buttons.size(); i++) {
		if (mouse->inside(buttons.at(i)->getXInit(), buttons.at(i)->getYInit(), buttons.at(i)->getXEnd(), buttons.at(i)->getYEnd())) {
			return i;
		}
	}
	return -1;
}

void Pause::reinit() {
	index = 0;
}

Pause::~Pause() {
	delete controlM;
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		delete(*it);
	}
}
