#include "world.hpp"


void World::update(double dt) {

}

void World::addObject(Vec2 cp, Vec2 pp, Vec2 v, double r) {
    Object object(cp, pp, v, r);
    m_objects.push_back(object);
}

void World::removeObject(const Object& obj) {
    auto it = std::find(m_objects.begin(), m_objects.end(), obj);
    if (it != m_objects.end()) {
        m_objects.erase(it);
    }
}