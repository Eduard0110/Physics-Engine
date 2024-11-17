// Here, all the fun happens

#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <vector>
#include "object.hpp"
#include "collisionSolver.hpp"


class World {
public:
	double width, height;
	const int sub_steps = 8;
	const double bounceDamping = 0.95;        // energy loss factor when an object collides with another object (5%)
	const double frictionCoefficient = 0.99;  // velocity loss factor that is opposite in the direction of the object (1%)
	const Vec2 gravity = Vec2(0.0, 1000.0);
	std::vector<Object> m_objects;
	CollisionSolver collision_solver;

	World::World(double w, double h) : width(w), height(h) {}
	
	void update(double dt);
	void addObject(Vec2 cp, Vec2 pp, Vec2 acc, double r);
	void constrainWalls();
	void applyGravity();
	void updateObjects(double dt);
	void removeObject(const Object& obj);
};

#endif