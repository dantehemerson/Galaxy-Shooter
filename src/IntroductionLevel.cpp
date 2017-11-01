#include "IntroductionLevel.hpp"

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_primitives.h>

#include "Gallery.hpp"
#include "R.hpp"
#include "Level.hpp"


const int IntroductionLevel::waitTime = 85;
const int IntroductionLevel::animationStart = 310;

IntroductionLevel::IntroductionLevel(Level* level) : level(level), velocity(9), counterStart(0) {
	isStart = true;
	velocityAnimationAlpha = 2;
	reinit();
}

void IntroductionLevel::draw() const {
	if (isStart) {
		al_draw_filled_rectangle(0, 0, 800, 600, al_map_rgba(0, 0, 0, alpha));
	}

	al_draw_filled_rectangle(rectPos.X() - 1, rectPos.Y(), rectPos.X() + 800, rectPos.Y() + 240, al_map_rgba(50, 50, 50, 150));
	al_draw_scaled_bitmap(Gallery::getSingleton().getImage(R::Image::SHADOW_TOP), 0, 0, 64, 33, rectPos.X(), 200, 800, 15, NULL);
	al_draw_scaled_bitmap(Gallery::getSingleton().getImage(R::Image::SHADOW_BOTTOM), 0, 0, 64, 33, rectPos.X(), 425, 800, 15, NULL);

	al_draw_scaled_bitmap(Gallery::getSingleton().getImage(R::Image::SHADOW_LEFT), 0, 0, 33, 64, rectPos.X(), 200, 15, 200, NULL);
	al_draw_scaled_bitmap(Gallery::getSingleton().getImage(R::Image::SHADOW_RIGHT), 0, 0, 33, 64, rectPos.X() + 785, 200, 15, 200, NULL);

	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_INTRO), R::Color::GREEN, titlePos.X() + 4, titlePos.Y() + 4, ALLEGRO_ALIGN_CENTER, "LEVEL %i", level->getLevel());
	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_INTRO), R::Color::WHITE, titlePos.X(), titlePos.Y(), ALLEGRO_ALIGN_CENTER, "LEVEL %i", level->getLevel());

	if (isStart) {
		al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_BIG), R::Color::GREEN, titlePos.X() + 4, 364, ALLEGRO_ALIGN_CENTER, "START");
		al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_BIG), R::Color::WHITE, titlePos.X(), 360, ALLEGRO_ALIGN_CENTER, "START");
	}

}

void IntroductionLevel::update() {

	if (counterStart < animationStart) {
		if (!isStart) {
			counterStart = animationStart;
		}
		else {
			if (initLLC) {
				loadLevelCounter++;
				if (loadLevelCounter > 50) {
					initLLC = false;
				}
			}
			else {
				alpha += velocityAnimationAlpha;
			}

			if (alpha >= 255) {
				level->show();
				alpha = 254;
				velocityAnimationAlpha = 2;
				velocityAnimationAlpha *= -1; // Para que ahora disminuya
				initLLC = true;
			}
			else if (alpha <= 0) {
				alpha = 0;
			}

			counterStart++;
		}

		if (counterStart == animationStart) {
			isStart = false;
		}

	}

	if (counterStart >= animationStart) {
		if (titlePos.X() > (400 - velocity / 2) && titlePos.X() <= (400 + velocity / 2)) {
			counter = (counter + 1) % 100000;
			if (counter > waitTime) {
				titlePos.setX(titlePos.X() - velocity);
			}
		}
		else {
			rectPos.setX(rectPos.X() + velocity + velocity / 3.73);
			titlePos.setX(titlePos.X() - velocity);
		}

		/* Es /2 */
		if (titlePos.X() <  -al_get_text_width(Gallery::getSingleton().getFont(R::Font::VENUS_INTRO), "NIVEL 0")) {
			finish = true;
		}
	}

}

bool IntroductionLevel::animationFinish() const {
	return finish;
}

void IntroductionLevel::setStart(bool value) {
	isStart = value;
}

void IntroductionLevel::reinit(bool initGame) {
	counter = 0;
	counterStart = 0;
	loadLevelCounter = 0;
	alpha = (initGame ? 255 : 0);
	initLLC = false;
	finish = false;
	velocityAnimationAlpha = 2;
	rectPos.setPosition(-800 - velocity, 200);
	titlePos.setPosition(800 + al_get_text_width(Gallery::getSingleton().getFont(R::Font::VENUS_INTRO), "NIVEL 00") / 2 + velocity, 250);
}

IntroductionLevel::~IntroductionLevel() {

}