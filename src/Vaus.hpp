#pragma once

#ifndef VAUS_HPP
#define VAUS_HPP

#include "ControllableActor.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"

#include <array>
#include <list>
#include <vector>

enum class VausState : size_t {
	NORMAL = 0,
	DEAD // Este no tiene animación solo se llama cuando el paddle muere.
};

enum  VausControl {
	RIGHT_VAUS = 100, /*Para diferenciar*/
	LEFT_VAUS,
	UP_SHIP,
	DOWN_SHIP,
	SHOT
};

class Game;

class Vaus : public ControllableActor {
public:
	Vaus(const float& x, const float& y, Game* g);

	virtual void draw() const override;
	virtual void update() override;
	virtual void doAction(action_t action, int magnitute) override;

	float getWidth() const;
	float getHeight() const;
	void verifyLimits();

	/* Elimina todas las balas en la lista bullets. */
	void clearBullets();

	bool isDead() const;

	void setState(VausState state);
	VausState getState() const;

	void setLives(int value);
	int getLives() const;



	std::list<Bullet> bullets; /* (:hail_dante*) */
private:
	Game* game;
	VausState state;
	std::array<Sprite, 2> sprites;

	int lives;
	float velocity;
};


#endif // !VAUS_HPP
