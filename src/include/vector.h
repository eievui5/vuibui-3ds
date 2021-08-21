#pragma once

#include <cmath>

bool detect_box(float x1, float y1, float w1, float h1,
		float x2, float y2, float w2, float h2);

// Floating point two-dimensional vector.
class Vec2Df {
public:
	float x = 0.0f;
	float y = 0.0f;

	Vec2Df() {}
	Vec2Df(float new_x, float new_y) : x(new_x), y(new_y) {}

	void normalize();
	void lerp(Vec2Df *target, float amount);

	inline float length() {
		return sqrtf(x * x + y * y);
	}
};