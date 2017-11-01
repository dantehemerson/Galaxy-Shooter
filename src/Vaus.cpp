#include "Vaus.hpp"

#include "Mouse.hpp"
#include "Ball.hpp"
#include "Bullet.hpp"
#include "Gallery.hpp"
#include "Game.hpp"
#include "Sound.hpp"
#include "Level.hpp"

Vaus::Vaus(const float& x, const float& y, Mouse* mouseControl, std::vector<Ball*>* _balls, Game* g) : game(g),
mouse(mouseControl),
state(VausState::NORMAL),
velocity(6),
useMouse(false),
balls(_balls),
lives(4) {
	position.setPosition(x, y);
	for (auto it = sprites.begin(); it != sprites.end(); it++) {
		it->setOwner(this);
		it->reinit();
	}
	int ticks = 9;
	int ticksL = 1;
	// Añadiendo frames a la animación normal. 44,22
	sprites[static_cast<size_t>(VausState::NORMAL)].setRepeat(true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 0, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 22, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 44, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 66, 44, 22, ticks, true); //
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 44, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL)].addFrame(R::Image::PADDLE, 0, 22, 44, 22, ticks, true);

	// Large	66, 22
	sprites[static_cast<size_t>(VausState::LARGE)].setRepeat(true);
	sprites[static_cast<size_t>(VausState::LARGE)].addFrame(R::Image::PADDLE, 0, 88, 66, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE)].addFrame(R::Image::PADDLE, 0, 110, 66, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE)].addFrame(R::Image::PADDLE, 0, 132, 66, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE)].addFrame(R::Image::PADDLE, 0, 154, 66, 22, ticks, true); //
	sprites[static_cast<size_t>(VausState::LARGE)].addFrame(R::Image::PADDLE, 0, 132, 66, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE)].addFrame(R::Image::PADDLE, 0, 110, 66, 22, ticks, true);

	// NormalToLarge 
	sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].addFrame(R::Image::PADDLE, 0, 0, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].addFrame(R::Image::PADDLE, 210, 132, 46, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].addFrame(R::Image::PADDLE, 206, 110, 50, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].addFrame(R::Image::PADDLE, 202, 88, 54, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].addFrame(R::Image::PADDLE, 198, 66, 58, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].addFrame(R::Image::PADDLE, 196, 44, 60, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].addFrame(R::Image::PADDLE, 194, 22, 62, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].addFrame(R::Image::PADDLE, 192, 0, 64, 22, ticksL, true);

	sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].addFrame(R::Image::PADDLE, 192, 0, 64, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].addFrame(R::Image::PADDLE, 194, 22, 62, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].addFrame(R::Image::PADDLE, 196, 44, 60, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].addFrame(R::Image::PADDLE, 198, 66, 58, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].addFrame(R::Image::PADDLE, 202, 88, 54, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].addFrame(R::Image::PADDLE, 206, 110, 50, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].addFrame(R::Image::PADDLE, 210, 132, 46, 22, ticksL, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].addFrame(R::Image::PADDLE, 0, 0, 44, 22, ticks, true);

	ticks = 1;
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 0, 0, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 88, 22, 40, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 88, 44, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 88, 66, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 88, 88, 34, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 88, 110, 32, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 88, 132, 30, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 2, 176, 30, 22, ticks, true);// Charged
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 1, 198, 31, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 0, 220, 32, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 34, 176, 34, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 33, 198, 35, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 32, 220, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 70, 176, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 69, 198, 37, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 68, 220, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 108, 176, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 107, 198, 39, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 106, 220, 40, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 148, 176, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 148, 198, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].addFrame(R::Image::PADDLE, 146, 220, 44, 22, ticks, true);


	// Charged to normal es lo mismo que normal To charged pero en orden inverso, ojo esto podria mejorarse si 
	// se crea una función para ir de adelante hacia atras en el sprite.
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 146, 220, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 148, 198, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 148, 176, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 106, 220, 40, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 107, 198, 39, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 108, 176, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 68, 220, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 69, 198, 37, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 70, 176, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 32, 220, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 33, 198, 35, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 34, 176, 34, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 0, 220, 32, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 1, 198, 31, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 2, 176, 30, 22, ticks, true);// Charged
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 88, 132, 30, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 88, 110, 32, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 88, 88, 34, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 88, 66, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 88, 44, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 88, 22, 40, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].addFrame(R::Image::PADDLE, 0, 0, 44, 22, ticks, true);

	// CHARGED
	ticks = 9;
	sprites[static_cast<size_t>(VausState::CHARGED)].setRepeat(true);
	sprites[static_cast<size_t>(VausState::CHARGED)].addFrame(R::Image::PADDLE, 44, 0, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED)].addFrame(R::Image::PADDLE, 44, 22, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED)].addFrame(R::Image::PADDLE, 44, 44, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED)].addFrame(R::Image::PADDLE, 44, 66, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED)].addFrame(R::Image::PADDLE, 44, 44, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED)].addFrame(R::Image::PADDLE, 44, 22, 44, 22, ticks, true);


	ticks = 1;

	// LARGE TO CHARGED
	// El cambio es muy grande
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 0, 88, 66, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 116, 154, 62, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 118, 132, 58, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 120, 110, 54, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 122, 88, 50, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 124, 66, 46, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 126, 44, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 128, 22, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 2, 176, 30, 22, ticks, true);// Charged
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 1, 198, 31, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 0, 220, 32, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 34, 176, 34, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 33, 198, 35, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 32, 220, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 70, 176, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 69, 198, 37, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 68, 220, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 108, 176, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 107, 198, 39, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 106, 220, 40, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 148, 176, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 148, 198, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].addFrame(R::Image::PADDLE, 146, 220, 44, 22, ticks, true);

	ticks = 1;
	// CHARGED TO LARGE
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 146, 220, 44, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 148, 198, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 148, 176, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 106, 220, 40, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 107, 198, 39, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 108, 176, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 68, 220, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 69, 198, 37, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 70, 176, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 32, 220, 36, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 33, 198, 35, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 34, 176, 34, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 0, 220, 32, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 1, 198, 31, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 2, 176, 30, 22, ticks, true);// Charged
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 128, 22, 38, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 126, 44, 42, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 124, 66, 46, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 122, 88, 50, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 120, 110, 54, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 118, 132, 58, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 116, 154, 62, 22, ticks, true);
	sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].addFrame(R::Image::PADDLE, 0, 88, 66, 22, ticks, true);

	ticks = 8;
	// No olvidar los desplazamientos basados en el ancho y el alto	 88 x 22
	sprites[static_cast<size_t>(VausState::DEAD_NORMAL)].addFrame(R::Image::PADDLE, 0, 0, 44, 22, 50, true);
	sprites[static_cast<size_t>(VausState::DEAD_NORMAL)].addFrame(R::Image::PADDLE, 189, 509, 88, 27, ticks, false, 0, -3);
	sprites[static_cast<size_t>(VausState::DEAD_NORMAL)].addFrame(R::Image::PADDLE, 187, 557, 97, 35, ticks, false, 0, -6);
	sprites[static_cast<size_t>(VausState::DEAD_NORMAL)].addFrame(R::Image::PADDLE, 183, 605, 107, 43, ticks, false, 0, -10);
	sprites[static_cast<size_t>(VausState::DEAD_NORMAL)].addFrame(R::Image::PADDLE, 175, 654, 123, 56, ticks, false, 0, -17);

	int ticksAfter = 80;
	/* Transparente para que se quede ahi hasta que reviva, si es que lo hace.*/
	sprites[static_cast<size_t>(VausState::DEAD_NORMAL)].addFrame(R::Image::PADDLE, 682, 963, 88, 22,ticksAfter, false);


	/* DEAD LARGE*/
	sprites[static_cast<size_t>(VausState::DEAD_LARGE)].addFrame(R::Image::PADDLE, 0, 88, 66, 22, 50, true);
	sprites[static_cast<size_t>(VausState::DEAD_LARGE)].addFrame(R::Image::PADDLE, 276, 716, 128, 27, ticks, false, 0, -3);
	sprites[static_cast<size_t>(VausState::DEAD_LARGE)].addFrame(R::Image::PADDLE, 273, 763, 136, 36, ticks, false, 0, -6);
	sprites[static_cast<size_t>(VausState::DEAD_LARGE)].addFrame(R::Image::PADDLE, 271, 809, 140, 44, ticks, false, 0, -10);
	sprites[static_cast<size_t>(VausState::DEAD_LARGE)].addFrame(R::Image::PADDLE, 264, 860, 156, 52, ticks, false, 0, -15);
	sprites[static_cast<size_t>(VausState::DEAD_LARGE)].addFrame(R::Image::PADDLE, 682, 963, 122, 22, ticksAfter, false); /*Trasparente*/

																												   /*DEAD CHARGED*/
	sprites[static_cast<size_t>(VausState::DEAD_CHARGED)].addFrame(R::Image::PADDLE, 44, 0, 44, 22, 50, true);
	sprites[static_cast<size_t>(VausState::DEAD_CHARGED)].addFrame(R::Image::PADDLE, 313, 511, 93, 25, ticks, false, 0, -2);
	sprites[static_cast<size_t>(VausState::DEAD_CHARGED)].addFrame(R::Image::PADDLE, 311, 557, 96, 35, ticks, false, 0, -6);
	sprites[static_cast<size_t>(VausState::DEAD_CHARGED)].addFrame(R::Image::PADDLE, 307, 606, 107, 43, ticks, false, 0, -10);
	sprites[static_cast<size_t>(VausState::DEAD_CHARGED)].addFrame(R::Image::PADDLE, 299, 654, 121, 49, ticks, false, 0, -13);
	sprites[static_cast<size_t>(VausState::DEAD_CHARGED)].addFrame(R::Image::PADDLE, 682, 963, 122, 22, ticksAfter, false); /*Trasparente*/

										
	ticks = 1; /*Animación revivir*/
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 682, 963, 88, 22, 10, false);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 848, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 870, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 892, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 914, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 935, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 957, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 979, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 1001, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 1023, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 1045, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 1065, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 1088, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 1110, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 1132, 88, 22, ticks);
	sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].addFrame(R::Image::PADDLE, 0, 1154, 88, 22, ticks);

}

