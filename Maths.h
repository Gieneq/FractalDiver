#pragma once
#include "SDL.h"

#include <cstdlib>
#include <time.h>

#include <algorithm>
#include <cmath>

#include <ostream>

class Point : public SDL_FPoint {
public:
	Point(float x, float y) : SDL_FPoint{ x,y } {}
	float length() const;
	float length_squared() const;
	void negate();
	Point get_negate() const;
	void rot_90();
	Point get_rot_90() const;
	void normalize();
	Point get_normalized() const;
	void scale(float value);
	Point get_scaled(float value) const;
};

class Rect : public SDL_FRect {
public:
	Rect( float x, float y, float w, float h ) : SDL_FRect{ x,y,w,h } {}
	Rect(const Point& p1, const Point& p2) {
		x = std::min(p1.x, p2.x);
		y = std::min(p1.y, p2.y);
		w = std::abs(p1.x - p2.x);
		h = std::abs(p1.y - p2.y);
	}
	bool is_inside(const Point& p) const;
	bool is_overlapping(const Rect& r) const;
	Point get_center() const;
	void translate(float dx, float dy);

	friend std::ostream& operator<<(std::ostream& ost, const Rect& r);
};

//SDL_FPoint normalize(SDL_FPoint& v);
size_t rand_range(size_t from, size_t to);