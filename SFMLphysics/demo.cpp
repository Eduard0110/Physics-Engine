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

void Demo::dragObject() {
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    Vec2 mouseWorldPos(mousePixelPos.x, mousePixelPos.y);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        if (!isDragging) {
            // Try to pick an object to drag
            for (auto& obj : world.m_objects) {
                if (!obj->isStatic && obj->c_pos.Distance(mouseWorldPos) < obj->r) {
                    draggedObject = obj.get();
                    isDragging = true;
                    break;
                }
            }
        }
        else if (draggedObject) {
            // While dragging: move the object to the mouse position
            draggedObject->c_pos = mouseWorldPos;
            draggedObject->p_pos = mouseWorldPos;  // Prevent sudden velocity
        }
    }
    else {
        // On mouse release
        isDragging = false;
        draggedObject = nullptr;
    }
}

void Demo::removeObjects() {
    // Get mouse position in world coordinates
    sf::Vector2i mousePosPixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosPixel);
    Vec2 mouse(mousePosWorld.x, mousePosWorld.y);

    // Find objects under the cursor
    std::vector<Object*> objectsToRemove;
    for (const auto& obj : world.m_objects) {
        if ((obj->c_pos - mouse).Length() < obj->r) {
            objectsToRemove.push_back(obj.get());
        }
    }

    if (objectsToRemove.empty()) return;  // Nothing to delete

    // Remove related links
    world.m_links.erase(
        std::remove_if(world.m_links.begin(), world.m_links.end(),
            [&](const Link& link) {
                return std::find(objectsToRemove.begin(), objectsToRemove.end(), link.A) != objectsToRemove.end() ||
                    std::find(objectsToRemove.begin(), objectsToRemove.end(), link.B) != objectsToRemove.end();
            }),
        world.m_links.end()
    );

    // Remove the objects themselves
    world.m_objects.erase(
        std::remove_if(world.m_objects.begin(), world.m_objects.end(),
            [&](const std::unique_ptr<Object>& obj) {
                return std::find(objectsToRemove.begin(), objectsToRemove.end(), obj.get()) != objectsToRemove.end();
            }),
        world.m_objects.end()
    );
}

void Demo::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::C:
            clear_all();
            break;
        case sf::Keyboard::S:
            clear_all();
            create_cloth(12 * 8, 35 * 8);
            break;
        case sf::Keyboard::Num1:
            world.b_Collisions = !world.b_Collisions;
            break;
        case sf::Keyboard::Num2:
            world.b_drawObjects = !world.b_drawObjects;
            break;
        case sf::Keyboard::Num3:
            world.b_drawLinks = !world.b_drawLinks;
            break;
        case sf::Keyboard::Num4:
            world.b_subSteps = !world.b_subSteps;
            break;
        default:
            break;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
        removeObjects();
    }
}

void Demo::clear_all() {
    world.m_objects.clear();
    world.m_links.clear();
}

void Demo::create_cloth(int rows, int columns, float step, int static_step, Vec2 initial_pos, double ball_r) {
    std::cout << "Creating cloth..." << std::endl;
    int startIndex = static_cast<int>(world.m_objects.size());

    // Create the balls and add them to the world
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            Vec2 ball_pos(initial_pos.x + j * step, initial_pos.y + i * step);
            world.addObject(ball_pos, ball_pos, Vec2(0.0f, 0.0f), ball_r);
        }
    }

    // Set top row objects to static
    for (int j = 0; j < columns; ++j) {
        world.m_objects[startIndex + j]->isStatic = true;
    }

    // Create horizontal connections
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns - 1; ++j) {
            Object* A = world.m_objects[startIndex + i * columns + j].get();
            Object* B = world.m_objects[startIndex + i * columns + j + 1].get();
            world.addLink(A, B, 20);
        }
    }

    // Create vertical connections
    for (int i = 0; i < rows - 1; ++i) {
        for (int j = 0; j < columns; ++j) {
            Object* A = world.m_objects[startIndex + i * columns + j].get();
            Object* B = world.m_objects[startIndex + (i + 1) * columns + j].get();
            world.addLink(A, B, 20);
        }
    }
}

void Demo::updateTitle() {
    std::string space = "               ";
    std::string title;

    title += "Collisions (Press 1) :   " + std::string(world.b_Collisions ? "On" : "Off") + space;
    title += "Draw Objects (Press 2) :   " + std::string(world.b_drawObjects ? "On" : "Off") + space;
    title += "Draw Links (Press 3) :   " + std::string(world.b_drawLinks ? "On" : "Off") + space;
    title += "Sub Steps (Press 4) :   " + std::string(world.b_subSteps ? "On" : "Off") + space;
    title += "Clear :   Press C" + space;
    title += "Create Cloth :   Press S" + space;

    window.setTitle(title);
}

// main run loop
void Demo::run() {
    uint32_t frameCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            handleInput(event);
        }

        frameCount++;
        mouseControl();
        dragObject();
        updateTitle();

        sf::Time delta = deltaClock.restart();
        double dt = delta.asSeconds();
        updateFPS(frameCount, dt);
        update(std::min(dt, minDt));  // Limit dt to avoid large changes
        render();  // Render the scene
    }
}

// update world
void Demo::update(double dt) {
    world.update(dt);
}

// Draw objects in the world
void Demo::drawObjects() {
    for (const auto& obj : world.m_objects) {
        sf::CircleShape circle(obj->r);
        circle.setPosition(obj->c_pos.x - obj->r, obj->c_pos.y - obj->r);

        Vec2 velocity = obj->c_pos - obj->p_pos;
        double speed = velocity.Length();

        double maxSpeed = 2.0;
        double t = std::min(speed / maxSpeed, 1.0);

        sf::Uint8 red = static_cast<sf::Uint8>(t * 255);
        sf::Uint8 blue = static_cast<sf::Uint8>((1.0 - t) * 255);

        circle.setFillColor(sf::Color(red, 0, blue));
        window.draw(circle);
    }
}

void Demo::drawLinks() {
    for (const auto& link : world.m_links) {
        const Vec2& posA = link.A->c_pos;
        const Vec2& posB = link.B->c_pos;

        double distance = (posA - posB).Length();
        double maxDistance = 100.0;
        double normalized = std::min(distance / maxDistance, 1.0);

        sf::Uint8 red = static_cast<sf::Uint8>(255 * normalized);
        sf::Uint8 blue = static_cast<sf::Uint8>(255 * (1.0 - normalized));

        sf::Color linkColor(red, 0, blue);

        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(posA.x, posA.y), linkColor),
            sf::Vertex(sf::Vector2f(posB.x, posB.y), linkColor)
        };

        window.draw(line, 2, sf::Lines);
    }
}

// render window
void Demo::render() {
    window.clear();
    if (world.b_drawObjects) drawObjects();
    if (world.b_drawLinks) drawLinks();
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
    for (const auto& obj : world.m_objects) {
        if (obj->c_pos.Distance(position) < (obj->r + radius)) {
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
