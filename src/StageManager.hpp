#pragma once
#ifndef STAGEMANAGER_HPP
#define STAGEMANAGER_HPP

class ActorManager;

class StageManager {
public:
	StageManager(ActorManager *actorManager);

	void draw();
	void update();

	~StageManager();
private:
	ActorManager* actorManager;
};
#endif // !STAGEMANAGER_HPP