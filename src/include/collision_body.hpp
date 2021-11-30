#pragma once

#include <citro2d.h>

class CollisionBody {
  public:
	virtual void debug_draw_collision();
};

class CollisionRect : public CollisionBody {
  public:
	f32 x = 0.0f;
	f32 y = 0.0f;
	f32 w = 0.0f;
	f32 h = 0.0f;

	void debug_draw_collision() {
		C2D_DrawRectSolid(x, y, 0.0f, w * 2.0f, h * 2.0f, C2D_Color32f(1.0f, 0.0f, 0.0f, 0.25f));
	}
};
