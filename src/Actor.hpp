#pragma once
#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "Vector2.hpp"

class Actor {
public:
	explicit Actor(const float& x = 0.0f, const float& y = 0.0f);
	virtual void draw() const = 0;
	virtual void update() = 0;

	virtual ~Actor();

	/* Este dato es publica para poder realizar las operaciones.*/
	Vector2 position;
private:

};

#endif // !ACTOR_HPP
