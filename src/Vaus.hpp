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
	LARGE,
	NORMAL_TO_LARGE,
	LARGE_TO_NORMAL,
	NORMAL_TO_CHARGED,
	CHARGED_TO_NORMAL,
	CHARGED,
	LARGE_TO_CHARGED,
	CHARGED_TO_LARGE,
	DEAD_NORMAL,
	DEAD_LARGE,
	DEAD_CHARGED,
	RELIVE_ANIMATION, // I dont know english
	DEAD // Este no tiene animación solo se llama cuando el paddle muere.
};

enum  VausControl {
	RIGHT_VAUS = 100, /*Para diferenciar*/
	LEFT_VAUS,
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
	std::array<Sprite, 13> sprites;

	int lives;
	float velocity;
};


#endif // !VAUS_HPP
