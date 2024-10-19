#include "demo.hpp"

Demo::Demo(int width, int height) : width(width), height(height), window(sf::VideoMode(width, height), "Physics Simulation") {
    window.setVerticalSyncEnabled(true);
    // create a small bouncing ball
    world.addObject(
        Vec2(width / 2., height / 2.),  // Position
        Vec2(width / 2.+6.0, height / 2.+1.0),  // Previous Position
        Vec2(1.0, 0.0),                 // Acceleration
        10.0                            // Radius
    );
}

void Demo::run() {
    while (window.isOpen()) {
        processEvents();
        double dt = (double) deltaClock.restart().asSeconds();
        dt = std::min(dt, minDt);  // Now both are double
        update(dt);
        render();
    }
}

void Demo::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Demo::update(double dt) {
    world.update(dt);
    world.m_objects[0].printInfo();
}

void Demo::drawObjects() {
    for (const auto& obj : world.m_objects) {
        sf::CircleShape circle(obj.r);
        circle.setPosition(obj.c_pos.x - obj.r, obj.c_pos.y - obj.r); // set the position (adjusting for radius)
        circle.setFillColor(sf::Color::White);
        window.draw(circle);
    }
}

void Demo::render() {
    window.clear();
    drawObjects();
    window.display();
}
