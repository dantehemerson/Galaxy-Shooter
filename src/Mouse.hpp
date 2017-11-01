#pragma once
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <allegro5\allegro.h>
#include <string>
#include <array>

#include "Peripheral.hpp"
#include "Vector2.hpp"

#define MAX_BUTTONS_MOUSE 5

class Mouse : public Peripheral {
public:
	Mouse();

	/* Identificadores para los botones, se deben llamar a éstos para
	obtener o registrar un estado.*/
	typedef enum buttons {
		MICKEY_LEFT = 1,
		MICKEY_RIGHT,
		MICKEY_CENTER
	};

	virtual state_t getState(component_t component) override;
	virtual component_t getChange() override;
	virtual std::string	 getComponentName(component_t component) override;
	virtual void reset() override;

	/* Actualiza el estado del mouse. */
	inline void poll() {
		al_get_mouse_state(&mouseState);
	}

	inline float getX() const {
		return mouseState.x;
	}
	inline float getY() const {
		return mouseState.y;
	}

	inline float getLastX() const {
		return lastPosition.X();
	}
	inline float getLastY() const {
		return lastPosition.Y();
	}

	/// Esto no debería pertenecer acá pero por el momento lo dejaré aquí. 
	void updateLastPosition();

	/**  Retorna true si lastPosition es diferente de la posición actual del cursor del mouse, es decir
	el cursor se ha movido, false de otro modo.*/
	bool changedPosition();

	/* Retorna true si el cursor mouse se encuentra dentro de la región de coordenadas
	(x1, y1) y (x2, y2), false de otro modo.*/
	bool inside(float x1, float y1, float x2, float y2) const;

	~Mouse();
private:
	std::array<bool, MAX_BUTTONS_MOUSE> oldState;
	ALLEGRO_MOUSE_STATE mouseState;
	unsigned int numButtons;
	Vector2 lastPosition;

};

#endif // !MOUSE_HPP