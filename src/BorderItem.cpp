#include "BorderItem.hpp"

#include <allegro5\allegro.h>

#include "Gallery.hpp"
#include "R.hpp"

/** POSICIONES(EN PIXELES) DE LOS ELEMENTOS	EN LA IMAGEN
type |	Description      	  (sX, sY)	   sW sH	   w h (sin sombra)
------------------------------------------------------------------------
0  |	cortoHorizontal 	(0,    71)	 (102, 36)	  (90, 23)
1  |	cortoVertical 		(103,  71)	 (36,  102)	  (23, 90)
2  |	delgado Vertical	(145, 207)	 (32,  108)	  (19, 95)
3  |	esquina Izq 		(103, 207)	 (42,  54)	  (29, 41)
4  |	esquina Der 		(103, 261)	 (42,  54) 	  (29, 41)
5  |	largo 				(103, 175)	 (232, 32)	  (219, 19)
6  |	esquina der mit    (103, 175)	 (232, 32)	  (219, 19)
7  |	esquinaizq mitad   (103, 175)	 (232, 32)	  (219, 19)
*/

BorderItem::BorderItem(float x, float y, short _type) : Actor(x, y), type(_type) {
	switch (type) {
	case 0:
		sx = 0;
		sy = 71;
		sw = 102;
		sh = 36;
		break;
	case 1:
		sx = 103;
		sy = 71;
		sw = 36;
		sh = 102;
		break;
	case 2:
		sx = 145;
		sy = 207;
		sw = 32;
		sh = 108;
		break;
	case 3:
		sx = 103;
		sy = 207;
		sw = 42;
		sh = 54;
		break;
	case 4:
		sx = 103;
		sy = 261;
		sw = 42;
		sh = 54;
		break;
	case 5:
		sx = 103;
		sy = 175;
		sw = 232;
		sh = 32;
		break;
	case 6:
		sx = 103;
		sy = 175;
		sw = 70;
		sh = 32;
		break;
	case 7:
		sx = 264;
		sy = 175;
		sw = 64;
		sh = 32;
		break;

	}

	if (type == 2 || type == 3 || type == 4) {
		position.setX(position.X() + 2);
	}
	if (type == 5 || type == 3 || type == 4 || type == 6 || type == 7) {
		position.setY(position.Y() + 2);
	}

}


void BorderItem::draw() const {
	al_draw_bitmap_region(Gallery::getSingleton().getImage(R::Image::ITEMS), sx, sy, sw, sh, position.X(), position.Y(), NULL);
}

void BorderItem::update() {

}

BorderItem::~BorderItem() {
}