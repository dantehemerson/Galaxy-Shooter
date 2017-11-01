#include "Bullet.hpp"

#include <allegro5\allegro.h>

#include "Gallery.hpp"

float Bullet::velocity = 6; // Velocidad para todas las balas.

Bullet::Bullet(float x, float y) : Actor(x, y) {

}

void Bullet::draw() const {
	if (position.Y() > 0)
		al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), 836, 36, 19, 27, position.X(), position.Y(), NULL);
}

void Bullet::update() {
	position.setY(position.Y() - velocity);
}

float Bullet::getWidth() const {
	return 6;
}

float Bullet::getHeight() const {
	return 14;
}


Bullet::~Bullet() {

}