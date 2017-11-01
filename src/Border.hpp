#pragma once
#ifndef BORDER_HPP
#define BORDER_HPP

#include <vector>

#include "Actor.hpp"

class BorderItem;

class Border : public Actor {
public:
	Border(float x = 0.0f, float y = 0.0f);
	virtual void draw() const override;
	void drawRight() const;
	virtual void update() override;

	~Border();

private:
	std::vector<BorderItem*> items;
	std::vector<BorderItem*> itemsRight;

};

#endif // !BORDER_HPP