void Vaus::draw() const {
	sprites[static_cast<size_t>(state)].draw();

	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		it->draw();
	}
	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::SHADOWN_TITLE, 722, 342, ALLEGRO_ALIGN_CENTER, "LIVES");
	al_draw_text(Gallery::getSingleton().getFont(R::Font::VENUS_20), R::Color::WHITE, 720, 340, ALLEGRO_ALIGN_CENTER, "LIVES");
	for (int i = 0; i < lives; i++) {
		al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), 684, 176, 32, 32, 660 + 30 * i, 370, NULL);
	}
}

void Vaus::update() {
	
	sprites[static_cast<size_t>(state)].update();
	switch (state) {
		case VausState::NORMAL_TO_LARGE:
		case VausState::CHARGED_TO_LARGE:
			if (sprites[static_cast<size_t>(state)].animationFinish()) {
				sprites[static_cast<size_t>(VausState::LARGE)].reinit();
				state = VausState::LARGE;
			}
			break;
		case VausState::LARGE_TO_NORMAL:
		case VausState::CHARGED_TO_NORMAL:
			if (sprites[static_cast<size_t>(state)].animationFinish()) {
				sprites[static_cast<size_t>(VausState::NORMAL)].reinit();
				state = VausState::NORMAL;
			}
			break;
		case VausState::NORMAL_TO_CHARGED:
		case VausState::LARGE_TO_CHARGED:
			if (sprites[static_cast<size_t>(state)].animationFinish()) {
				sprites[static_cast<size_t>(VausState::CHARGED)].reinit();
				state = VausState::CHARGED;
			}

			break;
		case VausState::RELIVE_ANIMATION:
			if (sprites[static_cast<size_t>(state)].animationFinish()) {
				sprites[static_cast<size_t>(VausState::NORMAL)].reinit();
				state = VausState::NORMAL;
			}
			break;
	
		default:
			break;
	}

	// Actualiza las balas
	for (auto it = bullets.begin(); it != bullets.end(); it++) {
		it->update();
	}

	collisionWhitBall();

	if (isDead()) {
		if (sprites[static_cast<size_t>(state)].animationFinish()) {
			if (lives < 1) {
				game->over();
			}
			else {
				game->relive();
				lives--;
			}

		}

	}
	if (useMouse) { // Si useMouse es true entonces se coloca la nave en la posición del mouse.
		position.setX(mouse->getX() - getWidth() / 2);
	}
	verifyLimits();
}

