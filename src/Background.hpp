#pragma once
#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Actor.hpp"
#include "Vector2.hpp"

class Background : public Actor {
public:
    Background(int x = 0, int y = 0);
    virtual void draw() const override;
    virtual void update() override;

    ~Background();
private:
    static float velocity;
    int value;
    Vector2 posGlobal;
};


#endif // !BACKGROUND_HPP
