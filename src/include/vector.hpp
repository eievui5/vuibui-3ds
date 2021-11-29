#pragma once

#include <cmath>

// Floating point two-dimensional vector.
template<typename T> class Vector2D {
public:
	T x = 0.0f;
	T y = 0.0f;

	Vector2D() {}
	Vector2D(T new_x, T new_y) : x(new_x), y(new_y) {}

	void normalize() {
	// If the vector is null do not normalize it. (Divide by 0 error)
	if (x == 0.0f && y == 0.0f)
		return;
	float divisor = length();
	x /= divisor;
	y /= divisor;
	}

	void lerp(Vector2D* target, float amount) {
		Vector2D<T> distance(target->x - x, target->y - y);
		distance.normalize();
		distance.x *= amount;
		distance.y *= amount;
		x += distance.x;
		y += distance.y;
	}

	inline float length() {
		return sqrtf(x * x + y * y);
	}
};

using Vector2Df = Vector2D<float>;

// Detect if two boxes overlap. Width and height are treated as radii centered
// on the x and y.
template<typename T> bool detect_overlap(T x1, T y1, T w1, T h1, T x2, T y2, T w2, T h2) {
	if (x1 - w1 > x2 + w2 || x1 + w1 < x2 - w2)
		return false;
	if (y1 - h1 > y2 + h2 || y1 + h1 < y2 - h2)
		return false;
	return true;
}
