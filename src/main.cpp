#include <3ds.h>
#include <citro2d.h>
#include <cmath>
#include <stdio.h>

#include "actors/actor.hpp"
#include "actors/player.hpp"
#include "input.hpp"
#include "vector.hpp"

int main() {
	// Initiallize the 3DS for rendering and file access.
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	// Initiallize the stdout console on the bottom screen.
	consoleInit(GFX_BOTTOM, nullptr);

	// Construct 3 debug actors.
	actors.emplace_back(new Player{16.0f, 80.0f, 8.0f, 8.0f});
	actors.emplace_back(new Enemy);
	actors.emplace_back(new Actor{16.0f, 16.0f, 8.0f, 8.0f});

	// Assign a sprite to each actor using a sprite sheet from romfs.
	C2D_SpriteSheet luvui_sheet = C2D_SpriteSheetLoad("romfs:/gfx/luvui.t3x");

	for (auto& cur_actor : actors) {
		C2D_SpriteFromSheet(&cur_actor->sprite, luvui_sheet, 0);
	}

	// Main loop
	while (aptMainLoop()) {
		// Poll 3DS inputs for this frame.
		update_inputs();

		if (new_keys & KEY_ZR) {
			show_collision ^= true;
			printf("Toggled visible collision %s.\n", show_collision ? "on" : "off");
		}

		// Run each actor's frame logic function.
		for (const auto& cur_actor : actors) {
			cur_actor->logic();
		}

		// Rendering
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.3f, 0.5f, 0.3f, 1.0f));
		C2D_SceneBegin(top);

		// Draw each actor according to their render function.
		for (const auto& cur_actor : actors) {
			cur_actor->render();
		}

		// Finish up the frame and wait for the next.
		C3D_FrameEnd(0);
	}

	gfxExit();
	return 0;
}
