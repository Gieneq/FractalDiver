#include "Maths.h"

//SDL_FPoint normalize(SDL_FPoint& v) {
//	float len = sqrtf(v.x * v.x + v.y * v.y);
//	return SDL_FPoint{ v.x / len, v.y / len };
//}

size_t rand_range(size_t from, size_t to) {
	if (to < from) std::swap(from, to);
	return static_cast<size_t>( from + rand() % (to-from) );
}


float Point::length() const {
	return std::sqrt(length_squared());
}

float Point::length_squared() const {
	return x * x + y * y;
}

void Point::negate() {
	this->x *= -1.0F;
	this->y *= -1.0F;
}

Point Point::get_negate() const {
	return Point{ -this->x, -this->y };
}

void Point::rot_90() {
	std::swap(this->x, this->y);
}

Point Point::get_rot_90() const {
	return Point(this->y, this->x);
}

void Point::normalize() {
	auto this_len = this->length();
	this->scale(1.0F / this_len);
}


Point Point::get_normalized() const {
	auto this_len = this->length();
	return Point(this->x / this_len, this->y / this_len);
}


void Point::scale(float value) {
	this->x *= value;
	this->y *= value;
}

Point Point::get_scaled(float value) const {
	return Point(this->x * value, this->y * value);
}


bool Rect::is_inside(const Point& p) const {
	return SDL_PointInFRect(&p, this) == SDL_TRUE;
}


bool Rect::is_overlapping(const Rect& r) const {
	return SDL_HasIntersectionF(this, &r) == SDL_TRUE;
}


Point Rect::get_center() const {
	return Point{x + w/2.0F, y + h/2.0F};
}

void Rect::translate(float dx, float dy) {
	x += dx;
	y += dy;
}


std::ostream& operator<<(std::ostream& ost, const Rect& r) {
	ost << "(" << r.x << ", " << r.y << ", " << r.w << ", " << r.h << ", " << ")";
	return ost;
}