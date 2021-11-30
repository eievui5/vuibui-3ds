#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <vector>

#include "collision_body.hpp"
#include "input.hpp"
#include "vector.hpp"

enum class ActorType { NONE = 0, PLAYER, ENEMY };

class Actor : public CollisionRect {
  public:
	ActorType type = ActorType::NONE;
	C2D_Sprite sprite;

	Actor(f32 x = 0.0f, f32 y = 0.0f, f32 w = 8.0f, f32 h = 8.0f) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
	}

	virtual void logic(){};

	void render() {
		sprite.params.pos.x = position.x;
		sprite.params.pos.y = position.y;
		C2D_DrawSprite(&sprite);
		if (show_collision)
			debug_draw_collision();
	}

	Actor* detect_actor();
};

extern std::vector<uptr<Actor>> actors;

class Enemy : public Actor {
  public:
	using Actor::Actor;

	void logic() {
		Vector2Df direction = {actors[0]->position.x - position.x, actors[0]->position.y - position.y};
		direction.normalize();
		direction *= 0.5f;
		position += direction;
	}
};
