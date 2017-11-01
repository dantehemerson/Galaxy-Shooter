#pragma once

#ifndef HELP_HPP
#define HELP_HPP

#include <allegro5\allegro.h>

#include <vector>

#include "Interface.hpp"
#include "ControllableObject.hpp"
#include "Vector2.hpp"

class Application;
class ControlManager;
class ActorManager;
class StageManager;
class Button;

class Help : public Interface, public ControllableObject {
public:
	Help(Application* const app);

	virtual void draw() const override;
	virtual void update() override;
	virtual void doAction(action_t action, int magnitute) override;

	void helpPosition();
	int insideButton() const;
	void drawItems();
	~Help();

private:
	ControlManager* controlManager;
	ActorManager* actorManager;
	StageManager* stageManager;
	ALLEGRO_BITMAP* itemsBMP;

	std::vector<Button*> buttons;
	Vector2 positionItemsBMP;

	bool useMouse;
	int index;
	int insideIndex;
	float difference;
	float velocityScroll;
	bool showArrowTop;
	bool showArrowBottom;

};

#endif // !HELP_HPP
