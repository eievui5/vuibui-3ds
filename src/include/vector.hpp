#pragma once

#include <cmath>

// 2-dimensional vector template.
template <typename T> class Vector2D {
  public:
	T x = 0.0f;
	T y = 0.0f;

	Vector2D() {}
	Vector2D(T new_x, T new_y) : x(new_x), y(new_y) {}

	// Vector operators. == is omitted because it should be avoided for vectors.
	inline Vector2D<T> operator+(Vector2D<T> rhs) { return {x + rhs.x, y + rhs.y}; }
	inline Vector2D<T> operator-(Vector2D<T> rhs) { return {x - rhs.x, y - rhs.y}; }
	inline Vector2D<T> operator*(T rhs) { return {x * rhs, y * rhs}; }
	inline Vector2D<T> operator/(T rhs) { return {x / rhs, y / rhs}; }
	inline void operator=(Vector2D<T> rhs) { x = rhs.x, y = rhs.y; }
	inline void operator+=(Vector2D<T> rhs) { x += rhs.x, y += rhs.y; }
	inline void operator-=(Vector2D<T> rhs) { x -= rhs.x, y -= rhs.y; }
	inline void operator*=(T rhs) { x *= rhs, y *= rhs; }
	inline void operator/=(T rhs) { x /= rhs, y /= rhs; }

	void normalize() {
		// If the vector is null do not normalize it. (Divide by 0 error)
		if (x == 0.0f && y == 0.0f)
			return;
		f32 divisor = length();
		x /= divisor;
		y /= divisor;
	}

	void lerp(Vector2D* target, f32 amount) {
		Vector2D<T> distance(target->x - x, target->y - y);
		distance.normalize();
		distance.x *= amount;
		distance.y *= amount;
		x += distance.x;
		y += distance.y;
	}

	inline f32 length() { return std::sqrt(x * x + y * y); }
};

using Vector2Df = Vector2D<f32>;

// Detect if two boxes overlap. Width and height are treated as radii centered
// on the x and y.
template <typename T> bool detect_overlap(T x1, T y1, T w1, T h1, T x2, T y2, T w2, T h2) {
	if (x1 - w1 > x2 + w2 || x1 + w1 < x2 - w2 || y1 - h1 > y2 + h2 || y1 + h1 < y2 - h2)
		return false;
	return true;
}
