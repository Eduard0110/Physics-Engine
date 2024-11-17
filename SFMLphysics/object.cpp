#include "object.hpp"

// Verlet Integration
// new_pos = 2 * current_pos - previous_pos + acc * dt^2
// or
// velocity = c_pos - p_pos (change in current and previous positions)
// new_pos += velocity + acc * dt^2 
void Object::update(double dt) {
    Vec2 velocity = c_pos - p_pos;         // calculate velocity
    p_pos = c_pos;                         // save current position into previous
    c_pos += velocity + acc * (dt * dt);   // update current position
    acc = Vec2(0.0, 0.0);                  // reset acceleration
}

// constraints the objects from moving beyond walls
void Object::constrainWalls(double width, double height, double damping, double frictionCoefficient) {
    Vec2 vel = c_pos - p_pos;

    applyWallConstraint(c_pos.x - r <= 0.0, c_pos.x, p_pos.x, r, frictionCoefficient, damping, vel.x);          // Left wall
    applyWallConstraint(c_pos.x + r >= width, c_pos.x, p_pos.x, width - r, frictionCoefficient, damping, vel.x); // Right wall
    applyWallConstraint(c_pos.y - r <= 0.0, c_pos.y, p_pos.y, r, frictionCoefficient, damping, vel.y);          // Top wall
    applyWallConstraint(c_pos.y + r >= height, c_pos.y, p_pos.y, height - r, frictionCoefficient, damping, vel.y); // Bottom wall
}

// apply constrain to a single wall
void Object::applyWallConstraint(bool hitWall, double& c_pos, double& p_pos, double wallPos,
    double friction, double damping, double velocityComponent) {
    if (hitWall) {
        p_pos -= velocityComponent * friction;
        c_pos = wallPos;
        p_pos = c_pos + velocityComponent * damping;
    }
}

// apply a force to the object
void Object::accelerate(Vec2 acceleration) {
    acc += acceleration;
}

// print object info (for debugging)
void Object::printInfo() const {
    std::cout << "Velocity: " << c_pos - p_pos << "\n";
    std::cout << "Acceleration: " << acc << "\n\n";
}
