#include "Vaus.hpp"

#include "Mouse.hpp"
#include "Bullet.hpp"
#include "Gallery.hpp"
#include "Game.hpp"
#include "Sound.hpp"
#include "Level.hpp"

Vaus::Vaus(const float& x, const float& y, Game* g) : game(g),
state(VausState::NORMAL),
velocity(6),
lives(4) {
	position.setPosition(x, y);
	for (auto it = sprites.begin(); it != sprites.end(); it++) {
		it->setOwner(this);
		it->reinit();
	}
	int ticks = 9;
	int ticksL = 1;
	// Añadiendo frames a la animación normal. 44,22
	sprites[static_cast<size_t>(VausState::NORMAL)].setRepeat(true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 0, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 22, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 44, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 66, 44, 22, ticks, true); //
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 44, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 22, 44, 22, ticks, true);


	ticks = 8;
	// No olvidar los desplazamientos basados en el ancho y el alto	 88 x 22
	sprites[static_cast<size_t>(VausState::DEAD)].addFrame(R::Image::PADDLE, 0, 0, 44, 22, 50, true);
	sprites[static_cast<size_t>(VausState::DEAD)].addFrame(R::Image::PADDLE, 189, 509, 88, 27, ticks, false, 0, -3);
	sprites[static_cast<size_t>(VausState::DEAD)].addFrame(R::Image::PADDLE, 187, 557, 97, 35, ticks, false, 0, -6);
	sprites[static_cast<size_t>(VausState::DEAD)].addFrame(R::Image::PADDLE, 183, 605, 107, 43, ticks, false, 0, -10);
	sprites[static_cast<size_t>(VausState::DEAD)].addFrame(R::Image::PADDLE, 175, 654, 123, 56, ticks, false, 0, -17);

	int ticksAfter = 80;
	/* Transparente para que se quede ahi hasta que reviva, si es que lo hace.*/
	sprites[static_cast<size_t>(VausState::DEAD)].addFrame(R::Image::PADDLE, 682, 963, 88, 22,ticksAfter, false);

}

void Vaus::draw() const {
	sprites[static_cast<size_t>(state)].draw();

	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		it->draw();
	}
	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::SHADOWN_TITLE, 722, 342, ALLEGRO_ALIGN_CENTER, "LIVES");
	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::WHITE, 720, 340, ALLEGRO_ALIGN_CENTER, "LIVES");
	for (int i = 0; i < lives; i++) {
		al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), 684, 176, 32, 32, 660 + 30 * i, 370, NULL);
	}
}

void Vaus::update() {

	sprites[static_cast<size_t>(state)].update();

	// Actualiza las balas
	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		it->update();
	}

	if (isDead()) {
		if (sprites[static_cast<size_t>(state)].animationFinish()) {
			if (lives < 1) {
				game->over();
			}
			else {
				game->relive();
				lives--;
			}

		}

	}

	verifyLimits();
}

void Vaus::doAction(action_t action, int magnitute) {

    switch (action) {
        case RIGHT_VAUS:
			if (!isDead()) {
				position.setX(position.X() + velocity);
			}
			break;
		case LEFT_VAUS:
			if (!isDead()) {
				position.setX(position.X() - velocity);
			}
			break;
    }

//	if (action == SHOT) {
//	}
}

/* Verifica que la posición de la nave no se salga de los límites horizontales. */
void Vaus::verifyLimits() {
	if (position.X() < 88) {
		position.setX(88);
	}
	else if (position.X() + getWidth() > 613) {
		position.setX(613 - getWidth());
	}
}

bool Vaus::isDead() const {
	return (state == VausState::DEAD);
}
void Vaus::setLives(int value) {
	lives = value;
}

int Vaus::getLives() const {
	return lives;
}

void Vaus::setState(VausState _state) {
	/* No hace nada si el estado es el mismo. */
	if (_state == state) return;

	/* Inicia la animación del estado actual al estado que se desea. */

}

VausState Vaus::getState() const {
	return state;
}

float Vaus::getWidth() const {
	return sprites[static_cast<size_t>(state)].getWidth();
}

float Vaus::getHeight() const {
	return 22;
}

void Vaus::clearBullets() {
	bullets.clear();
}
