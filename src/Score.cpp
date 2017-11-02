#include "Score.hpp"

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <iostream>

#include "Gallery.hpp"

int Score::scorePlayer = 0x26632;

Score::Score() {

}

void Score::draw() const {
//	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::SHADOWN_TITLE, 722, 242, ALLEGRO_ALIGN_CENTER, "SCORE");
//	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::WHITE, 720, 240, ALLEGRO_ALIGN_CENTER, "SCORE");
//	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::SHADOW_GRAY, 722, 272, ALLEGRO_ALIGN_CENTER, "%i", scorePlayer);
//	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::WHITE, 720, 270, ALLEGRO_ALIGN_CENTER, "%i", scorePlayer);

}

void Score::update() {

}
void Score::addToScore(int value) {
	scorePlayer += value;
}

void Score::setScore(int score) {
	scorePlayer = score;
}
int Score::getScore() {
	return scorePlayer;
}

Score::~Score() {
	std::cout << "Ya sali del colset " << std::endl;
}
