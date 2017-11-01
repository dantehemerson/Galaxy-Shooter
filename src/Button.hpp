#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <allegro5\allegro_font.h>

#include <string>

#include "Actor.hpp"
#include "R.hpp"

/** 384 x 47 dimensión del background - 390 */

enum class ButtonType { NORMAL, MEDIUM, SMALL, GITHUB };

class Button : public Actor {
public:
	Button(float x, float y, const std::string& text, ButtonType type = ButtonType::NORMAL);

	virtual void draw() const override;
	virtual void update() override;

	// Establece el texto del botón.
	void setText(const std::string& text);

	bool isFocused() const;
	void isFocused(bool value);

	// Funciónes que retornan los puntos del area que ocupa para saber si el mouse esta dentro.
	float getXInit() const;
	float getYInit() const;
	float getYEnd() const;
	float getXEnd() const;

private:
	std::string text;
	ALLEGRO_COLOR textColor;
	ALLEGRO_COLOR textColorFocused;
	int alignment;
	bool focused;
	ButtonType type;
	R::Image imageBackground; // Id de la imagen de fondo.
	R::Image imageFocused;	// Id de la imagen de fondo en foco.
	int width; // Es  el ancho/2 de la imagen
};

#endif // !BUTTON_HPP
