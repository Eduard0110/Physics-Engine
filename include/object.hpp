#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "vec2.hpp"


class Object {
public:
	Vec2 c_pos;  // current position
	Vec2 p_pos;  // previous position
	Vec2 vel;    // velocity
	double r;    // radius

	Object(Vec2 cp, Vec2 pp, Vec2 v, double r) : c_pos(cp), p_pos(pp), vel(v), r(r) {}

	bool operator==(const Object& other) const {
		return c_pos == other.c_pos && p_pos == other.p_pos && vel == other.vel && r == other.r;
	}
};

#endif