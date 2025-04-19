#ifndef DEMO_HPP
#define DEMO_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include "world.hpp"

class Demo {
public:
    Demo(double width, double height);
    void run();

private:
    // Constants
    const double minDt = 1.0 / 60.0;

    // window and world settings
    double width, height;
    sf::RenderWindow window;
    sf::Clock deltaClock;
    World world{ width, height };

    // text and font for the UI
    sf::Font font;
    sf::Text fpsText;
    sf::Text objectCountText;

    // Core functions
    void processEvents();
    void update(double dt);
    void render();

    // drawing and control functions
    void drawObjects();
    void mouseControl();

    void drawCells();

    // helper functions
    void initialiseText(sf::Text& text, unsigned int charSize, sf::Vector2f position);
    bool isOverlapping(const Vec2& position, double radius) const;
    void updateFPS(uint32_t frameCount, double dt);
    sf::Color calculateColour(const Vec2& position) const;
};

#endif
