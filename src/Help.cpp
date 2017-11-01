#include "Help.hpp"

// Ancho y Alto del Bitmap en el que se dibujarán los items
#define WIDTH_ITEMS_BMP 800	
#define HEIGHT_ITEMS_BMP 1000

#include <allegro5\allegro_primitives.h>

#include "Application.hpp"
#include "ActorManager.hpp"
#include "StageManager.hpp"
#include "ControlManager.hpp"
#include "Gallery.hpp"
#include "Button.hpp"
#include "Mouse.hpp"
#include "Keyboard.hpp"

Help::Help(Application*const app) : Interface(app),
controlManager(nullptr),
actorManager(nullptr),
stageManager(nullptr),
itemsBMP(nullptr),
velocityScroll(3) {

	showArrowBottom = true; showArrowTop = false;

	/*Botones que tendrá esta interface. */
	buttons.push_back(new Button(89, 50, R::String::BACK, ButtonType::SMALL));

	controlManager = new ControlManager;
	actorManager = new ActorManager;
	stageManager = new StageManager(actorManager);

	Control* control = new Control;
	/* Asigna acciónes a las que respondera esta interface. */
	control->addActionName(ActionMenu::DOWN, "Bajar");
	control->addActionName(ActionMenu::UP, "Subir");
	control->addActionName(ActionMenu::ENTER, "Enter");
	control->addActionName(ActionMenu::BACKSPACE, "Atras");
	control->addActionName(ActionMenu::MOUSE_MICKEY_LEFT, "Raton Izquierdo");
	control->addActionName(ActionMenu::MOUSE_MICKEY_LEFT_DOWN, "Raton  Izquierdo Presionando");
	control->addActionName(ActionMenu::MOUSE_MICKEY_LEFT_UP, "Raton Izquierdo Up");
	//ALLEGRO_KEY_END
	control->setActionPeripheral(ActionMenu::DOWN, app->getKeyboard(), ALLEGRO_KEY_DOWN, Peripheral::ON_PRESSING);
	control->setActionPeripheral(ActionMenu::UP, app->getKeyboard(), ALLEGRO_KEY_UP, Peripheral::ON_PRESSING);
	control->setActionPeripheral(ActionMenu::ENTER, app->getKeyboard(), ALLEGRO_KEY_ENTER, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::BACKSPACE, app->getKeyboard(), ALLEGRO_KEY_BACKSPACE, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::MOUSE_MICKEY_LEFT, app->getMouse(), Mouse::buttons::MICKEY_LEFT, Peripheral::ON_PRESS);
	control->setActionPeripheral(ActionMenu::MOUSE_MICKEY_LEFT_DOWN, app->getMouse(), Mouse::buttons::MICKEY_LEFT, Peripheral::ON_PRESSING);
	control->setActionPeripheral(ActionMenu::MOUSE_MICKEY_LEFT_UP, app->getMouse(), Mouse::buttons::MICKEY_LEFT, Peripheral::ON_RELEASE);

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
	itemsBMP = al_create_bitmap(WIDTH_ITEMS_BMP, HEIGHT_ITEMS_BMP);

	/*Dibujando en el bitmap --------------------------------------------------------*/
	al_set_target_bitmap(itemsBMP); // Desde aca lo que dibujemos se dibujará en el bitmap
	al_clear_to_color(R::Color::TRANSPARENTS);

	/* Dibuja la información de Ayuda en el Bitmap itemsBMP, de esta manera ya no será necesario
	llamar a dibujar cada uno si no que solo se llamará a el BITMAP.*/
	drawItems();
	al_set_target_backbuffer(app->getDisplay()); // Ahora todo lo que dibujemos sera en display
												 /*----------------------------------------------------------------------------------*/

												 // Posición inicial de itemsBMP
	positionItemsBMP = Vector2(120, 100);
}

