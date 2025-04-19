#include "world.hpp"

void World::update(double dt) {
    const float sub_dt = dt / static_cast<float>(sub_steps);

    // Update grid based on objects
    grid.Update(&m_objects);

    // Use substeps for more precise simulation
    if (b_subSteps) {
        for (size_t i = 0; i < sub_steps; ++i) {
            updateSimulationStep(sub_dt);
        }
    }
    else {
        // Single step update
        updateSimulationStep(dt);
    }
}

void World::updateSimulationStep(double dt) {
    applyGravity();
    constrainWalls();
    constrainLinks(dt);

    // Resolve collisions if enabled
    if (b_Collisions) {
        collision_solver.solveCollisions(&grid);
    }

    // Update all objects in the world
    updateObjects(dt);
}

void World::applyGravity() {
    for (auto& obj : m_objects) {
        obj->accelerate(gravity);
    }
}

void World::updateObjects(double dt) {
    for (auto& obj : m_objects) {
        obj->update(dt);
    }
}

void World::constrainWalls() {
    for (auto& obj : m_objects) {
        obj->constrainWalls(width, height, bounceDamping, frictionCoefficient);
    }
}

void World::constrainLinks(double dt) {
    for (auto& link : m_links) {
        link.update(dt);
    }
}

void World::addObject(Vec2 cp, Vec2 pp, Vec2 acc, double r) {
    m_objects.push_back(std::make_unique<Object>(cp, pp, acc, r));
}

void World::removeObject(const Object& obj) {
    auto it = std::remove_if(m_objects.begin(), m_objects.end(),
        [&obj](const std::unique_ptr<Object>& o) { return *o == obj; });
    m_objects.erase(it, m_objects.end());
}

void World::addLink(Object* A, Object* B, double k, double d) {
    m_links.emplace_back(A, B, k, d);
}

void World::removeLink(const Link& link) {
    auto it = std::remove_if(m_links.begin(), m_links.end(),
        [&link](const Link& l) { return l == link; });
    m_links.erase(it, m_links.end());
}
