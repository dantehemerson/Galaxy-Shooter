#include "Bonus.hpp"

const float Bonus::velocity = 1.5;

Bonus::Bonus(float x, float y, BonusType type) : Actor(x, y), type(type) {
	sprite.setOwner(this);
	initType();
}

void Bonus::draw() const {
	sprite.draw();
}

void Bonus::update() {
	sprite.update();

	// Va cayendo
	if (position.Y() < 630) {
		position.setY(position.Y() + velocity);
	}

}

BonusType Bonus::getType() const {
	return type;
}

void Bonus::initType() {
	int ticks = 4;
	sprite.setRepeat(true);
	switch (type) {
	case BonusType::E:
		sprite.addFrame(R::Image::ITEMS, 0, 350, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 44, 350, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 88, 350, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 132, 350, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 176, 350, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 220, 350, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 264, 350, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 308, 350, 44, 22, ticks);
		break;
	case BonusType::C:
		sprite.addFrame(R::Image::ITEMS, 0, 374, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 44, 374, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 88, 374, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 132, 374, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 176, 374, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 220, 374, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 264, 374, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 308, 374, 44, 22, ticks);
		break;
	case BonusType::S:
		sprite.addFrame(R::Image::ITEMS, 0, 398, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 44, 398, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 88, 398, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 132, 398, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 176, 398, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 220, 398, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 264, 398, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 308, 398, 44, 22, ticks);
		break;
	case BonusType::P:
		sprite.addFrame(R::Image::ITEMS, 0, 542, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 44, 542, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 88, 542, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 132, 542, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 176, 542, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 220, 542, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 264, 542, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 308, 542, 44, 22, ticks);
		break;
	case BonusType::L:
		sprite.addFrame(R::Image::ITEMS, 0, 326, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 44, 326, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 88, 326, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 132, 326, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 176, 326, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 220, 326, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 264, 326, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 308, 326, 44, 22, ticks);
		break;
	case BonusType::D:
		sprite.addFrame(R::Image::ITEMS, 0, 470, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 44, 470, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 88, 470, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 132, 470, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 176, 470, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 220, 470, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 264, 470, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 308, 470, 44, 22, ticks);
		break;
	case BonusType::B:
		sprite.addFrame(R::Image::ITEMS, 0, 494, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 44, 494, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 88, 494, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 132, 494, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 176, 494, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 220, 494, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 264, 494, 44, 22, ticks);
		sprite.addFrame(R::Image::ITEMS, 308, 494, 44, 22, ticks);
		break;
	default:
		break;
	}
}

float Bonus::getWidth() const {
	return 44;
}

float Bonus::getHeight() const {
	return 22;
}