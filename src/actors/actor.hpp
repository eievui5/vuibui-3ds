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
	Vector2Df velocity = {0.0f, 0.0f};

	Actor(f32 x = 0.0f, f32 y = 0.0f, f32 w = 8.0f, f32 h = 8.0) {
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
		if (show_collision) {
			debug_draw_collision();
			C2D_DrawLine(
				position.x + width, position.y + height, C2D_Color32f(0.0f, 0.0f, 1.0f, 0.0f),
				position.x + width + velocity.x * 32.0f, position.y + height + velocity.y * 32.0f,
				C2D_Color32f(1, 0, 0, 1), 1, 0);
		}
	}

	Actor* detect_actor();
};

extern std::vector<uptr<Actor>> actors;

class Enemy : public Actor {
  public:
	using Actor::Actor;

	void logic() {
		velocity = {actors[0]->position.x - position.x, actors[0]->position.y - position.y};
		velocity.normalize();
		velocity *= 0.5f;
		position += velocity;
	}
};
