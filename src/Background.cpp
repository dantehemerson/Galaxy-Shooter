#include "Background.hpp"
#include "Gallery.hpp"

#include <cstdio>


float Background::velocity =  1;

Background::Background(int x, int y) : Actor(x, y) {
    value = -1;
}


void Background::draw() const {
    al_draw_bitmap(Gallery::getSingleton().getImage(R::Image::BACKGROUND1), Background::posGlobal.X(), Background::posGlobal.Y(), 0);
    al_draw_bitmap(Gallery::getSingleton().getImage(R::Image::BACKGROUND1), Background::posGlobal.X(), Background::posGlobal.Y() + 600 * value, 0);

}

void Background::update() {
    posGlobal.setY(posGlobal.Y() + velocity);
    if(posGlobal.Y() == 600){
        posGlobal.setY(-600);
        value *= -1;
    }
    if(posGlobal.Y() == 0) {
        value *= -1;
    }
}

Background::~Background() {

}
