#include "Level.hpp"

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>

#include <fstream>

#include "Utils.hpp"
#include "Vaus.hpp"
#include "Bonus.hpp"
#include "Score.hpp"
#include "Sound.hpp"
#include "Gallery.hpp"

using namespace std;


Level::Level(const float& x, const float& y, Vaus* _vaus) : Actor(x, y),  vaus(_vaus) {
	actualLevel = 1;
	showLvl = true;
}

void Level::draw() const {

	// Dibuja el texto nivel
//	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::SHADOWN_TITLE, 722, 152, ALLEGRO_ALIGN_CENTER, "LEVEL");
//	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::WHITE, 720, 150, ALLEGRO_ALIGN_CENTER, "LEVEL");
//	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::SHADOW_GRAY, 722, 182, ALLEGRO_ALIGN_CENTER, "%i", actualLevel);
//	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::WHITE, 720, 180, ALLEGRO_ALIGN_CENTER, "%i", actualLevel);

	if (showLvl) {

	}

}

void Level::update() {


}

void Level::setLevel(int level) {
	actualLevel = level;
}


bool Level::empty() {
	bool isempty = true;
	return false;
}

int Level::getLevel() const {
	return actualLevel;
}

void Level::clearBonuses() {
	for (auto itBonus = bonuses.begin(); itBonus != bonuses.end(); itBonus++) {
		delete(*itBonus);
	}
	bonuses.clear();
}

void Level::clearBlocks() {

}


/* Para la animación */
void Level::show() {
	showLvl = true;
}

void Level::hide() {
	showLvl = false;
}

void Level::loadLevel() {


	ifstream file;
	string filename("resources/levels/level_" + Utils::intToStr(actualLevel) + ".lvl");

	file.open(filename, ios::in);
	//ALLEGRO_FILE* file = al_fopen(filename.c_str(), "r");

	int rows = 12;
	int coordX = 0;
	int coordY = 0;
	int type;

	clearBlocks();

	if (file) {
		printf("Se cargo correctamenete el archivo %s \n", filename.c_str());

		while (file >> type) {
			coordX++;
			if (type >= 1 && type <= 10) {

			}
			if (coordX % rows == 0) {
				coordY++;
				coordX = 0;
			}
		}
		file.close();

		int randIndex;
		int randType;
		/* Lleando algunos bloques con items bonus */

	}
	else {
		printf("No se pudo cargar el archivo %s \n", filename.c_str());
		if (getLevel() > 1) {
			actualLevel = 1;
			loadLevel();
		}
	}
}



Level::~Level() {

	clearBonuses();
}
