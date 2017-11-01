#pragma once

#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "ControllableActor.hpp"

#include <vector>

class Button;
class ControlManager;
class Game;
class Mouse;
class Keyboard;

class Pause : public  ControllableActor {
public:
	Pause(float x, float y, Game* game, Mouse* mouse, Keyboard* keyboard);
	virtual void draw() const override;
	virtual void update() override;
	virtual void doAction(action_t action, int magnitute) override;
	int insideButton();
	void reinit();
	~Pause();

private:
	Game* game;
	Mouse* mouse; // Para poder seleccinar con el mouse.
	Keyboard* keyboard;
	ControlManager* controlM;
	std::vector<Button*> buttons;
	std::vector<Button*>::iterator buttonsIter;
	int index;
	int insideIndex;
	bool useMouse;
};

#endif // !PAUSE_HPP
