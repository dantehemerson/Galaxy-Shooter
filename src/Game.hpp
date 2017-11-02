#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include "Interface.hpp"
#include "ControllableObject.hpp"

#include <vector>

class Application;
class ControlManager;
class ActorManager;
class StageManager;
class Level;
class Vaus;
class Border;
class Pause;
class IntroductionLevel;
class GameOver;

class Game : public Interface, public ControllableObject {
public:
	explicit Game(Application*const app);

	virtual void draw() const override;
	virtual void update() override;
	virtual void doAction(action_t action, int magnitute) override;

	void setPause(bool pause);
	void backToMenu();

	void reinit();
	void relive();
	void over();

	Level* getLevel() const;
	~Game();
private:
	ControlManager* controlManager;
	ActorManager* actorManager;
	StageManager* stageManager;
	Level* level;
	Vaus* vaus;
	Pause* pauseGame;
	IntroductionLevel* introLevel;
	GameOver* gameOver;
	bool showIntro;
	bool showGameOver;
	bool pause;
};

#endif // !GAME_HPP