void Vaus::doAction(action_t action, int magnitute) {
	if (!useMouse) {
		switch (action) {
		case RIGHT_VAUS:
			if (!isDead()) {
				position.setX(position.X() + velocity);
			}
			break;
		case LEFT_VAUS:
			if (!isDead()) {
				position.setX(position.X() - velocity);
			}
			break;
		}
	}

	if (action == SHOT) {
		if (state == VausState::CHARGED) {
			verifyLimits();
			Bullet b(this->position.X() + 7, this->position.Y());
			bullets.push_back(b);
			b.position.setX(this->position.X() + 74);
			bullets.push_back(b);
			Sound::playSample(R::Sample::SHOT);
		}
		else if (state == VausState::NORMAL) {
			/* Lanza la bola.*/
			for (auto it = balls->begin(); it != balls->end(); it++) {
				if ((*it)->isStopped()) {
					(*it)->setDirectionVertical(-1);
					Sound::playSample(R::Sample::RELEASE);
					(*it)->setStopped(false);
				}
			}
		}
	}
}

/* Verifica que la posición de la nave no se salga de los límites horizontales. */
void Vaus::verifyLimits() {
	if (position.X() < 88) {
		position.setX(88);
	}
	else if (position.X() + getWidth() > 613) {
		position.setX(613 - getWidth());
	}
}

