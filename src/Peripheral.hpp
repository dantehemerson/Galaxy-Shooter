#pragma once
#ifndef PERIPHERAL_HPP
#define PERIPHERAL_HPP

#include <string>

#define INVALID_STATE        -2
#define INVALID_COMPONENT    -3

class Peripheral {
public:
	typedef enum event_t {
		NO_EVENT,
		ON_PRESS,
		ON_RELEASE,
		ON_PRESSING,
		ON_RELEASSING
	};

	typedef int state_t;
	typedef int component_t;

	Peripheral();

	virtual state_t getState(component_t component) = 0;
	virtual component_t getChange() = 0;
	virtual std::string	getComponentName(component_t comp) = 0;
	virtual void reset() = 0;
};

#endif // !PERIPHERAL_HPP