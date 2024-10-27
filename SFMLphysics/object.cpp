#include "object.hpp"

void Object::update(double dt) {
	Vec2 new_pos = c_pos * 2.0 - p_pos + acc * dt;
	Vec2 new_acc = applyForces();

	p_pos = c_pos;
	c_pos = new_pos;
	acc = new_acc;
}

void Object::constrainWalls(double width, double height, const double damping, const double frictionCoefficient) {
    Vec2 dpos = (c_pos - p_pos);  // Change in positions (velocity)

    // Left wall
    if ((c_pos.x - r) <= 0.0) {
        p_pos = c_pos - dpos * frictionCoefficient;  // apply friction

        c_pos.x = r;
        p_pos.x = c_pos.x + dpos.x * damping;
    }
    // Right wall
    if ((c_pos.x + r) >= width) {
        p_pos = c_pos - dpos * frictionCoefficient;  // apply friction

        c_pos.x = width - r;
        p_pos.x = c_pos.x + dpos.x * damping;
    }
    // Top wall (ceiling)
    if ((c_pos.y - r) <= 0.0) {
        p_pos = c_pos - dpos * frictionCoefficient;  // apply friction
        c_pos.y = r;
        p_pos.y = c_pos.y + dpos.y * damping;
    }
    // Bottom wall (floor)
    if ((c_pos.y + r) >= height) {
        p_pos = c_pos - dpos * frictionCoefficient;  // apply friction

        c_pos.y = height - r;
        p_pos.y = c_pos.y + dpos.y * damping;
    }
}

Vec2 Object::applyForces() {
	Vec2 gravity_acceleration = Vec2(0.0, 9.81);
	return gravity_acceleration;
}


void Object::printInfo() {
	// std::cout << "CP: " << c_pos << std::endl;
	// std::cout << "PP: " << p_pos << std::endl;
	std::cout << "VEL: " << c_pos - p_pos << std::endl;
	std::cout << "ACC: " << acc << std::endl;
	std::cout << std::endl;
}