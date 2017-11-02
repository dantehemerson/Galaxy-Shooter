#include "Game.hpp"

#include <vector>
#include <iostream>

#include "Application.hpp"
#include "ControlManager.hpp"
#include "ActorManager.hpp"
#include "StageManager.hpp"
#include "Gallery.hpp"
#include "Level.hpp"
#include "Frame.hpp"
#include "Vaus.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Pause.hpp"
#include "IntroductionLevel.hpp"
#include "Score.hpp"
#include "GameOver.hpp"

using namespace std;

Game::Game(Application*const app) : Interface(app),
controlManager(nullptr),
actorManager(nullptr),
stageManager(nullptr),
level(nullptr),
pauseGame(nullptr),
pause(false),
showIntro(true),
showGameOver(false) {
	controlManager = new ControlManager();
	actorManager = new ActorManager();
	stageManager = new StageManager(actorManager);

	gameOver = new GameOver;
	vaus = new Vaus(520, 200, this);

	// Control para el Paddle(nave vaus)
	Control* controlVaus = new Control;
	controlVaus->addActionName(VausControl::LEFT_VAUS, "Izquierda Vaus");
	controlVaus->addActionName(VausControl::RIGHT_VAUS, "Derecha Vaus");
	controlVaus->addActionName(VausControl::SHOT, "Disparando");
	controlVaus->setActionPeripheral(VausControl::LEFT_VAUS, app->getKeyboard(), ALLEGRO_KEY_LEFT, Peripheral::ON_PRESSING);
	controlVaus->setActionPeripheral(VausControl::RIGHT_VAUS, app->getKeyboard(), ALLEGRO_KEY_RIGHT, Peripheral::ON_PRESSING);
	controlVaus->setActionPeripheral(VausControl::SHOT, app->getKeyboard(), ALLEGRO_KEY_X, Peripheral::ON_PRESS);
	controlVaus->setOwner(vaus);

	Control* controlGame = new Control;
	controlGame->addActionName(ActionMenu::BACKSPACE, "Atras");
	controlGame->addActionName(ActionMenu::ESCAPE, "Escape");
	controlGame->setActionPeripheral(ActionMenu::BACKSPACE, app->getKeyboard(), ALLEGRO_KEY_BACKSPACE, Peripheral::ON_PRESS);
	controlGame->setActionPeripheral(ActionMenu::ESCAPE, app->getKeyboard(), ALLEGRO_KEY_ESCAPE, Peripheral::ON_PRESS);
	controlGame->setOwner(this);

	controlManager->addControl(controlGame);
	controlManager->addControl(controlVaus);
	controlManager->addPeripheral(app->getKeyboard());



	level = new Level(64 + 24, 24, vaus);
	introLevel = new IntroductionLevel(level);

	actorManager->add(level);

	actorManager->add(new Score);

	pauseGame = new Pause(100, 100, this, app->getMouse(), app->getKeyboard());

	actorManager->add(vaus);

	level->setLevel(1);
}

void Game::draw() const {
	static Gallery& gallery = Gallery::getSingleton();
	static auto fSmall = gallery.getFont(R::Font::VENUS_SMALL);
	static auto f = gallery.getFont(R::Font::VENUS_20);
	static auto fBig = gallery.getFont(R::Font::VENUS_TITLES);

	/* Fondo */
	al_draw_bitmap(gallery.getImage(R::Image::BACKGROUND1), 0, 0, NULL);
}

void Game::update() {
	stageManager->update();
	if (showGameOver) {
		gameOver->draw();
		gameOver->update();
		if (gameOver->animationFinish()) {
			// Finaliza el juego
			backToMenu();
		}
	}
	else if (showIntro) {
		vaus->position.setPosition(305, vaus->position.Y());
		introLevel->draw();
		introLevel->update();
		if (introLevel->animationFinish()) {
			showIntro = false;
		}
	}
	else {
		if (!pause) {
			controlManager->update();
			actorManager->update();
		}
		else {
			pauseGame->draw();
			pauseGame->update();
		}
	}


	// Comprobando si el nivel esta terminado( cuando no queda ningun bloque, excepto los de tipo GOLD)
	if (level->empty()) {
		level->setLevel(level->getLevel() + 1);
		level->loadLevel();
		introLevel->reinit();
		showIntro = true;
		showGameOver = false;

		relive();
		introLevel->setStart(true);
		level->hide();
	}

}

void Game::relive() {
	vaus->position.setPosition(305, vaus->position.Y());
	vaus->clearBullets();
	level->clearBonuses();

}

void Game::doAction(action_t action, int magnitute) {
	switch (action) {
	case ActionMenu::BACKSPACE:
	case ActionMenu::ESCAPE:
		setPause(true);
		break;
	}
}


void Game::setPause(bool value) {
	pause = value;
}

void Game::backToMenu() {
	app->setInterface(Application::INTERFACE_SCREEN::MAIN_MENU);
}

Level* Game::getLevel() const {
	return this->level;
}

void Game::reinit() {
	level->setLevel(1);
	level->loadLevel();

	//* Inicia un nuevo nivel.
	introLevel->setStart(true);
	level->hide();

	vaus->setLives(5); // Inicia con 4 vidas todo el juego.
	setPause(false);
	Score::setScore(0x000);
	relive();
	introLevel->reinit(true);

}

void Game::over() {
	showIntro = false;
	showGameOver = true;
	gameOver->reinit();
}

Game::~Game() {
	delete controlManager;
	delete actorManager;
	std::cout << "Pase el error actor manager" << std::endl;
	delete stageManager;
	delete pauseGame;
	delete introLevel;
}
