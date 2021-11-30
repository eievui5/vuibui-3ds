#include <3ds.h>
#include <citro2d.h>

#include "actors/actor.hpp"
#include "vector.hpp"

std::vector<uptr<Actor>> actors;

// Detect overlap with another actor by comparing positions, width, and height.
Actor* Actor::detect_actor() {
	for (auto& i : actors) {
		if (i.get() == this)
			continue;
		if (detect_overlap(position.x, position.y, width, height, i->position.x, i->position.y, i->width, i->height))
			return i.get();
	}
	return nullptr;
}
