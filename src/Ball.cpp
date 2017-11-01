#include "Ball.hpp"

#include <algorithm>
#include <stdio.h>
#include <allegro5\allegro.h>


#include "Gallery.hpp"
#include "Utils.hpp"


using namespace std;

float Ball::velocity = 5;

Ball::Ball(const float& x, const float& y) : Actor(x, y), lives(1), state(BallState::STICKY), stopped(true) {
	direction.setPosition(1, -1);
	generateAngle(30, 32);
	diff = 40;
}

void Ball::draw() const {
	if (lives > 0) {
		al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), 812, 36, 23, 23, position.X(), position.Y(), NULL);
	}
}

void Ball::update() {
	if (enable()) {
		if (!stopped) {
			position += (displacement * direction * velocity);
		}

		if (position.X() <= 88) {
			setDirectionHorizontal(1);
		}
		else if (position.X() + getWidth() >= 615) {
			setDirectionHorizontal(-1);
		}
		if (position.Y() <= 24) {
			setDirectionVertical(1);
		}
	}
}

void Ball::setDirectionHorizontal(int dir) {
	direction.setX(dir);
}

void Ball::generateAngle(int a, int b) {

	int anguloAleatorio = (rand() % (max(a, b) - min(a, b) + 1)) + min(a, b);
	displacement.setX(abs(cos(Utils::degressToRad(anguloAleatorio))));
	displacement.setY(abs(sin(Utils::degressToRad(anguloAleatorio))));
	printf("angle=%d  disp = (%f, %f) degRad = %f\n", anguloAleatorio, displacement.X(), displacement.Y(), Utils::degressToRad(anguloAleatorio));
}
void Ball::setDirectionVertical(int dir) {
	direction.setY(dir);
}

void Ball::invertDirectionHorizontal() {
	direction.setX(direction.X() * -1);
}

void Ball::invertDirectionVertical() {
	direction.setY(direction.Y() * -1);
}

void Ball::setVelocity(float _velocity) {
	velocity = _velocity;
}

bool Ball::enable() const {
	return (lives > 0);
}
float Ball::getWidth() const {
	return 10.0f;
}

float Ball::getHeight() const {
	return 10.0f;
}

void Ball::die() {
	if (lives > 0) {
		lives--;
		if (lives < 0) {
			lives = 0;
		}
	}
}

void Ball::setLives(int value) {
	lives = value;
}

float Ball::getVelocity() const {
	return velocity;
}

void Ball::setStopped(bool value) {
	stopped = value;
}

bool Ball::isStopped() const {
	return stopped;
}

void Ball::setState(BallState value) {
	state = value;
}

BallState Ball::getState() const {
	return state;
}


void Ball::setDiff(float value) {
	diff = value;
}

float Ball::getDiff() const {
	return diff;
}
