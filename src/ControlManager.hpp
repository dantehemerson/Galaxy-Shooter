#pragma once
#ifndef CONTROLMANAGER_HPP
#define CONTROLMANAGER_HPP

#include <vector>

#include "Control.hpp"
#include "Peripheral.hpp"

#define MAX_PERIPHERALS 5

class ControlManager {
public:
	ControlManager();
	~ControlManager();

	typedef struct {
		Peripheral *peripheral;
		Peripheral::component_t component;
	} change_t;

	change_t getChange();

	int addControl(Control* control);
	int addPeripheral(Peripheral *peripheral);
	Control* getControl(int index);
	Peripheral* getPeripheral(int index);
	void update();
private:
	std::vector<Control*> controls;
	std::vector<Control*>::iterator controlsIter;
	std::vector<Peripheral*> peripherals;
	std::vector<Peripheral*>::iterator peripheralsIter;
	int oldState[MAX_PERIPHERALS];
};

#endif // CONTROLMANAGER_HPP