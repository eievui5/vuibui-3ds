#include <3ds.h>
#include <citro2d.h>
#include <cmath>
#include "actors/actor.hpp"
#include "actors/player.hpp"
#include "include/input.hpp"
#include "include/vector.hpp"

circlePosition cur_circle;
u32 cur_keys;
u32 new_keys;

int main() {
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	consoleInit(GFX_BOTTOM, nullptr);

	actors.emplace_back(new Player);
	actors.emplace_back(new Enemy);
	actors.emplace_back(new Actor);

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
