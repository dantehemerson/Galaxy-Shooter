#pragma once
#ifndef CONTROLLABLEOBJECT_HPP
#define CONTROLLABLEOBJECT_HPP

class ControllableObject {
public:
	typedef short action_t;
	virtual void doAction(action_t action, int magnitute) = 0;
};

#endif // !CONTROLLABLEOBJECT_HPP