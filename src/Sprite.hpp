#pragma once

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <allegro5\allegro.h>

#include <vector>

#include "Frame.hpp"

class Actor;

class Sprite {
public:
	Sprite(Actor* owner = nullptr);
	void draw()	const;
	void update();

	void reinit();

	/* True si la animación a finalizado, False de otro modo. Esto solo funciona
	si repeat es false.*/
	bool animationFinish() const;
	/* Establece el dueño del sprite, esto es principalmente para obtener la posición
	en la que se pintará el sprite. */
	void setOwner(Actor* owner);

	/*Establece si el sprite se repite en bucles. */
	void setRepeat(bool repeat);

	/* Recibe los datos para un nuevo frame y añade al vector de frames. */
	void addFrame(R::Image idImage, const float sx, const float sy, const float width,
		const float height, int ticks, bool invert = false, const float xDesp = 0.0f, const float yDesp = 0.0f);

	void setActualTick(int tick);
	void setActualFrame(int frame);

	/* Retorna el ancho del frame actual.*/
	float getWidth() const;

	~Sprite();

private:
	Actor* owner;
	std::vector<Frame> frames;
	int actualTick;
	int actualFrame;
	bool repeat;
	bool finish;
};

#endif // !SPRITE_HPP
