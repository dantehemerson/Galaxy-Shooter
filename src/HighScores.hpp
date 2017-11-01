#pragma once

#ifndef HIGHSCORES_HPP
#define HIGHSCORES_HPP

#include <vector>

#include "Interface.hpp"
#include "ControllableObject.hpp"

class Application;
class ControlManager;
class ActorManager;
class StageManager;
class Button;
class FileScores;

class HighScores : public Interface, public ControllableObject {
public:
	HighScores(Application* const app);

	virtual void draw() const override;
	virtual void update() override;
	virtual void doAction(action_t action, int magnitute) override;

	int insideButton() const;
	~HighScores();

private:
	ControlManager* controlManager;
	ActorManager* actorManager;
	StageManager* stageManager;

	FileScores* file;
	std::vector<Button*> buttons;
	bool useMouse;
	int index;
	int insideIndex;
};

#endif // !HIGHSCORES_HPP
