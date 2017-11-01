#include <iostream>

#include "Keyboard.hpp"

using namespace std;

Keyboard::Keyboard() {
	/* LLama a la función para iniciar el teclado si es que aún no está instalado. */
	if (!al_is_keyboard_installed()) {
		if (!al_install_keyboard()) {
			cerr << "No se pudo instalar el teclado.\n";
		}
	}
	/* Obtiene el estado del teclado y sus componentes */
	al_get_keyboard_state(&keyboardState);
	for (int i = 1; i < ALLEGRO_KEY_MAX; i++) {
		oldState[i] = al_key_down(&keyboardState, i);
	}
}

/*La variable component representa el keycode definido en @file allegro5/keycodes.h */
Peripheral::state_t Keyboard::getState(state_t component) {
	if ((component >= 0) && (component < ALLEGRO_KEY_MAX) && al_key_down(&keyboardState, component)) {
		//reset();
		return true;
	}
	else {
		return INVALID_STATE;
	}
}

/* Detecta si hubo cambio con respecto al evento anterior que tuvo el teclado */
Peripheral::component_t Keyboard::getChange() {
	bool value;
	for (int i = 1; i < ALLEGRO_KEY_MAX; ++i) {
		value = al_key_down(&keyboardState, i);
		if (value != oldState[i]) {
			oldState[i] = value;
			//reset();

			return i;
		}
	}
	return INVALID_COMPONENT;
}

void Keyboard::reset() {

	for (int i = 1; i < ALLEGRO_KEY_MAX; ++i) {
		oldState[i] = false;
	}
}

string Keyboard::getComponentName(component_t component) {
	string nameKeyCode(al_keycode_to_name(component));
	return nameKeyCode;
}

Keyboard::~Keyboard() {

}