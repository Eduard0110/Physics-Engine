#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "vec2.hpp"
#include <iostream>

class Object {
public:
    Object(Vec2 cp, Vec2 pp, Vec2 a, double r)
        : c_pos(cp), p_pos(pp), acc(a), r(r) {}

    void update(double dt);
    void constrainWalls(double width, double height, double damping, double frictionCoefficient);
    void accelerate(Vec2 acceleration);
    void printInfo() const;

    bool operator==(const Object& other) const {
        return c_pos == other.c_pos &&
            p_pos == other.p_pos &&
            acc == other.acc &&
            r == other.r;
    }

    // Member variables
    Vec2 c_pos;   // Current position
    Vec2 p_pos;   // Previous position
    Vec2 acc;     // Acceleration
    double r;     // Radius
    bool isStatic = false;

private:
    void applyWallConstraint(
        bool hitWall,
        double& pos,
        double& prevPos,
        double wallPos,
        double friction,
        double damping,
        double velocityComponent
    );
};

#endif
