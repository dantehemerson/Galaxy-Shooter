#include "Level.hpp"

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>

#include <fstream>

#include "Utils.hpp"
#include "Ball.hpp"
#include "Vaus.hpp"
#include "Bonus.hpp"
#include "Score.hpp"
#include "Sound.hpp"
#include "Gallery.hpp"

using namespace std;


Level::Level(const float& x, const float& y, vector<Ball*>* _balls, Vaus* _vaus) : Actor(x, y), balls(_balls), vaus(_vaus) {
	Block::referencePosition.setPosition(x, y);
	actualLevel = 1;
	showLvl = true;
}

void Level::draw() const {

	// Dibuja el texto nivel
	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::SHADOWN_TITLE, 722, 152, ALLEGRO_ALIGN_CENTER, "LEVEL");
	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::WHITE, 720, 150, ALLEGRO_ALIGN_CENTER, "LEVEL");
	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::SHADOW_GRAY, 722, 182, ALLEGRO_ALIGN_CENTER, "%i", actualLevel);
	al_draw_textf(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::WHITE, 720, 180, ALLEGRO_ALIGN_CENTER, "%i", actualLevel);

	if (showLvl) {
		for (auto it = blocks.begin(); it != blocks.end(); it++) {
			(*it)->draw();
		}
		for (auto it = bonuses.begin(); it != bonuses.end(); it++) {
			(*it)->draw();
		}
	}

}

