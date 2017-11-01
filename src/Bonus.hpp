#pragma once
#ifndef BONUS_HPP
#define BONUS_HPP

#include "Actor.hpp"
#include "Sprite.hpp"


enum class BonusType : unsigned { E, C, S, P, L, D, B, NONE };

class Bonus : public Actor {
public:
	Bonus(float x, float y, BonusType type);
	virtual void draw() const override;
	virtual void update() override;

	// Retorna el ancho y alto.
	float getWidth() const;
	float getHeight() const;

	// Retorna el tipo.
	BonusType getType() const;

private:
	void initType();

	Sprite sprite;	// Sprite para la animación de la aspirina(no sé como llamarlo).
	BonusType type;	// Tipo de la aspirina.
	static const float velocity; // La velocidad es constante para todos
};

#endif // !BONUS_HPP