bool Vaus::isDead() const {
	return (state == VausState::DEAD_NORMAL || state == VausState::DEAD_LARGE || state == VausState::DEAD_CHARGED);
}
void Vaus::setLives(int value) {
	lives = value;
}

int Vaus::getLives() const {
	return lives;
}

void Vaus::setState(VausState _state) {
	/* No hace nada si el estado es el mismo. */
	if (_state == state) return;

	/* Inicia la animación del estado actual al estado que se desea. */
	switch (_state) {
		case VausState::CHARGED:
			switch (state) {
			case VausState::NORMAL:
				sprites[static_cast<size_t>(VausState::NORMAL_TO_CHARGED)].reinit();
				state = VausState::NORMAL_TO_CHARGED;
				break;
			case VausState::LARGE:
				sprites[static_cast<size_t>(VausState::LARGE_TO_CHARGED)].reinit();
				state = VausState::LARGE_TO_CHARGED;
				break;
			default:
				break;
			}
			break;
		case VausState::NORMAL:
			switch (state) {
				case VausState::CHARGED:
					sprites[static_cast<size_t>(VausState::CHARGED_TO_NORMAL)].reinit();
					state = VausState::CHARGED_TO_NORMAL;
					break;
				case VausState::LARGE:
					sprites[static_cast<size_t>(VausState::LARGE_TO_NORMAL)].reinit();
					state = VausState::LARGE_TO_NORMAL;
					break;
				default:
					sprites[static_cast<size_t>(VausState::NORMAL)].reinit();
					state = VausState::NORMAL;
					break;
			}
			break;
		case VausState::LARGE:
			switch (state) {
				case VausState::CHARGED:
					sprites[static_cast<size_t>(VausState::CHARGED_TO_LARGE)].reinit();
					state = VausState::CHARGED_TO_LARGE;
					break;
				case VausState::NORMAL:
					sprites[static_cast<size_t>(VausState::NORMAL_TO_LARGE)].reinit();
					state = VausState::NORMAL_TO_LARGE;
					break;
				default:
					break;
			}
			break;
		case VausState::DEAD:
			switch (state) {   // Verificar cuando se está animando
				case VausState::CHARGED:
					sprites[static_cast<size_t>(VausState::DEAD_CHARGED)].reinit();
					state = VausState::DEAD_CHARGED;
					break;
				case VausState::NORMAL:
					sprites[static_cast<size_t>(VausState::DEAD_NORMAL)].reinit();
					state = VausState::DEAD_NORMAL;
					break;
				case VausState::LARGE:
					sprites[static_cast<size_t>(VausState::DEAD_LARGE)].reinit();
					state = VausState::DEAD_LARGE;
					break;
			}
			break;
		case VausState::RELIVE_ANIMATION:
			sprites[static_cast<size_t>(VausState::RELIVE_ANIMATION)].reinit();
			state = VausState::RELIVE_ANIMATION;
			break;
	}
}

