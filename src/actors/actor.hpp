#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <vector>

#include "collision_body.hpp"
#include "vector.hpp"

enum class ActorType { NONE = 0, PLAYER, ENEMY };

class Actor : public CollisionRect {
  public:
	ActorType type = ActorType::NONE;
	C2D_Sprite sprite;

	Actor() {
		w = 8.0f;
		h = 8.0f;
	}
	Actor(f32 _w, f32 _h) {
		w = _w;
		h = _h;
	}
	Actor(f32 _x, f32 _y, f32 _w, f32 _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	virtual void logic(){};

	void render() {
		sprite.params.pos.x = x;
		sprite.params.pos.y = y;
		C2D_DrawSprite(&sprite);
		debug_draw_collision();
	}

	Actor* detect_actor();
};

extern std::vector<uptr<Actor>> actors;

class Enemy : public Actor {
  public:
	using Actor::Actor;

	void logic() {
		Vector2Df direction = {actors[0]->x - x, actors[0]->y - y};
		direction.normalize();
		direction *= 0.5f;
		direction += Vector2Df(0.0f, 0.0f) - Vector2Df(1.0f, 5.0f);
		Vector2D<u8> integer_vector{(u8) direction.x, (u8) direction.y};
		direction *= integer_vector.x;
		x += direction.x;
		y += direction.y;
	}
};
