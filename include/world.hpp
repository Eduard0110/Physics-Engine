// Here, all the fun happens

#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <vector>
#include "object.hpp"


class World {
public:
	std::vector<Object> m_objects;
	void update(double dt);
	void addObject(Vec2 cp, Vec2 pp, Vec2 v, double r);
	void removeObject(const Object& obj);
};

#endif