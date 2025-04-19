// Here, all the fun happens

#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <vector>
#include "object.hpp"
#include "collisionSolver.hpp"
#include "grid.hpp"
#include "link.hpp"

class World {
public:
    double width, height;

    const int sub_steps = 8;
    const double bounceDamping = 0.95;        // energy loss factor when an object collides with another object (5%)
    const double frictionCoefficient = 0.99;  // velocity loss factor that is opposite in the direction of the object (1%)
    const double objectMaxR = 25.0;           // maximum object's radius
    const double objectMinR = 5.0;            // minimum object's radius
    const Vec2 gravity = Vec2(0.0, 1000.0);

    std::vector<std::unique_ptr<Object>> m_objects;
    std::vector<Link> m_links;

    CollisionSolver collision_solver;
    Grid grid;

    bool b_Collisions = true;
    bool b_drawObjects = true;
    bool b_drawLinks = true;
    bool b_subSteps = true;

    World(double w, double h)
        : width(w), height(h), grid(width, height, objectMaxR) {}

    void updateSimulationStep(double dt);
    void update(double dt);
    void constrainWalls();
    void constrainLinks(double dt);
    void applyGravity();
    void updateObjects(double dt);

    void addObject(Vec2 cp, Vec2 pp, Vec2 acc, double r);
    void removeObject(const Object& obj);

    void addLink(Object* A, Object* B, double k, double d = -1.0);
    void removeLink(const Link& obj);
};

#endif
