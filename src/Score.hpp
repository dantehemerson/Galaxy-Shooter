#pragma once
#ifndef SCORE_HPP
#define SCORE_HPP

#include "Actor.hpp"
class Score : public Actor {
public:

	Score();
	virtual void draw() const override;
	virtual void update() override;

	static void addToScore(int value);
	static void setScore(int score);
	static int getScore();

	virtual ~Score();

private:
	static int scorePlayer;
};
#endif // !SCORE_HPP
