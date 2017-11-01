#pragma once

#ifndef BALL_HPP
#define BALL_HPP

#include "Actor.hpp"
#include "Vector2.hpp"

enum class BallState { NORMAL, STICKY };

class Ball : public Actor {
public:
	Ball(const float& x, const float& y);

	virtual void draw() const override;
	virtual void update() override;

	// Establece y retorna la velocidad.
	void setVelocity(float velocity);
	float getVelocity() const;

	float getWidth() const;
	float getHeight() const;

	void setDirectionVertical(int dir);
	void setDirectionHorizontal(int dir);

	// Invierte la dirección en la que se mueve la pelota.
	void invertDirectionVertical();
	void invertDirectionHorizontal();

	void generateAngle(int a, int b);

	// Resta una vida
	void die();

	void setStopped(bool value);
	bool isStopped() const;

	void setState(BallState value);
	BallState getState() const;

	void setDiff(float value);
	float getDiff() const;

	// True si las vidas(lives) es 1, False de otro modo.
	bool enable() const;

	void setLives(int value);

private:
	Vector2 displacement; // Vector Desplazamiento.
	Vector2 direction; // Dirección de la pelota(horizontal y vertical).
	static float velocity; // Para todos las pelotas es la misma velocidad.
	int lives; // 1 ó 0. Si es 1 entonces la pelota se muestra, de lo contrario no se muestra.
	BallState state;
	bool stopped;
	float diff;
};

#endif // !BALL_HPP
