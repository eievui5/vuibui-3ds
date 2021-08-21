#include "include/vector.h"

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