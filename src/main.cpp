#include <3ds.h>
#include <citro2d.h>
#include <cstdio>
#include <cmath>
#include "actors/actor.h"
#include "actors/player.h"
#include "include/input.h"
#include "include/vector.h"

circlePosition cur_circle;
uint cur_keys;
uint new_keys;

// Detect if two boxes overlap. Width and height are treated as radii centered
// on the x and y.
bool detect_box(float x1, float y1, float w1, float h1,
		float x2, float y2, float w2, float h2) {
	if (x1 - w1 > x2 + w2 || x1 + w1 < x2 - w2)
		return false;
	if (y1 - h1 > y2 + h2 || y1 + h1 < y2 - h2)
		return false;
	return true;
}

void Vec2Df::normalize() {
	// If the vector is null do not normalize it. (Divide by 0 error)
	if (x == 0.0f && y == 0.0f)
		return;
	float divisor = length();
	x /= divisor;
	y /= divisor;
}

void Vec2Df::lerp(Vec2Df *target, float amount) {
	Vec2Df distance(target->x - x, target->y - y);
	distance.normalize();
	distance.x *= amount;
	distance.y *= amount;
	x += distance.x;
	y += distance.y;
}

int main() {
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	consoleInit(GFX_BOTTOM, NULL);

	actors.push_back(new Player);
	actors.push_back(new Enemy);
	actors.push_back(new Actor);

	C2D_SpriteSheet luvui_sheet = C2D_SpriteSheetLoad("romfs:/gfx/luvui.t3x");
	for (auto& cur_actor : actors) {
		C2D_SpriteFromSheet(&cur_actor->sprite, luvui_sheet, 0);
	}

	// Main loop
	while (aptMainLoop()) {
		update_inputs();

		for (const auto& cur_actor : actors) {
			cur_actor->logic();
		}

		// Rendering
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.3f, 0.5f, 0.3f, 1.0f));
		C2D_SceneBegin(top);

		for (const auto& cur_actor : actors) {
			cur_actor->render();
		}

		C3D_FrameEnd(0);
	}

	gfxExit();
	return 0;
}
