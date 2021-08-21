#include <3ds.h>
#include <citro2d.h>
#include "actors/actor.h"
#include "include/vector.h"

std::vector <Actor*> actors;

void Actor::render() {
	sprite.params.pos.x = x;
	sprite.params.pos.y = y;
	C2D_DrawSprite(&sprite);
}

Actor* Actor::detect_actor(ActorType type) {
	for (auto& cur_actor : actors) {
		if (cur_actor == this)
			continue;
		if (detect_box(x, y, width, height, cur_actor->x, cur_actor->y,
			       cur_actor->width, cur_actor->height) && 
		    (cur_actor->type == type || type == ActorType::NONE))
			return cur_actor;
	}
	return NULL;
}

Enemy::Enemy() {
	type = ActorType::ENEMY;
}

void Enemy::logic() {
	x += 0.5f;
}