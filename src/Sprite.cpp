#include "Sprite.hpp"

#include "Actor.hpp"

Sprite::Sprite(Actor* owner) : owner(owner) {
	actualFrame = 0;
	actualTick = 0;
	repeat = false;
	finish = true;
}

void Sprite::draw() const {
	frames.at(actualFrame).draw();
}

void Sprite::update() {
	if (frames.size() <= 1) return;

	if (actualTick > frames.at(actualFrame).getTicks()) {
		actualTick = 0;
		actualFrame++;
		if (actualFrame >= static_cast<int>(frames.size())) {
			/* si repeat = false, Se queda en el ultimo frame, de lo contrario vuelve al primer frame.*/
			//finish = actualFrame = repeat ? 0 : frames.size() - 1;
			actualFrame = repeat ? 0 : frames.size() - 1;
			if (!repeat) {
				finish = true;
			}
		}
		else {
			static int dif;
			dif = frames.at(actualFrame - 1).getWidth() - frames.at(actualFrame).getWidth();
			owner->position.setX(owner->position.X() + dif / 2);

		}
	}
	else {
		actualTick++;
	}
}

void Sprite::setOwner(Actor* actor) {
	owner = actor;
}

void Sprite::setRepeat(bool _repeat) {
	repeat = _repeat;
}

void Sprite::reinit() {
	// Se reinician los valores de los contadores y las variables.
	actualTick = 0;
	actualFrame = 0;
	finish = false;
}

float Sprite::getWidth() const {
	return frames.at(actualFrame).getWidth();

}
bool Sprite::animationFinish() const {
	return finish;
}
void Sprite::addFrame(R::Image idImage, const float sx, const float sy, const float width,
	const float height, int ticks, bool invert, const float xDesp, const float yDesp) {
	Frame frame(owner, idImage, sx, sy, width, height, ticks, invert, xDesp, yDesp);
	frames.push_back(frame);
}

void Sprite::setActualTick(int indexTick) {
	actualTick = indexTick;
}

void Sprite::setActualFrame(int indexFrame) {
	actualFrame = indexFrame;
}

Sprite::~Sprite() {
	frames.clear();
}