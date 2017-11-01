#include "GameOver.hpp"

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>

#include "Gallery.hpp"
#include "R.hpp"


GameOver::GameOver() : velocity(9) {
	reinit();
}

void GameOver::draw() const {
	al_draw_filled_rectangle(rectPos.X() - 1, rectPos.Y(), rectPos.X() + 804, rectPos.Y() + 200, al_map_rgba(180, 40, 40, 150));
	al_draw_scaled_bitmap(Gallery::getSingleton().getImage(R::Image::SHADOW_TOP), 0, 0, 64, 33, rectPos.X(), 200, 804, 15, NULL);
	al_draw_scaled_bitmap(Gallery::getSingleton().getImage(R::Image::SHADOW_BOTTOM), 0, 0, 64, 33, rectPos.X(), 385, 804, 15, NULL);

	al_draw_scaled_bitmap(Gallery::getSingleton().getImage(R::Image::SHADOW_LEFT), 0, 0, 33, 64, rectPos.X(), 200, 15, 200, NULL);
	al_draw_scaled_bitmap(Gallery::getSingleton().getImage(R::Image::SHADOW_RIGHT), 0, 0, 33, 64, rectPos.X() + 798, 200, 15, 200, NULL);


	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_INTRO), R::Color::GREEN, titlePos.X() + 4, titlePos.Y() + 4, ALLEGRO_ALIGN_CENTER, R::String::GAMEOVER.c_str());
	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_INTRO), R::Color::WHITE, titlePos.X(), titlePos.Y(), ALLEGRO_ALIGN_CENTER, R::String::GAMEOVER.c_str());

}

void GameOver::update() {
	if (titlePos.X() > (400 - velocity / 2) && titlePos.X() <= (400 + velocity / 2)) {
		counter = (counter + 1) % 100000;
		if (counter > 200) {
			titlePos.setX(titlePos.X() - velocity);
		}
	}
	else {
		rectPos.setX(rectPos.X() + velocity + velocity / 3.81);
		titlePos.setX(titlePos.X() - velocity);
	}

	/* Es /2 */
	if (titlePos.X() <  -(al_get_text_width(Gallery::getSingleton().getFont(R::Font::VENUS_BIG), R::String::GAMEOVER.c_str()) + 2000)) {
		finish = true;
	}

	// Hacer cierra telón con la imagen de fondo.



}

bool GameOver::animationFinish() const {
	return finish;
}

void GameOver::reinit() {
	counter = 0;
	finish = false;
	rectPos.setPosition(-800 - velocity, 200);
	titlePos.setPosition(800 + al_get_text_width(Gallery::getSingleton().getFont(R::Font::VENUS_BIG), R::String::GAMEOVER.c_str()) / 2 + velocity, 250);
}

GameOver::~GameOver() {

}