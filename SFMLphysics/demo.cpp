#include "demo.hpp"


Demo::Demo(int width, int height) : width(width), height(height), window(sf::VideoMode(width, height), "Physics Simulation") {
    window.setVerticalSyncEnabled(true);

    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> posDistX(0.0, width);   // random x position
    std::uniform_real_distribution<> posDistY(0.0, height);  // random y position
    std::uniform_real_distribution<> radiusDist(5.0, 20.0);  // random radius between 5 and 20
    std::uniform_real_distribution<> velDist(-50.0, 50.0);   // random velocity between -50 and 50 for x and y

    // Create multiple random bouncing balls
    int numberOfBalls = 10;
    for (int i = 0; i < numberOfBalls; ++i) {
        double radius = radiusDist(gen);
        Vec2 position(posDistX(gen), posDistY(gen));
        Vec2 previousPosition(position.x + velDist(gen) * 0.1,
            position.y + velDist(gen) * 0.1);
        Vec2 acceleration(velDist(gen), velDist(gen));

        world.addObject(position, previousPosition, acceleration, radius);
    }
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

        // normalize ratios
        float xRatio = obj.c_pos.x / window.getSize().x;
        float yRatio = obj.c_pos.y / window.getSize().y;
        // the colour changes depending on position
        sf::Uint8 red = static_cast<sf::Uint8>(255 * xRatio);
        sf::Uint8 green = static_cast<sf::Uint8>(255 * yRatio);
        sf::Uint8 blue = static_cast<sf::Uint8>(255 * (1.0f - xRatio));

        sf::Color colour = sf::Color(red, green, blue);

        circle.setFillColor(colour);
        window.draw(circle);
    }
}


void Demo::render() {
    window.clear();
    drawObjects();
    window.display();
}
