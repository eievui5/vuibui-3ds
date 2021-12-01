#pragma once

#include "actor.hpp"
#include "vector.hpp"

class Player : public Actor {
  public:
	using Actor::Actor;

	void logic();
};
