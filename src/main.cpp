#include <3ds.h>
#include <array>
#include <citro2d.h>
#include <cstdio>

#define NB_ACTORS 8

circlePosition cur_circle;
uint cur_keys;

// Floating point two-dimensional vector.
class Vec2Df {
public:
	float x = 0.0f;
	float y = 0.0f;

	Vec2Df() {}
	Vec2Df(float new_x, float new_y) : x(new_x), y(new_y) {}

	void normalize() {
		// If the vector is null do not normalize it. (Divide by 0 error)
		if (x == 0 && y == 0)
			return;
		float divisor = sqrtf(x * x + y * y);
		x /= divisor;
		y /= divisor;
	}
};

class Actor {
public:
	float x;
	float y;
	C2D_Sprite sprite;

	virtual void logic() {}

	void render() {
		sprite.params.pos.x = x;
		sprite.params.pos.y = y;
		C2D_DrawSprite(&sprite);
	}
};

class Player : public Actor {
public:
	void logic() {
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

		printf("\x1b[2;0HInput direction: %f %f", input_direction.x, input_direction.y);

		x += input_direction.x * 1.5f;
		y -= input_direction.y * 1.5f;
	}
};

class Enemy : public Actor {
public:
	void logic() {
		x += 0.5f;
	}
};

int main() {
	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	consoleInit(GFX_BOTTOM, NULL);

	puts(CONSOLE_RED "H" CONSOLE_YELLOW "e" CONSOLE_GREEN "l" CONSOLE_BLUE "l"
		CONSOLE_MAGENTA "o" CONSOLE_RED " W" CONSOLE_YELLOW "o" CONSOLE_GREEN "r"
		CONSOLE_BLUE "l" CONSOLE_MAGENTA "d" CONSOLE_WHITE "!");

	Actor *actors[NB_ACTORS];
	memset(actors, 0, sizeof(actors));
	actors[0] = new Player;
	actors[1] = new Enemy;
	actors[2] = new Actor;

	C2D_SpriteSheet luvui_sheet = C2D_SpriteSheetLoad("romfs:/gfx/luvui.t3x");
	for (int i = 0; i < NB_ACTORS; i++) {
		if (actors[i]) {
			C2D_SpriteFromSheet(&actors[i]->sprite, luvui_sheet, 0);
		}
	}

	// Main loop
	while (aptMainLoop()) {

		// Read Input
		hidScanInput();
		hidCircleRead(&cur_circle);
		cur_keys = hidKeysHeld();

		for (int i = 0; i < NB_ACTORS; i++) {
			if (actors[i]) {
				actors[i]->logic();
			}
		}

		// Rendering
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.3f, 0.5f, 0.3f, 1.0f));
		C2D_SceneBegin(top);

		for (int i = 0; i < NB_ACTORS; i++) {
			if (actors[i]) {
				actors[i]->render();
			}
		}

		C3D_FrameEnd(0);
	}

	gfxExit();
	return 0;
}