void Level::update() {
	for (auto itBonus = bonuses.begin(); itBonus != bonuses.end(); ) {
		(*itBonus)->update();

		if (((*itBonus)->position.Y() + (*itBonus)->getHeight()) > vaus->position.Y() &&
			((*itBonus)->position.Y() + (*itBonus)->getHeight()) < (vaus->position.Y() + vaus->getHeight()) &&
			((*itBonus)->position.X() + (*itBonus)->getWidth() - 3) > vaus->position.X() &&
			((*itBonus)->position.X() - 3) < (vaus->position.X() + vaus->getWidth())) {
			bool dead = vaus->getState() == VausState::DEAD_CHARGED || vaus->getState() == VausState::DEAD_NORMAL || vaus->getState() == VausState::DEAD_LARGE;
			if (!dead) {
				switch ((*itBonus)->getType()) {
				case BonusType::L:
					for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {
						(*itBall)->setState(BallState::NORMAL);
						(*itBall)->setStopped(false);
					}
					vaus->setState(VausState::CHARGED);
					break;
				case BonusType::E:
					for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {
						(*itBall)->setState(BallState::NORMAL);
						(*itBall)->setStopped(false);

					}
					vaus->setState(VausState::LARGE);
					break;
				case BonusType::B:
					for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {
						(*itBall)->setState(BallState::NORMAL);
						(*itBall)->setStopped(false);

					}
					vaus->setState(VausState::NORMAL);
					break;
				case BonusType::C:
					for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {
						(*itBall)->setState(BallState::STICKY);
					}
					vaus->setState(VausState::NORMAL);
					break;
				case BonusType::P:
					vaus->setLives(vaus->getLives() + 1);
					for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {
						(*itBall)->setState(BallState::NORMAL);
						(*itBall)->setStopped(false);

					}
					vaus->setState(VausState::NORMAL);
					break;
				case BonusType::S:
					for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {
						(*itBall)->setState(BallState::NORMAL);
						(*itBall)->setStopped(false);

					}
					vaus->setState(VausState::NORMAL);
					break;
				case BonusType::D:
					for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {
						(*itBall)->setState(BallState::NORMAL);
						(*itBall)->setStopped(false);

					}
					vaus->setState(VausState::NORMAL);
					break;
				default:
					break;
				}
			}
			delete (*itBonus);
			itBonus = bonuses.erase(itBonus);
		}
		else if ((*itBonus)->position.Y() > 600) {
			delete (*itBonus);
			itBonus = bonuses.erase(itBonus);
		}
		else {
			itBonus++;
		}
	}

	for (auto it = blocks.begin(); it != blocks.end(); it++) {
		(*it)->update();

		/* Colisión con las balas. */
		for (auto itBullet = vaus->bullets.begin(); itBullet != vaus->bullets.end(); ) {


			if ((*it)->getLives() > 0 &&
				itBullet->position.Y() < ((*it)->position.Y() + (*it)->getHeight()) &&
				itBullet->position.Y() > (*it)->position.Y() &&

				(itBullet->position.X() + itBullet->getWidth() / 2) > (*it)->position.X() &&
				(itBullet->position.X() + itBullet->getWidth() / 2) < ((*it)->position.X() + (*it)->getWidth())) {
				itBullet = vaus->bullets.erase(itBullet);
				(*it)->die();
				Score::addToScore((*it)->getValue());

				/* Bonus*/
				if ((*it)->getLives() == 0) {
					if ((*it)->getBonusType() != BonusType::NONE) {
						if (bonuses.size() < 2) {
							bonuses.push_back(new Bonus((*it)->position.X(), (*it)->position.Y(), (*it)->getBonusType()));
						}
					}
				}
			}
			else if (itBullet->position.Y() < 24) {
				itBullet = vaus->bullets.erase(itBullet);
			}
			else {
				itBullet++;
			}
		}



		if ((*it)->getLives() > 0) {
			/* Colisión Pelotas*/
			for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {
				if ((*itBall)->enable()) {

					if (((*itBall)->position.Y() + (*itBall)->getHeight() / 2) >= (*it)->position.Y() &&
						((*itBall)->position.Y() + (*itBall)->getHeight() / 2) <= ((*it)->position.Y() + (*it)->getHeight())) {

						if (((*itBall)->position.X() + (*itBall)->getWidth()) >= (*it)->position.X() &&
							((*itBall)->position.X() + (*itBall)->getWidth()) < ((*it)->position.X() + (*it)->getWidth() / 2)) {
							(*itBall)->invertDirectionHorizontal();
							Sound::playSample(R::Sample::BOUNCE); /// TEST SONIDO --------


							(*it)->die();
							Score::addToScore((*it)->getValue());

							/* Bonus*/
							if ((*it)->getLives() == 0) {
								if ((*it)->getBonusType() != BonusType::NONE) {
									if (bonuses.size() < 2) {
										bonuses.push_back(new Bonus((*it)->position.X(), (*it)->position.Y(), (*it)->getBonusType()));
									}
								}
							}

						}
						else if ((*itBall)->position.X() <= ((*it)->position.X() + (*it)->getWidth()) &&
							(*itBall)->position.X()	> ((*it)->position.X() + (*it)->getWidth() / 2)) {
							(*itBall)->invertDirectionHorizontal();
							Sound::playSample(R::Sample::BOUNCE); /// TEST SONIDO --------

							(*it)->die();
							Score::addToScore((*it)->getValue());
							if ((*it)->getLives() == 0) {
								if ((*it)->getBonusType() != BonusType::NONE && bonuses.size() < 2) {
									bonuses.push_back(new Bonus((*it)->position.X(), (*it)->position.Y(), (*it)->getBonusType()));
								}
							}
						}
					}
					if (((*itBall)->position.X() + (*itBall)->getWidth() / 2) >= (*it)->position.X() &&
						((*itBall)->position.X() + (*itBall)->getWidth() / 2) <= ((*it)->position.X() + (*it)->getWidth())) {

						if (((*itBall)->position.Y() + (*itBall)->getHeight()) >= (*it)->position.Y() &&
							((*itBall)->position.Y() + (*itBall)->getHeight()) < ((*it)->position.Y() + (*it)->getHeight())) {
							(*itBall)->invertDirectionVertical();
							Sound::playSample(R::Sample::BOUNCE); /// TEST SONIDO --------

							(*it)->die();
							Score::addToScore((*it)->getValue());
							if ((*it)->getLives() == 0) {
								if ((*it)->getBonusType() != BonusType::NONE && bonuses.size() < 2) {
									bonuses.push_back(new Bonus((*it)->position.X(), (*it)->position.Y(), (*it)->getBonusType()));
								}
							}
						}
						else if ((*itBall)->position.Y() < ((*it)->position.Y() + (*it)->getHeight()) &&
							(*itBall)->position.Y() > (*it)->position.Y()) {
							(*itBall)->invertDirectionVertical();
							Sound::playSample(R::Sample::BOUNCE); /// TEST SONIDO --------

							(*it)->die();
							Score::addToScore((*it)->getValue());
							if ((*it)->getLives() == 0) {
								if ((*it)->getBonusType() != BonusType::NONE && bonuses.size() < 2) {
									bonuses.push_back(new Bonus((*it)->position.X(), (*it)->position.Y(), (*it)->getBonusType()));
								}
							}
						}
					}
				}
			}
		}

	}
}

void Level::setLevel(int level) {
	actualLevel = level;
}


bool Level::empty() {
	bool isempty = true;
	for (auto it = blocks.begin(); it != blocks.end(); it++) {
		if ((*it)->getType() != BlockType::GOLD) {
			if ((*it)->getLives() > 0) {
				isempty = false;
				break;
			}
		}
	}
	return isempty;
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
	/*Borra los bloques del nivel si es que hay.*/
	for (auto it = blocks.begin(); it != blocks.end(); it++) {
		if (*it) {
			delete (*it);
		}
	}
	blocks.clear();
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
				blocks.push_back(new Block(coordX - 1, coordY, static_cast<BlockType>(type)));
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
		for (size_t i = 1; i <= blocks.size() / 3; i++) { // serán 24 
			randIndex = rand() % blocks.size();
			if (blocks.at(randIndex)->getBonusType() == BonusType::NONE) {
				randType = rand() % 7;
				blocks.at(randIndex)->setBonusType(BonusType(randType));
			}
			else {
				i--;
			}
		}
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
	for (auto it = blocks.begin(); it != blocks.end(); it++) {
		delete (*it);
	}
	clearBonuses();
}
