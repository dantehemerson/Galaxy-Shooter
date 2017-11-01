#include "Button.hpp"

#include <allegro5\allegro_font.h>

#include "Gallery.hpp"

using namespace std;


Button::Button(float x, float y, const string& text, ButtonType type) : Actor(x, y), text(text),
alignment(ALLEGRO_ALIGN_CENTER),
focused(false),
type(type)
{
	switch (type) {
	case ButtonType::MEDIUM:
		imageBackground = R::Image::BUTTON_MEDIUM;
		imageFocused = R::Image::BUTTON_MEDIUM_FOCUSED;
		textColor = R::Color::BUTTON_FOCUSED;
		width = 134;
		break;
	case ButtonType::SMALL:
		imageBackground = R::Image::BUTTON_SMALL;
		imageFocused = R::Image::BUTTON_SMALL_FOCUSED;
		textColor = R::Color::BUTTON_FOCUSED;
		width = 73;
		break;
	case ButtonType::GITHUB: // Es Medium
		imageBackground = R::Image::BUTTON_GITHUB;
		imageFocused = R::Image::BUTTON_MEDIUM_FOCUSED;
		textColor = R::Color::GITHUB;
		width = 134;
		break;
	default:  /*Para normal y cualquier otro.*/
		imageBackground = R::Image::BUTTON;
		imageFocused = R::Image::BUTTON_FOCUSED;
		textColor = R::Color::BUTTON_FOCUSED;
		width = 192;
		break;
	}
	textColorFocused = R::Color::WHITE;
}

void Button::draw() const {
	if (focused) {
		al_draw_bitmap(Gallery::getSingleton().getImage(imageFocused), getXInit(), position.Y() - 16, NULL);
		al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), textColorFocused, position.X(), position.Y() - 3, alignment, text.c_str());
	}
	else {
		al_draw_bitmap(Gallery::getSingleton().getImage(imageBackground), getXInit(), position.Y() - 16, NULL);
		al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_18), textColor, position.X(), position.Y(), alignment, text.c_str());
	}
}

void Button::update() {

}

void Button::setText(const string& _text) {
	text = _text;
}

bool Button::isFocused()  const {
	return focused;
}

void Button::isFocused(bool value) {
	focused = value;
}

float Button::getXInit() const {
	return position.X() - width;
}

float Button::getYInit() const {
	return position.Y() - 14;
}

float Button::getXEnd() const {
	return position.X() + width;
}

float Button::getYEnd() const {
	return position.Y() + 28;
}