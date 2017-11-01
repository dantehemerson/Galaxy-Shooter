#include <allegro5\allegro.h>

#include "StageManager.hpp"
#include "ActorManager.hpp"
#include "Actor.hpp"

StageManager::StageManager(ActorManager* _actorManager) : actorManager(_actorManager) {

}

void StageManager::update() {
	draw();
}

void StageManager::draw() {
	Actor* tempActor;
	actorManager->rewind();

	while ((tempActor = actorManager->next()) != NULL) {
		tempActor->draw();
	}
}

StageManager::~StageManager() {
}