VausState Vaus::getState() const {
	return state;
}

float Vaus::getWidth() const {
	return sprites[static_cast<size_t>(state)].getWidth();
}

float Vaus::getHeight() const {
	return 22;
}

void Vaus::collisionWhitBall() {
	static float centerX;
	static bool dead;

	dead = true; /* True si es que existe pelotas, false de otro modo. */
	for (auto itBall = balls->begin(); itBall != balls->end(); itBall++) {

		/*Comprobando si la pelota salió hacia abajo entonces perdio*/
		if ((*itBall)->position.Y() + (*itBall)->getHeight() > 610) {
			(*itBall)->die();
			/*Coloca en una posición para que no compare, pero no se muestra.*/
			(*itBall)->position.setPosition(100, 300);
		}


		if ((*itBall)->enable()) {
			dead = false;
			centerX = (*itBall)->position.X() + (*itBall)->getWidth() / 2;
			if ((*itBall)->isStopped()) {
				verifyLimits();
				(*itBall)->position.setX(position.X() + (*itBall)->getDiff());
			}

			// Esta dentro de vaus horizontal
			if (centerX > position.X() && centerX < (position.X() + getWidth())) {
				// Choca por arriba
				if (((*itBall)->position.Y() + (*itBall)->getHeight() > position.Y()) &&
					((*itBall)->position.Y() + (*itBall)->getHeight() < (position.Y() + getHeight()))) {

					(*itBall)->setDirectionVertical(-1); // La pelota va hacia arriba
					(*itBall)->generateAngle(30, 90);
					if ((*itBall)->getState() == BallState::STICKY) {
						(*itBall)->setStopped(true);
						(*itBall)->position.setY(position.Y() - (*itBall)->getHeight());
						(*itBall)->setDiff((*itBall)->position.X() - position.X());
					}
					else {
						Sound::playSample(R::Sample::RELEASE);
					}
				}
			}

			// Esta dentro de Vaus vertical
			if ((((*itBall)->position.Y() + (*itBall)->getHeight()) > position.Y()) &&
				((*itBall)->position.Y() < (position.Y() + getHeight()))) {

				// Choca por la izquierda
				if ((((*itBall)->position.X() + (*itBall)->getWidth()) > position.X()) &&
					(((*itBall)->position.X() + (*itBall)->getWidth()) < position.X() + 20)) {
					(*itBall)->setDirectionHorizontal(-1); // Va a la izquierda
				}

				// Choca por la derecha
				if ((*itBall)->position.X() < (position.X() + getWidth()) &&
					((*itBall)->position.X() >  (position.X() + getWidth() - 20))) {
					(*itBall)->setDirectionHorizontal(1); // Va a la izquierda
				}

			}
		}
	}

	if (dead) { // No hay ninguna pelota
		setState(VausState::DEAD);
		clearBullets();
		game->getLevel()->clearBonuses();
	}

}

void Vaus::clearBullets() {
	bullets.clear();
}