#include <3ds.h>
#include <citro2d.h>
#include "actors/actor.h"
#include "include/input.h"
#include "include/vector.h"

std::vector <Actor*> actors;

void Actor::render() {
	sprite.params.pos.x = x;
	sprite.params.pos.y = y;
	C2D_DrawSprite(&sprite);
}

Actor* Actor::detect_actor(ActorType type = ActorType::NONE) {
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

Player::Player() {
	y = 80.0f;
	type = ActorType::PLAYER;
}

void Player::logic() {
	// Calculate input direction.
	Vec2Df input_direction;
	// The circle pad takes priority over the D-Pad.
	if (cur_circle.dx != 0 || cur_circle.dy != 0) {
		input_direction.x = cur_circle.dx / 150.0f;
		input_direction.y = cur_circle.dy / 150.0f;
	} else {
		if (cur_keys & KEY_DUP) {
			input_direction.y = 1.0f;
		} else if (cur_keys & KEY_DDOWN) {
			input_direction.y = -1.0f;
		}
		if (cur_keys & KEY_DRIGHT) {
			input_direction.x = 1.0f;
		} else if (cur_keys & KEY_DLEFT) {
			input_direction.x = - 1.0f;
		}
		input_direction.normalize();
	}

	if (new_keys & KEY_A) {
		if (detect_actor(ActorType::ENEMY)) {
			printf("Found Enemy!\n");
		} else if (detect_actor()) {
			printf("Found Actor!\n");
		} else {
			printf("Found none.\n");
		}
	}

	x += input_direction.x * 1.5f;
	y -= input_direction.y * 1.5f;
}

Enemy::Enemy() {
	type = ActorType::ENEMY;
}

void Enemy::logic() {
	x += 0.5f;
}