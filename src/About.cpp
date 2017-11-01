#include "About.hpp"

#include "Application.hpp"
#include "ActorManager.hpp"
#include "StageManager.hpp"
#include "ControlManager.hpp"
#include "Gallery.hpp"
#include "Button.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

About::About(Application*const app) : Interface(app),
controlManager(nullptr),
actorManager(nullptr),
stageManager(nullptr) {

	/*Botones que tendrá esta interface. */
	buttons.push_back(new Button(89, 50, R::String::BACK, ButtonType::SMALL));
	buttons.push_back(new Button(400, 392, R::String::GITHUB, ButtonType::GITHUB));

	controlManager = new ControlManager;
	actorManager = new ActorManager;
	stageManager = new StageManager(actorManager);

	Control* control = new Control;
	/* Asigna acciónes a las que respondera esta interface. */
	control->addActionName(ActionMenu::DOWN, "Bajar");
	control->addActionName(ActionMenu::UP, "Subir");
	control->addActionName(ActionMenu::ENTER, "Enter");
	control->addActionName(ActionMenu::LEFT, "Izquierda");
	control->addActionName(ActionMenu::RIGHT, "Derecha");
	control->addActionName(ActionMenu::BACKSPACE, "Atras");
	control->addActionName(ActionMenu::MOUSE_MICKEY_LEFT, "Raton Izquierdo");
	control->setActionPeripheral(ActionMenu::DOWN, app->getKeyboard(), ALLEGRO_KEY_DOWN, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::UP, app->getKeyboard(), ALLEGRO_KEY_UP, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::ENTER, app->getKeyboard(), ALLEGRO_KEY_ENTER, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::LEFT, app->getKeyboard(), ALLEGRO_KEY_LEFT, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::RIGHT, app->getKeyboard(), ALLEGRO_KEY_RIGHT, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::BACKSPACE, app->getKeyboard(), ALLEGRO_KEY_BACKSPACE, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::MOUSE_MICKEY_LEFT, app->getMouse(), Mouse::buttons::MICKEY_LEFT, Peripheral::ON_PRESS);

	/** Esta clase sera controlada por este control*/
	control->setOwner(this);
	controlManager->addControl(control);
	controlManager->addPeripheral(app->getKeyboard());
	controlManager->addPeripheral(app->getMouse());

	/* Agrega los botons al actorManager, ya no es necesario eliminar la memoria reservada por
	estos ya que actorManager se encarga de eso. */
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		actorManager->add(*it);
	}
	index = 0; // Inicialmente el foco estará en el primer boton que se agrego al vector buttons.
	buttons.at(index)->isFocused(true);

	useMouse = true;
}

void About::draw() const {
	static Gallery& gallery = Gallery::getSingleton();
	static auto fSmall = gallery.getFont(R::Font::VENUS_SMALL);
	static auto f = gallery.getFont(R::Font::VENUS_20);
	static auto fBig = gallery.getFont(R::Font::VENUS_TITLES);

	/*Fondo*/
	al_draw_bitmap(gallery.getImage(R::Image::BACKGROUND1), 0, 0, 0);

	/*Logo Arkanoid*/
	al_draw_scaled_bitmap(gallery.getImage(R::Image::ARKANOID_LOGO), 0, 0, 600, 218, 265, 120, 270, 98, NULL);

	/* Title ABOUT*/
	al_draw_text(fBig, R::Color::SHADOWN_TITLE, 404, 24, ALLEGRO_ALIGN_CENTER, R::String::ABOUT.c_str());
	al_draw_text(fBig, R::Color::WHITE, 400, 20, ALLEGRO_ALIGN_CENTER, R::String::ABOUT.c_str());

	/* Version game*/
	al_draw_text(fSmall, R::Color::WHITE, 400, 210, ALLEGRO_ALIGN_CENTER, R::String::VERSION_GAME.c_str());

	al_draw_text(f, R::Color::WHITE, 400, 280, ALLEGRO_ALIGN_CENTER, "BREAKOUT ATARI");

	al_draw_text(f, R::Color::WHITE, 400, 345, ALLEGRO_ALIGN_CENTER, R::String::NAME_AUTHOR.c_str());
	al_draw_text(fSmall, R::Color::WHITE, 400, 328, ALLEGRO_ALIGN_CENTER, "PROGRAMMER, TESTER AND DESIGNER : ");


	/* Powered by C++ and Allegro Library */
	al_draw_bitmap(gallery.getImage(R::Image::C_PLUS_PLUS_LOGO), 270, 440, NULL);
	al_draw_text(fSmall, R::Color::WHITE, 315, 530, ALLEGRO_ALIGN_CENTER, R::String::POWERED.c_str());
	al_draw_text(fSmall, R::Color::WHITE, 400, 480, ALLEGRO_ALIGN_CENTER, R::String::AND.c_str());
	al_draw_bitmap(gallery.getImage(R::Image::ALLEGRO_LOGO), 450, 440, NULL);

	/*Copyright*/
	al_draw_text(fSmall, R::Color::WHITE, 400, 565, ALLEGRO_ALIGN_CENTER, R::String::COPYRIGHT.c_str());

	/*Función draw de cada botón*/
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		(*it)->draw();
	}
}

