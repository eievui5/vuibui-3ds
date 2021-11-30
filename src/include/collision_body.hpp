#pragma once

#include <citro2d.h>

#include "vector.hpp"

inline bool show_collision = false;

class CollisionBody {
  public:
	Vector2Df position = {0.0f, 0.0f};

	virtual void debug_draw_collision();
};

class CollisionRect : public CollisionBody {
  public:
	f32 width = 0.0f;
	f32 height = 0.0f;

	void debug_draw_collision() {
		C2D_DrawRectSolid(
			position.x, position.y, 0.0f, width * 2.0f, height * 2.0f, C2D_Color32f(1.0f, 0.0f, 0.0f, 0.25f));
	}
};
