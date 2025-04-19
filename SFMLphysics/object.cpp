#include "object.hpp"

// Verlet Integration:
// new_pos = 2 * current_pos - previous_pos + acc * dt^2
void Object::update(double dt) {
    if (!isStatic) {
        Vec2 velocity = c_pos - p_pos;             // calculate velocity
        p_pos = c_pos;                             // store current as previous
        c_pos += velocity + acc * (dt * dt);       // update current position
        acc = Vec2(0.0, 0.0);                      // reset acceleration
    }
}

// Constrain the object within the bounds of the walls
void Object::constrainWalls(double width, double height, double damping, double frictionCoefficient) {
    Vec2 velocity = c_pos - p_pos;

    applyWallConstraint(c_pos.x - r <= 0.0, c_pos.x, p_pos.x, r, frictionCoefficient, damping, velocity.x);              // Left wall
    applyWallConstraint(c_pos.x + r >= width, c_pos.x, p_pos.x, width - r, frictionCoefficient, damping, velocity.x);   // Right wall
    applyWallConstraint(c_pos.y - r <= 0.0, c_pos.y, p_pos.y, r, frictionCoefficient, damping, velocity.y);              // Top wall
    applyWallConstraint(c_pos.y + r >= height, c_pos.y, p_pos.y, height - r, frictionCoefficient, damping, velocity.y); // Bottom wall
}

// Apply a constraint to a specific wall
void Object::applyWallConstraint(bool hitWall, double& c_pos, double& p_pos, double wallPos,
    double friction, double damping, double velocityComponent) {
    if (hitWall) {
        p_pos -= velocityComponent * friction;             // simulate friction
        c_pos = wallPos;                                   // snap to wall
        p_pos = c_pos + velocityComponent * damping;       // damp the bounce
    }
}

// Apply a force (acceleration) to the object
void Object::accelerate(Vec2 acceleration) {
    if (!isStatic) {
        acc += acceleration;
    }
}

// Debugging: print velocity and acceleration
void Object::printInfo() const {
    std::cout << "Velocity: " << c_pos - p_pos << "\n";
    std::cout << "Acceleration: " << acc << "\n\n";
}
