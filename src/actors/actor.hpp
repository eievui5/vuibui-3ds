#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <vector>

enum class ActorType { NONE = 0, PLAYER, ENEMY };

class Actor {
  public:
	f32 x = 50.0f;
	f32 y = 50.0f;
	f32 width = 8.0f;
	f32 height = 8.0f;
	ActorType type = ActorType::NONE;
	C2D_Sprite sprite;

	virtual void logic(){};

	void render() {
		sprite.params.pos.x = x;
		sprite.params.pos.y = y;
		C2D_DrawSprite(&sprite);
	}

	Actor* detect_actor(ActorType type = ActorType::NONE);
};

class Enemy : public Actor {
  public:
	Enemy() { type = ActorType::ENEMY; };

	void logic() { x += 0.5f; }
};

extern std::vector<uptr<Actor>> actors;