void About::update() {
	stageManager->update();
	controlManager->update();
	stageManager->update();

	/*Si el mouse cambio de posición entonces el usuario quiere usar el mouse entonces
	el booleano useMouse es verdadero.*/
	if (app->getMouse()->changedPosition()) {
		useMouse = true;
		app->getMouse()->updateLastPosition();
	}

	/*Si use mouse es verdadero entonces verificamos si el cursor se encuentra sobre algun boton,
	si es asi el foco se ubica en ese boton. */
	if (useMouse) {
		insideIndex = insideButton();
		/*Si insideIndex es -1 no se hace nada, ademas si el foco estuvo sobre ese boton ya no es necesario
		cambiar, no?*/
		if (insideIndex != -1 && insideIndex != index) {
			buttons.at(index)->isFocused(false);
			index = insideIndex;
			buttons.at(index)->isFocused(true);
		}
	}
}

void About::doAction(action_t action, int magnitute) {
	buttons.at(index)->isFocused(false);
	switch (action) {
		/* Las teclas UP y LEFT tienen la misma función. */
	case ActionMenu::UP:
	case ActionMenu::LEFT:
		/*Si el foco estuvo en el primer botón entonces el foco se ubica en el último botón.*/
		index = (index + buttons.size() - 1) % buttons.size();
		useMouse = false;
		break;

		/* Acá igualmente estas dos teclas tienen la misma función. */
	case ActionMenu::DOWN:
	case ActionMenu::RIGHT:
		index = (index + 1) % buttons.size();
		useMouse = false;
		break;

	case ActionMenu::ENTER:
		switch (index) {
		case 0: /* BACK */
			app->setInterface(Application::INTERFACE_SCREEN::MAIN_MENU);
			break;
		default:
			break;
		}
		break;
	case ActionMenu::BACKSPACE:
		/* Al presionar la tecla Backspace se muestra el Menu Principal.*/
		app->setInterface(Application::INTERFACE_SCREEN::MAIN_MENU);
		break;
	case ActionMenu::MOUSE_MICKEY_LEFT:
		if (useMouse) {
			insideIndex = insideButton();
			switch (insideIndex) {
			case 0: /* BACK */
				app->setInterface(Application::INTERFACE_SCREEN::MAIN_MENU);
				break;
			default:
				break;
			}
		}
		break;
	}
	buttons.at(index)->isFocused(true);
}

/*Si el mouse se encuentra dentro de una región ocupado por un botón del vector buttons
entonces retorna el indice del botón en el vector, de lo contrario retorna (-1). */
int About::insideButton() const {
	for (size_t i = 0; i < buttons.size(); i++) {
		if (app->getMouse()->inside(buttons.at(i)->getXInit(), buttons.at(i)->getYInit(), buttons.at(i)->getXEnd(), buttons.at(i)->getYEnd())) {
			return i; /* Retorna el indice del boton */
		}
	}
	return -1;
}

About::~About() {
	delete controlManager;
	delete actorManager;
	delete stageManager;
}