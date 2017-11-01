#include "Control.hpp"

using namespace std;

void Control::addActionName(ControllableObject::action_t action, string name) {
	association_t association;
	association.action = action;
	association.name = name;
	association.peripheral = NULL;
	association.component = 0;
	associations.push_back(association);
}

void Control::setActionPeripheral(ControllableObject::action_t action, Peripheral* peripheral,
	Peripheral::component_t component, Peripheral::event_t e) {
	for (associationsIter = associations.begin(); associationsIter != associations.end(); associationsIter++) {
		if (associationsIter->action == action) {
			associationsIter->peripheral = peripheral;
			associationsIter->component = component;
			associationsIter->event = e;
			associationsIter->oldEvent = Peripheral::NO_EVENT;
			return;
		}
	}
}

void Control::addAssociation(Control::association_t association) {
	associations.push_back(association);
}

void Control::setOwner(ControllableObject* co) {
	owner = co;
}

ControllableObject* Control::getOwner() const {
	return owner; /* Retorna el apuntador al dueño del control. */
}

void Control::update() {
	int doActionOrder;
	Peripheral::state_t tempState;
	Peripheral::event_t tempOldEvent;
	for (associationsIter = associations.begin(); associationsIter != associations.end(); associationsIter++) {

		tempState = associationsIter->peripheral->getState(associationsIter->component);

		tempOldEvent = associationsIter->oldEvent;
		doActionOrder = false;

		switch (associationsIter->event) {
		case Peripheral::ON_PRESSING:
			if (tempState != INVALID_STATE) {
				doActionOrder = true;
			}
			break;

		case Peripheral::ON_PRESS:
			if ((tempOldEvent == Peripheral::ON_RELEASE) && (tempState != INVALID_STATE)) {
				associationsIter->oldEvent = Peripheral::ON_PRESS;
				doActionOrder = true;
			}
			else if (tempState == INVALID_STATE) {
				associationsIter->oldEvent = Peripheral::ON_RELEASE;
			}
			break;

		case Peripheral::ON_RELEASE:
			if ((tempOldEvent == Peripheral::ON_PRESS) && (tempState == INVALID_STATE)) {
				associationsIter->oldEvent = Peripheral::ON_RELEASE;
				doActionOrder = true;
			}
			else if (tempState != INVALID_STATE) {
				associationsIter->oldEvent = Peripheral::ON_PRESS;
			}
			break;

		case Peripheral::ON_RELEASSING:
			if (tempState == INVALID_STATE) {
				doActionOrder = true;
			}
			break;

		default:
			break;
		}
		if (doActionOrder) {
			owner->doAction(associationsIter->action, tempState);
		}
	}
}

string Control::getNameAction(ControllableObject::action_t action) {
	for (associationsIter = associations.begin(); associationsIter != associations.end(); associationsIter++) {
		if (associationsIter->action == action) {
			return associationsIter->name;
		}
	}
	return "";
}