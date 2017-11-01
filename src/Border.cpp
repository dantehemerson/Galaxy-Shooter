#include "Border.hpp"

#include "BorderItem.hpp"

using std::vector;

/** POSICIONES(EN PIXELES) DE LOS ELEMENTOS	EN LA IMAGEN
type |	Description      	  (sX, sY)	   sW sH	   w h (sin sombra)
------------------------------------------------------------------------
0  |	cortoHorizontal 	(0,    71)	 (102, 36)	  (90, 23)
1  |	cortoVertical 		(103,  71)	 (36,  102)	  (23, 90)
2  |	delgado Vertical	(145, 207)	 (32,  108)	  (19, 95)
3  |	esquina Izq 		(103, 207)	 (42,  54)	  (29, 41)
4  |	esquina Der 		(103, 261)	 (42,  54) 	  (29, 41)
5  |	largo 				(103, 175)	 (232, 32)	  (219, 19)
*/
Border::Border(float x, float y) : Actor(x, y) {

	//Parte izquierda
	items.push_back(new BorderItem(0 + x, 41 + y, 1));
	items.push_back(new BorderItem(0 + x, 222 + y, 1));
	items.push_back(new BorderItem(0 + x, 403 + y, 1));
	items.push_back(new BorderItem(0 + x, 584 + y, 1));
	items.push_back(new BorderItem(0 + x, 0 + y, 3));
	items.push_back(new BorderItem(0 + x, 129 + y, 2));
	items.push_back(new BorderItem(0 + x, 310 + y, 2));
	items.push_back(new BorderItem(0 + x, 491 + y, 2));

	int rigth = 550;
	int inicioSup = rigth / 2 - 219 / 2 + 10;

	// Parte superior
	items.push_back(new BorderItem(inicioSup - 88 + x, 0 + y, 0));
	items.push_back(new BorderItem(inicioSup + 218 + x, 0 + y, 0));
	items.push_back(new BorderItem(inicioSup + x, 0 + y, 5));
	items.push_back(new BorderItem(inicioSup + 218 + 88 + x, 0 + y, 6));
	items.push_back(new BorderItem(31 + x, 0 + y, 7));

	/* Parte derecha.
	Esta dividida en parte derecha y parte izquierda porque al pintar los ultimos bloques
	de la derecha, la sombra de estos opacaban al borde con su sombra.
	Luego, los elementos de itemsRight se llaman con la función
	drawRight() después de haber pintado los bloques.*/
	itemsRight.push_back(new BorderItem(rigth + x, 41 + y, 1));
	itemsRight.push_back(new BorderItem(rigth + x, 222 + y, 1));
	itemsRight.push_back(new BorderItem(rigth + x, 403 + y, 1));
	itemsRight.push_back(new BorderItem(rigth + x, 584 + y, 1));
	itemsRight.push_back(new BorderItem(rigth - 10 + x, 0 + y, 4));
	itemsRight.push_back(new BorderItem(rigth + x, 129 + y, 2));
	itemsRight.push_back(new BorderItem(rigth + x, 310 + y, 2));
	itemsRight.push_back(new BorderItem(rigth + x, 491 + y, 2));
}

void Border::draw() const {
	for (auto it = items.begin(); it != items.end(); it++) {
		(*it)->draw();
	}
}

void Border::drawRight() const {
	for (auto it = itemsRight.begin(); it != itemsRight.end(); it++) {
		(*it)->draw();
	}
}

void Border::update() {

}

Border::~Border() {
	for (auto it = items.begin(); it != items.end(); it++) {
		delete (*it);
	}
	for (auto it = itemsRight.begin(); it != itemsRight.end(); it++) {
		delete (*it);
	}
}
