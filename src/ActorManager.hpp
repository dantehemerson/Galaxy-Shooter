#pragma once
#ifndef ACTORMANAGER_HPP
#define ACTORMANAGER_HPP

#include <algorithm>
#include <list>

class Actor;

class ActorManager {
public:
	ActorManager();

	/*Añade un nuevo actor a la lista. */
	void add(Actor *actor);

	/*Elimina un actor de la lista. */
	void del(Actor *actor);

	/*Coloca el iterador en el inicio de la lista. */
	void rewind();

	/*El iterador apunta al siguiente elemento de la lista y retorna el puntero. */
	Actor* next();

	/* Retorna un apuntador al Actor al que esta apuntado el iterador. */
	Actor* current();
	void update();

	/* Retorna la cantidad de actores que hay en la lista, el tamaño de la lista actors */
	int getNumActors() const;

	~ActorManager();
private:
	std::list<Actor*> actors;/*Esta es la lista de actores*/
	std::list<Actor*>::iterator actorsIter; /* El iterador*/
};

#endif // !ACTORMANAGER_HPP