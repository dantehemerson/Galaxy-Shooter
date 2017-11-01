#include <vector>

#include "ControlManager.hpp"

ControlManager::ControlManager() {
	for (int i = 0; i < MAX_PERIPHERALS; i++) {
		oldState[i] = false;
	}
}

int ControlManager::addControl(Control* control) {
	controls.push_back(control);
	return controls.size() - 1; /* Posición en la que se almancenó. */
}

int ControlManager::addPeripheral(Peripheral* peripheral) {
	peripherals.push_back(peripheral);
	return peripherals.size() - 1;	/* Posición en la que se almancenó. */
}

Control* ControlManager::getControl(int index) {
	return controls.at(index);
}

Peripheral* ControlManager::getPeripheral(int index) {
	return peripherals.at(index);
}

ControlManager::change_t ControlManager::getChange() {
	change_t ret;
	Peripheral::component_t comp;
	int pos = 0;

	for (peripheralsIter = peripherals.begin(); peripheralsIter != peripherals.end(); peripheralsIter++) {
		pos++;
		comp = (*peripheralsIter)->getChange();
		if (comp != INVALID_COMPONENT) {
			ret.component = comp;
			ret.peripheral = *peripheralsIter;
			oldState[pos] = true;
		}
		else {
			oldState[pos] = false;
		}
	}
	return ret;
}

void ControlManager::update() {
	for (controlsIter = controls.begin(); controlsIter != controls.end(); controlsIter++) {
		(*controlsIter)->update();
	}
}

ControlManager::~ControlManager() {
	for (peripheralsIter = peripherals.begin(); peripheralsIter != peripherals.end(); peripheralsIter++) {
		if (*peripheralsIter) {
			//			delete(*peripheralsIter);
			/* El teclado no se borra esta declarado en Application y se elimina ante.*/
		}
	}
	for (controlsIter = controls.begin(); controlsIter != controls.end(); controlsIter++) {
		delete(*controlsIter);
	}
}
