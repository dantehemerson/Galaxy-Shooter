#include "Frame.hpp"

#include "Gallery.hpp"

Frame::Frame(Actor* _owner, R::Image _idImage, const float _sx, const float _sy,
	const float _width, const float _height, int _ticks, bool _invert, const float _xDesp, const float _yDesp) :
	owner(_owner),
	image(_idImage),
	sx(_sx),
	sy(_sy),
	width(_width),
	height(_height),
	ticks(_ticks),
	invert(_invert),
	xDesp(_xDesp),
	yDesp(_yDesp) {


}

void Frame::draw() const {
	al_draw_bitmap_region(Gallery::getSingleton().getImage(image), sx, sy,
		width, height, owner->position.X() + xDesp, owner->position.Y() + yDesp, NULL);

	if (invert) {
		al_draw_bitmap_region(Gallery::getSingleton().getImage(image), sx, sy,
			width, height, owner->position.X() + width + xDesp, owner->position.Y() + yDesp, ALLEGRO_FLIP_HORIZONTAL);
	}
}

void Frame::update() {

}

int Frame::getTicks() const {
	return ticks;
}

float Frame::getWidth() const {
	return width * (invert ? 2 : 1); // Si es invert entonces sería el doble de ancho
}