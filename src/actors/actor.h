#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <vector>

enum class ActorType {NONE = 0, PLAYER = 1, ENEMY = 2};

class Actor {
public:
	float x = 50.0f;
	float y = 50.0f;
	float width = 8.0f;
	float height = 8.0f;
	ActorType type = ActorType::NONE;
	C2D_Sprite sprite;

	virtual void logic() {};
	void render();
	Actor* detect_actor(ActorType type = ActorType::NONE);
};

class Enemy : public Actor {
public:
	Enemy();
	void logic();
};

extern std::vector <Actor*> actors;