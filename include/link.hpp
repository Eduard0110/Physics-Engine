#ifndef LINK_HPP
#define LINK_HPP

#include "object.hpp"

class Link {
public:
	Link(Object* objA, Object* objB, double spring_constant, double distance = -1)
		: A(objA), B(objB), k(spring_constant)
	{
		// if distance is not provided (or set to -1), calculate it from current positions
		d = (distance > 0) ? distance : A->c_pos.Distance(B->c_pos);
	}

	bool operator==(const Link& other) const {
		return A == other.A && B == other.B;
	}

	Object* A;
	Object* B;
	double d;
	double k;

	void update(double dt) {
		double curr_d = A->c_pos.Distance(B->c_pos);

		double delta_d = curr_d - d;
		Vec2 direction = (A->c_pos - B->c_pos).Normalize();

		A->c_pos -= direction * delta_d * dt * k;
		B->c_pos += direction * delta_d * dt * k;
	}
};

#endif
