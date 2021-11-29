#pragma once

#include <3ds.h>
#include <cstdlib>

inline circlePosition cur_circle;
inline u32 cur_keys;
inline u32 new_keys;

inline void update_inputs() {
	// Read Input
	hidScanInput();
	hidCircleRead(&cur_circle);

	// Clamp circle pad strength.
	if (std::abs(cur_circle.dx) < 10) {
		cur_circle.dx = 0;
	} else if (cur_circle.dx > 140) {
		cur_circle.dx = 150;
	} else if (cur_circle.dx < -140) {
		cur_circle.dx = -150;
	}
	if (std::abs(cur_circle.dy) < 10) {
		cur_circle.dy = 0;
	} else if (cur_circle.dy > 140) {
		cur_circle.dy = 150;
	} else if (cur_circle.dy < -140) {
		cur_circle.dy = -150;
	}

	// Set basic keys.
	new_keys = hidKeysDown();
	cur_keys = hidKeysHeld();
}
