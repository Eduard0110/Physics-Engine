#include "world.hpp"


void World::update(double dt) {
    // updates all objects "sub_steps" times a frame 
    // the more updates per frame, the more accurate calculations
    const float sub_dt = dt / static_cast<float>(sub_steps);

    for (size_t i = 0; i < sub_steps; ++i) {
        applyGravity();
        constrainWalls();
        collision_solver.solveCollisions(m_objects);
        updateObjects(sub_dt);
    }

}

void World::applyGravity() {
    for (size_t i = 0; i < m_objects.size(); ++i) {
        m_objects[i].accelerate(gravity);
    }

}void World::updateObjects(double dt) {
    for (size_t i = 0; i < m_objects.size(); ++i) {
        m_objects[i].update(dt);
    }
}

void World::constrainWalls() {
    for (size_t i = 0; i < m_objects.size(); ++i) {
        m_objects[i].constrainWalls(width, height, bounceDamping, frictionCoefficient);
    }
}

void World::addObject(Vec2 cp, Vec2 pp, Vec2 acc, double r) {
    Object object(cp, pp, acc, r);
    m_objects.push_back(object);
}

void World::removeObject(const Object& obj) {
    auto it = std::find(m_objects.begin(), m_objects.end(), obj);
    if (it != m_objects.end()) {
        m_objects.erase(it);
    }
}