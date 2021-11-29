#pragma once

#include "actor.hpp"
#include "vector.hpp"

class Player : public Actor {
  public:
	Vector2Df velocity = {0.0f, 0.0f};

	Player() {
		y = 80.0f;
		type = ActorType::PLAYER;
	}

	void logic();
};
