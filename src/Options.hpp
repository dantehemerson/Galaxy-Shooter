#pragma once

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <vector>

#include "Interface.hpp"
#include "ControllableObject.hpp"

class Application;
class ControlManager;
class ActorManager;
class StageManager;
class Button;
class ConfigFile;

class Options : public Interface, public ControllableObject {
public:
	Options(Application* const app);

	virtual void draw() const override;
	virtual void update() override;
	virtual void doAction(action_t action, int magnitute) override;

	int insideButton() const;
	~Options();

private:
	ControlManager* controlManager;
	ActorManager* actorManager;
	StageManager* stageManager;
	ConfigFile* configuration;

	std::vector<Button*> buttons;
	bool useMouse;
	int index;
	int insideIndex;
};

#endif // !OPTIONS_HPP
