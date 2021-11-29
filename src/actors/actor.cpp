#include <3ds.h>
#include <citro2d.h>

#include "actors/actor.hpp"
#include "vector.hpp"

std::vector<uptr<Actor>> actors;

// Detect overlap with another actor by comparing positions, width, and height.
Actor* Actor::detect_actor(ActorType type) {
	for (auto& i : actors) {
		if (i.get() == this)
			continue;
		if (detect_overlap(x, y, width, height, i->x, i->y, i->width, i->height)
			&& (i->type == type || type == ActorType::NONE))
			return i.get();
	}
	return nullptr;
}
