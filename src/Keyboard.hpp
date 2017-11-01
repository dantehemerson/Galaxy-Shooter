#pragma once

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <allegro5\allegro.h>

#include "Peripheral.hpp"

class Keyboard : public	 Peripheral {
public:
	Keyboard();


	virtual state_t getState(component_t component) override;
	virtual component_t getChange() override;
	virtual std::string getComponentName(component_t component) override;
	virtual void reset() override;
	/* Actualiza el el etado del teclado y lo almacena en keyboardState.*/
	inline void poll() {
		al_get_keyboard_state(&keyboardState);
	}
	~Keyboard();

private:
	bool oldState[ALLEGRO_KEY_MAX]; /* Almacena los estados de todas las teclas.*/
	ALLEGRO_KEYBOARD_STATE keyboardState;
};

#endif // !KEYBOARD_HPP