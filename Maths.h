#pragma once

#include <cstdlib>
// #include <SDL.h>/

#include <time.h>

#include <algorithm>
#include <cmath>

#include <ostream>


class Point {
public:
	Point(double x, double y) : x{x}, y{y} {}
	double length() const;
	double length_squared() const;
	void negate();
	Point get_negate() const;
	void rot_90();
	Point get_rot_90() const;
	void normalize();
	Point get_normalized() const;
	void scale(double value);
	Point get_scaled(double value) const;
	double x;
	double y;

	friend std::ostream& operator<<(std::ostream& ost, const Point& p);
};

class Rect {
public:
	Rect( double x, double y, double w, double h ) : x{x}, y{y}, w{w}, h{h} {}
	Rect(const Point& p1, const Point& p2) {
		x = std::min(p1.x, p2.x);
		y = std::min(p1.y, p2.y);
		w = std::abs(p1.x - p2.x);
		h = std::abs(p1.y - p2.y);
	}
	// bool is_inside(const Point& p) const;
	// bool is_overlapping(const Rect& r) const;
	Point get_center() const;
	void translate(double dx, double dy);

	friend std::ostream& operator<<(std::ostream& ost, const Rect& r);
	double x;
	double y;
	double w;
	double h;
};

//SDL_FPoint normalize(SDL_FPoint& v);
size_t rand_range(size_t from, size_t to);
Point compute_next(Point current, Point constant);
float computer_iterations(Point z0, Point constant, size_t max_iterations);