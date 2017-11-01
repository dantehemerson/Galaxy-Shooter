#include <allegro5\allegro.h>

#include "Mouse.hpp"

using namespace std;

Mouse::Mouse() {
	if (!al_is_mouse_installed()) {
		al_install_mouse();
	}
	numButtons = al_get_mouse_num_buttons();
	if (numButtons > MAX_BUTTONS_MOUSE) {
		numButtons = MAX_BUTTONS_MOUSE;
	}
	reset();
}

Peripheral::state_t Mouse::getState(Peripheral::component_t component) {
	if ((component >= 1) && (static_cast<unsigned>(component) <= numButtons) && al_mouse_button_down(&mouseState, component)) {
		return true;
	}
	return INVALID_STATE;
}

Peripheral::component_t Mouse::getChange() {
	bool value;
	for (size_t i = 1; i < numButtons; ++i) {
		value = al_mouse_button_down(&mouseState, i);
		if (value != oldState[i]) {
			oldState[i] = value;
			return i;
		}
	}
	return INVALID_COMPONENT;
}

string Mouse::getComponentName(Peripheral::component_t component) {
	string nameComponent;
	switch (component) {
	case MICKEY_LEFT:
		nameComponent = "MICKEY LEFT";
		break;
	case MICKEY_RIGHT:
		nameComponent = "MICKEY RIGHT";
		break;
	case MICKEY_CENTER:
		nameComponent = "MICKEY CENTER";
		break;
	default:
		break;
	}
	return nameComponent;
}

void Mouse::updateLastPosition() {
	lastPosition = Vector2(mouseState.x, mouseState.y);
}

bool Mouse::changedPosition() {
	return ((int(lastPosition.X()) != mouseState.x) && (int(lastPosition.Y()) != mouseState.x));
}

bool Mouse::inside(float x1, float y1, float x2, float y2) const {
	if (mouseState.x >= min(x1, x2) && mouseState.x <= max(x1, x2) &&
		mouseState.y >= min(y1, y2) && mouseState.y <= max(y1, y2)) {
		return true;
	}
	return false;
}

void Mouse::reset() {
	for (size_t i = 0; i < numButtons; ++i) {
		oldState[i] = false;
	}
}

Mouse::~Mouse() {

}