void Help::draw() const {
	static Gallery& gallery = Gallery::getSingleton();
	static auto fSmall = gallery.getFont(R::Font::VENUS_SMALL);
	static auto f = gallery.getFont(R::Font::VENUS_20);
	static auto fBig = gallery.getFont(R::Font::VENUS_TITLES);

	/* Fondo */
	al_draw_bitmap(gallery.getImage(R::Image::BACKGROUND1), 0, 0, NULL);

	/*Dibuja el rectangulo transparente*/
	al_draw_filled_rectangle(80, 100, 720, 580, R::Color::BACKGROUND_ABOUT_TRANSPARENT);
	/*Dibuja el bitmap con los items*/
	al_draw_bitmap(itemsBMP, positionItemsBMP.X(), positionItemsBMP.Y(), NULL);

	/*Ahora pintamos las partes de arriba y abajo para que no se muestre el bitmap completo y se
	muestre solo una parte y se vaya ocultando cuando se hace scroll*/
	al_draw_bitmap_region(gallery.getImage(R::Image::BACKGROUND1), 0, 0, 800, 100, 0, 0, NULL);
	al_draw_bitmap_region(gallery.getImage(R::Image::BACKGROUND1), 0, 580, 800, 20, 0, 580, NULL);

	/*Shadow top and Bottom*/
	al_draw_scaled_bitmap(gallery.getImage(R::Image::SHADOW_TOP), 0, 0, 64, 33, 80, 100, 640, 15, NULL);
	al_draw_scaled_bitmap(gallery.getImage(R::Image::SHADOW_BOTTOM), 0, 0, 64, 33, 80, 565, 640, 15, NULL);

	if (showArrowTop)
		al_draw_filled_triangle(400, 85, 380, 97, 420, 97, R::Color::WHITE);
	if (showArrowBottom)
		al_draw_filled_triangle(400, 595, 380, 583, 420, 583, R::Color::WHITE);


	/* ABOUT*/
	al_draw_text(fBig, R::Color::SHADOWN_TITLE, 404, 24, ALLEGRO_ALIGN_CENTER, R::String::HELP.c_str());
	al_draw_text(fBig, R::Color::WHITE, 400, 20, ALLEGRO_ALIGN_CENTER, R::String::HELP.c_str());

	/*Todos los botones */
	for (auto it = buttons.begin(); it != buttons.end(); it++) {
		(*it)->draw();
	}

}

void Help::update() {
	stageManager->update();
	controlManager->update();
	stageManager->update();

	if (app->getMouse()->changedPosition()) {
		useMouse = true;
		app->getMouse()->updateLastPosition();
	}

	if (useMouse) {
		insideIndex = insideButton();
		if (insideIndex != -1 && insideIndex != index) {
			buttons.at(index)->isFocused(false);
			index = insideIndex;
			buttons.at(index)->isFocused(true);
		}
	}
}

