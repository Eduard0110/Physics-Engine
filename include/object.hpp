#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "vec2.hpp"


class Object {
public:
	Vec2 c_pos;  // current position
	Vec2 p_pos;  // previous position
	Vec2 acc;    // acceleration
	double r;    // radius

	Object(Vec2 cp, Vec2 pp, Vec2 a, double r) : c_pos(cp), p_pos(pp), acc(a), r(r) {}

	// Function declarations
	void printInfo();
	void update(double dt);
	void constrainWalls(double width, double height);
	Vec2 applyForces();

	// Overload equality operator
	bool operator==(const Object& other) const {
		return c_pos == other.c_pos && p_pos == other.p_pos && acc == other.acc && r == other.r;
	}
};

#endif
