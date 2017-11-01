#include "ActorManager.hpp"
#include "Actor.hpp"
#include <iostream>

using namespace std;

ActorManager::ActorManager() {

}

/*Añade un nuevo actor a la lista. */
void ActorManager::add(Actor* actor) {
	actors.push_back(actor);
}

/*Elimina un actor de la lista. */
void ActorManager::del(Actor* actor) {
	list<Actor*>::iterator tempActorsIter;

	tempActorsIter = find(actors.begin(), actors.end(), actor);
	if (tempActorsIter != actors.end()) {
		actors.erase(tempActorsIter);
	}
}

/* El iterador apunta al primer elemento de la lsita actors. */
void ActorManager::rewind() {
	actorsIter = actors.begin();
}

/* El iterador apunta al siguiente elemento de la lista, si llega al final de la lista entonces
retorna nullptr(un apuntador seguro que no apunta a nada) */
Actor* ActorManager::next() {
	Actor* tempActor;
	if (actorsIter == actors.end()) {
		return nullptr;
	}
	tempActor = *actorsIter;
	actorsIter++;
	return tempActor;
}

/* Retorna un apuntador a un objeto de actors al que se encuentra apuntado el iterador
actualmente */
Actor* ActorManager::current() {
	if (actorsIter == actors.end()) {
		return nullptr;
	}
	else {
		return *actorsIter;
	}
}

int ActorManager::getNumActors() const {
	return actors.size();
}

void ActorManager::update() {
	list<Actor*>::iterator tempActorsIter;
	for (tempActorsIter = actors.begin(); tempActorsIter != actors.end(); tempActorsIter++) {
		(*tempActorsIter)->update();
	}
}

ActorManager::~ActorManager() {
	for (actorsIter = actors.begin(); actorsIter != actors.end(); actorsIter++) {
		delete (*actorsIter);
	}
}
