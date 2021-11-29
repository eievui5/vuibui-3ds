#pragma once

#include "actor.hpp"
#include "include/vector.hpp"

class Player : public Actor {
public:
	Vector2Df velocity = {0.0f, 0.0f};
	Player();
	void logic();
};
