#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include <vector>

#include "Interface.hpp"
#include "ControllableObject.hpp"

class Application;
class Button;
class ControlManager;
class ActorManager;
class StageManager;

class Menu : public Interface, public ControllableObject {
public:
	Menu(Application*const app);

	virtual void draw() const override;
	virtual void update() override;

	/* Esta función es llamada por el administrador de controles si la acción fue registrada
	previamente.*/
	virtual void doAction(ControllableObject::action_t action, int magnitute) override;

	int insideButton() const;

	~Menu();

private:
	ControlManager* controlManager;
	ActorManager* actorManager;
	StageManager* stageManager;

	std::vector<Button*> buttons;
	std::vector<Button*>::iterator buttonsIter;
	int index;
	int insideIndex;
	bool useMouse;

};
#endif // !MENU_HPP
