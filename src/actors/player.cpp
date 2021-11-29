#include <cstdio>

#include "include/input.hpp"
#include "include/vector.hpp"
#include "player.hpp"

Player::Player() {
	y = 80.0f;
	type = ActorType::PLAYER;
}

void Player::logic() {
	// Calculate input direction.
	Vector2Df input_direction;
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

	x += input_direction.x * 1.5f;
	y -= input_direction.y * 1.5f;

	if (new_keys & KEY_A) {
		if (detect_actor(ActorType::ENEMY)) {
			std::printf("Found Enemy!\n");
		} else if (detect_actor()) {
			std::printf("Found Actor!\n");
		} else {
			std::printf("Found none.\n");
		}
	}
}
