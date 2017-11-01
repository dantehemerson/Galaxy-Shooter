#pragma once
#ifndef BULLET_HPP
#define BULLET_HPP

#include "Actor.hpp"

class Bullet : public Actor {
public:
	Bullet(float x, float y);

	virtual void draw() const override;
	virtual void update() override;

	float getWidth() const;
	float getHeight() const;

	~Bullet();
private:
	static float velocity;
};

#endif // !BULLET_HPP
