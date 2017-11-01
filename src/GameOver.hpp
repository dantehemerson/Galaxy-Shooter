#pragma once

#ifndef GAME_OVER
#define GAME_OVER

#include "Actor.hpp"
#include "Vector2.hpp"
#include "R.hpp"

class GameOver : public Actor {
public:
	GameOver();

	virtual void draw() const override;
	virtual void update() override;

	bool animationFinish() const;
	void reinit();

	~GameOver();
private:
	Vector2 titlePos;
	Vector2 rectPos;
	int counter;
	float velocity;
	bool finish;
};

#endif // !GAME_OVER
