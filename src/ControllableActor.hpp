#pragma once
#ifndef CONTROLLABLEACTOR_HPP
#define CONTROLLABLEACTOR_HPP

#include "Actor.hpp"            
#include "ControllableObject.hpp"

class ControllableActor : public Actor, public ControllableObject {
};

#endif // !CONTROLLABLEACTOR_HPP