#include <3ds.h>
#include <citro2d.h>

#include "actors/actor.hpp"
#include "include/vector.hpp"

std::vector <uptr<Actor>> actors;

void Actor::render() {
	sprite.params.pos.x = x;
	sprite.params.pos.y = y;
	C2D_DrawSprite(&sprite);
}

Actor* Actor::detect_actor(ActorType type) {
	for (auto& i : actors) {
		if (i.get() == this)
			continue;
		if (detect_overlap(x, y, width, height, i->x, i->y,i->width, i->height)
			&& (i->type == type || type == ActorType::NONE))
			return i.get();
	}
	return nullptr;
}

void Enemy::logic() {
	x += 0.5f;
}
