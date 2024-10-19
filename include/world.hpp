// Here, all the fun happens

#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <vector>
#include "object.hpp"


class World {
public:
	int width, height;

	World::World(int width, int height) : width(width), height(height) {}

	std::vector<Object> m_objects;
	void update(double dt);
	void addObject(Vec2 cp, Vec2 pp, Vec2 acc, double r);
	void constrainWalls();
	void removeObject(const Object& obj);
};

#endif