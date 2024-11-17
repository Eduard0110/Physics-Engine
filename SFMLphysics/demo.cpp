#include "demo.hpp"

// constructor
Demo::Demo(double width, double height)
    : width(width), height(height), window(sf::VideoMode(width, height), "Physics Simulation") {

    // initialize window settings
    window.setVerticalSyncEnabled(true);

    // load font and initialise text objects
    initialiseText(fpsText, 20, { 10.f, 10.f });
    initialiseText(objectCountText, 20, { 10.f, 40.f });
}

// mouse control for adding objects
void Demo::mouseControl() {
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<double> distXY(-1.0, 1.0);
    std::uniform_real_distribution<double> distRadius(5.0, 25.0);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        Vec2 newPosition(pos.x, pos.y);
        double newRadius = distRadius(rng);

        // Check for overlapping objects before adding
        if (!isOverlapping(newPosition, newRadius)) {
            world.addObject(
                newPosition,                                  // current position
                newPosition - Vec2(distXY(rng), distXY(rng)), // previous position (randomized velocity)
                Vec2(0.0, 0.0),                               // acceleration
                newRadius                                     // random radius
            );
        }
    }
}

void Demo::run() {
    uint32_t frameCount = 0;

    while (window.isOpen()) {
        frameCount++;
        processEvents();
        mouseControl();

        double dt = deltaClock.restart().asSeconds();
        updateFPS(frameCount, dt);
        update(std::min(dt, minDt));  // limit dt to avoid large changes in dt
        render();
    }
}

// handle events
void Demo::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

// update world
void Demo::update(double dt) {
    world.update(dt);
}

// Draw objects in the world
void Demo::drawObjects() {
    for (const auto& obj : world.m_objects) {
        sf::CircleShape circle(obj.r);
        circle.setPosition(obj.c_pos.x - obj.r, obj.c_pos.y - obj.r); // Adjust for radius
        circle.setFillColor(calculateColour(obj.c_pos));
        window.draw(circle);
    }
}

// render window
void Demo::render() {
    window.clear();
    drawObjects();
    window.draw(fpsText);
    window.draw(objectCountText);
    window.display();
}

// initialize text objects
void Demo::initialiseText(sf::Text& text, unsigned int charSize, sf::Vector2f position) {
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::White);
    text.setPosition(position);
}

// check for overlap with existing objects
bool Demo::isOverlapping(const Vec2& position, double radius) const {
    for (const Object& obj : world.m_objects) {
        if (obj.c_pos.Distance(position) < (obj.r + radius)) {
            return true;
        }
    }
    return false;
}

// update FPS
void Demo::updateFPS(uint32_t frameCount, double dt) {
    double fps = 1.0 / dt;
    if (frameCount % 30 == 0) {
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
    }
    objectCountText.setString("Objects: " + std::to_string(world.m_objects.size()));
}

// calculate colour based on object position
sf::Color Demo::calculateColour(const Vec2& position) const {
    float xRatio = position.x / width;
    float yRatio = position.y / height;

    sf::Uint8 red = static_cast<sf::Uint8>(255 * xRatio);
    sf::Uint8 green = static_cast<sf::Uint8>(255 * yRatio);
    sf::Uint8 blue = static_cast<sf::Uint8>(255 * (1.0f - xRatio));

    return sf::Color(red, green, blue);
}
