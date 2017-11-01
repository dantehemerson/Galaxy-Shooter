#pragma once

#ifndef FRAME_HPP
#define FRAME_HPP

#include "Actor.hpp"
#include "R.hpp"

class Frame : public Actor {
public:
	Frame(Actor* owner, R::Image idImage, const float sx, const float sy,
		const float width, const float height, int ticks, bool invert = false, const float xDesp = 0.0f, const float yDesp = 0.0F);

	virtual void draw() const override;
	virtual void update() override;

	float getWidth() const;
	int getTicks() const;

private:
	Actor* owner;
	R::Image image;
	float sx;
	float sy;
	float width;
	float height;
	int ticks;
	bool invert;
	float xDesp;
	float yDesp;

};
#endif // !FRAME_HPP
