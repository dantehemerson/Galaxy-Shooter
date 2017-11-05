#include "Background.hpp"
#include "Gallery.hpp"

#include <cstdio>


float Background::velocity =  1;

Background::Background(int x, int y) : Actor(x, y) {
    posGlobal.setPosition(x, y);
}

void Background::draw() const {
    al_draw_bitmap(Gallery::getSingleton().getImage(R::Image::BACKGROUND1), Background::posGlobal.X(), Background::posGlobal.Y(), 0);
}

void Background::update() {
    posGlobal.setY(posGlobal.Y() - velocity);
    printf("valor = %f\n", posGlobal.Y());
    if(posGlobal.Y() <= -800) {
        posGlobal.setY(0);
    }
}

Background::~Background() {

}
