#pragma once

#include "actor.h"
#include "include/vector.h"

class Player : public Actor {
public:
	Vec2Df velocity = {0.0f, 0.0f};
	Player();
	void logic();
};