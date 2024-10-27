// Here, all the fun happens

#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <vector>
#include "object.hpp"
//#include "collisionSolver.hpp"


class World {
public:
	int width, height;
	const double bounceDamping = 0.9;  // energy loss factor when an object collides with another object (2%)
	const double frictionCoefficient = 0.99;  // velocity loss factor that is opposite in the direction of the object (1%)

	World::World(int width, int height) : width(width), height(height) {}

	std::vector<Object> m_objects;
	void update(double dt);
	void addObject(Vec2 cp, Vec2 pp, Vec2 acc, double r);
	void constrainWalls();
	void removeObject(const Object& obj);
};

#endif