void Help::doAction(action_t action, int magnitute) {
	buttons.at(index)->isFocused(false);
	switch (action) {
	case ActionMenu::UP:
		positionItemsBMP.setY(positionItemsBMP.Y() + velocityScroll);
		helpPosition(); // Verifica si la posición de itemsBMP esta en el rango correcto.
		break;
	case ActionMenu::DOWN:
		positionItemsBMP.setY(positionItemsBMP.Y() - velocityScroll);
		helpPosition(); // Verifica si la posición de itemsBMP esta en el rango correcto.

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

		difference = (positionItemsBMP.Y() - app->getMouse()->getY());

		break;
	case ActionMenu::MOUSE_MICKEY_LEFT_UP:
		al_set_system_mouse_cursor(app->getDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
		break;
	case ActionMenu::MOUSE_MICKEY_LEFT_DOWN:
		if (app->getMouse()->inside(80, 100, 720, 580)) {
			al_set_system_mouse_cursor(app->getDisplay(), ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
			//if (difference)
			positionItemsBMP.setY(app->getMouse()->getY() + difference);
			helpPosition(); // Verifica si la posición de itemsBMP esta en el rango correcto.
		}
		else {
			difference = 0;
		}

		break;
	}
	buttons.at(index)->isFocused(true);
}

int Help::insideButton() const {
	for (size_t i = 0; i < buttons.size(); i++) {
		if (app->getMouse()->inside(buttons.at(i)->getXInit(), buttons.at(i)->getYInit(), buttons.at(i)->getXEnd(), buttons.at(i)->getYEnd())) {
			return i;
		}
	}

	return -1;
}

void Help::helpPosition() {
	if (positionItemsBMP.Y() > 100) {
		positionItemsBMP.setY(100);

	}
	else if (positionItemsBMP.Y() + HEIGHT_ITEMS_BMP < 580) {
		positionItemsBMP.setY(580 - HEIGHT_ITEMS_BMP);
	}

	showArrowBottom = showArrowTop = true;
	if (positionItemsBMP.Y() == 100) {
		showArrowTop = false;
	}
	else if (positionItemsBMP.Y() == 580 - HEIGHT_ITEMS_BMP) {
		showArrowBottom = false;
	}
}

void Help::drawItems() {
	int widthBrick = 57;
	int heightBrick = 35;
	int initY = 30;
	int space = 10;
	int mult = 2;

	Gallery& gallery = Gallery::getSingleton();
	ALLEGRO_BITMAP* itemsGallery = gallery.getImage(R::Image::ITEMS);
	ALLEGRO_FONT* itemsFont = gallery.getFont(R::Font::VENUS_18);

	/*White Brick, aunque en realidad parece plomo but... */
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY, NULL, R::String::BRICK_WHITE_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 0, 0, widthBrick, heightBrick, 30, initY, NULL);

	/*Orange Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick + space, NULL, R::String::BRICK_ORANGE_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 58, 0, widthBrick, heightBrick, 30, initY + heightBrick + space, NULL);

	/*Light-Blue Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick * mult + space * mult, NULL, R::String::BRICK_LIGHT_BLUE_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 116, 0, widthBrick, heightBrick, 30, initY + heightBrick * mult + space * mult++, NULL);

	/*Green Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick * mult + space * mult, NULL, R::String::BRICK_GREEN_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 174, 0, widthBrick, heightBrick, 30, initY + heightBrick * mult + space * mult++, NULL);

	/*Red Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick * mult + space * mult, NULL, R::String::BRICK_RED_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 0, 36, widthBrick, heightBrick, 30, initY + heightBrick * mult + space * mult++, NULL);

	/*Blue Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick * mult + space * mult, NULL, R::String::BRICK_BLUE_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 58, 36, widthBrick, heightBrick, 30, initY + heightBrick * mult + space * mult++, NULL);

	/*Pink Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick * mult + space * mult, NULL, R::String::BRICK_PINK_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 116, 36, widthBrick, heightBrick, 30, initY + heightBrick * mult + space * mult++, NULL);

	/*Yellow Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick * mult + space * mult, NULL, R::String::BRICK_YELLOW_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 174, 36, widthBrick, heightBrick, 30, initY + heightBrick * mult + space * mult++, NULL);

	/*Silver Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick * mult + space * mult, NULL, R::String::BRICK_SILVER_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 232, 0, widthBrick, heightBrick, 30, initY + heightBrick * mult + space * mult++, NULL);

	/*Gold Brick*/
	al_draw_text(itemsFont, R::Color::WHITE, 130, initY + heightBrick * mult + space * mult, NULL, R::String::BRICK_GOLD_DESCRIPTION.c_str());
	al_draw_bitmap_region(itemsGallery, 232, 36, widthBrick, heightBrick, 30, initY + heightBrick * mult + space * mult++, NULL);


}

Help::~Help() {
	delete controlManager;
	delete actorManager;
	delete stageManager;
}