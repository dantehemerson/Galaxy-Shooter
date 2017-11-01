#pragma once

#ifndef BORDERITEM_HPP
#define BORDERITEM_HPP

#include "Actor.hpp"


class BorderItem : public Actor {
public:
	BorderItem(float x, float y, short type);

	virtual void draw() const override;
	virtual void update() override;

	~BorderItem();

private:
	short type;
	float sx; // Posicion x en la imagen
	float sy; // Posicion y en la imagen
	float sw; // Ancho 
	float sh; // Alto
};

#endif //!BORDERITEM_HPP