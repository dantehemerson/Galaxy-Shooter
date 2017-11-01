#pragma once

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <list>

#include "Actor.hpp"


class Vaus;
class Bonus;

class Level : public Actor {
public:
	Level(const float& x, const float& y, Vaus* vaus);
	virtual void draw() const override;
	virtual void update() override;

	void setLevel(int level);
	int getLevel() const;

	bool empty();
	void clearBonuses();
	void clearBlocks();

	void show();
	void hide();

	void loadLevel();
	~Level();
private:
	int actualLevel;
	std::list<Bonus*> bonuses;

	Vaus* vaus;
	bool showLvl;
};

#endif // !LEVEL_HPP
