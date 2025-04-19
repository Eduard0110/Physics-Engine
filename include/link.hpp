#ifndef LINK_HPP
#define LINK_HPP

#include "object.hpp"

class Link {
public:
    Link(Object* objA, Object* objB, double spring_constant, double distance = -1)
        : A(objA), B(objB), k(spring_constant)
    {
        // If distance is not provided (or set to -1), calculate it from current positions
        d = (distance > 0) ? distance : A->c_pos.Distance(B->c_pos);
    }

    bool operator==(const Link& other) const {
        return A == other.A && B == other.B;
    }

    void update(double dt) {
        double curr_d = A->c_pos.Distance(B->c_pos);
        double delta_d = curr_d - d;
        Vec2 direction = (A->c_pos - B->c_pos).Normalize();

        if (!A->isStatic) {
            A->c_pos -= direction * delta_d * dt * k;
        }
        if (!B->isStatic) {
            B->c_pos += direction * delta_d * dt * k;
        }
    }

    Object* A;
    Object* B;
    double d; // rest length
    double k; // spring constant
};

#endif
