#pragma once
#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <list>
#include <string>

#include "Peripheral.hpp"
#include "ControllableObject.hpp"

class Control {
public:
	typedef struct {
		ControllableObject::action_t action;
		std::string name;
		Peripheral *peripheral;
		Peripheral::component_t component;
		Peripheral::event_t oldEvent;
		Peripheral::event_t event;
	} association_t;

	void addActionName(ControllableObject::action_t action, std::string name);
	void addAssociation(association_t association);
	void setActionPeripheral(ControllableObject::action_t action, Peripheral* peripheral,
		Peripheral::component_t component, Peripheral::event_t event);
	void setOwner(ControllableObject*);
	ControllableObject* getOwner() const;
	void update();
	std::string getNameAction(ControllableObject::action_t);
	void reset();
private:
	ControllableObject *owner;
	std::list<association_t> associations;
	std::list<association_t>::iterator associationsIter;

};

#endif // !CONTROL_HPP