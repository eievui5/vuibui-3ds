#include <stdio.h>

#include "input.hpp"
#include "player.hpp"
#include "vector.hpp"

void Player::logic() {
	// Calculate input direction.
	Vector2Df input_direction;
	// The circle pad takes priority over the D-Pad.
	if (cur_circle.dx != 0 || cur_circle.dy != 0) {
		input_direction.x = cur_circle.dx / 150.0f;
		input_direction.y = cur_circle.dy / -150.0f;
	} else {
		if (cur_keys & KEY_DUP) {
			input_direction.y = -1.0f;
		} else if (cur_keys & KEY_DDOWN) {
			input_direction.y = 1.0f;
		}
		if (cur_keys & KEY_DRIGHT) {
			input_direction.x = 1.0f;
		} else if (cur_keys & KEY_DLEFT) {
			input_direction.x = -1.0f;
		}
		input_direction.normalize();
	}

	velocity = input_direction * 1.5f;
	position += velocity;

	if (new_keys & KEY_A) {
		if (detect_actor()) {
			puts("Found actor.");
		} else {
			puts("Found none.");
		}
	}
}
