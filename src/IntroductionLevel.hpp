#pragma once

#ifndef INTRODUCTIONLEVEL_HPP
#define INTRODUCTIONLEVEL_HPP

#include "Actor.hpp"
#include "Vector2.hpp"
#include "R.hpp"

class Level;

class IntroductionLevel : public Actor {
public:
	IntroductionLevel(Level* level);

	virtual void draw() const override;
	virtual void update() override;

	bool animationFinish() const;
	void reinit(bool initGame = false);
	void setStart(bool value);

	~IntroductionLevel();
private:
	Level* level;
	Vector2 titlePos;
	Vector2 rectPos;
	int counter;
	int alpha;
	int counterStart;
	int loadLevelCounter;
	bool initLLC;

	static const int waitTime;
	static const int animationStart;
	bool isStart;
	float velocity;
	int velocityAnimationAlpha;
	bool finish;
};

#endif // !INTRODUCTIONLEVEL_HPP
