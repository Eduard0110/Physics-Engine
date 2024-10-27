#ifndef DEMO_HPP
#define DEMO_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include "world.hpp"

class Demo {
public:
    Demo(int width, int height);
    void run();

private:
    double minDt = 1.0 / 60.0;
    int width, height;

    sf::RenderWindow window;
    sf::Clock deltaClock;
    World world = World(width, height);


    void processEvents();
    void update(double dt);
    void drawObjects();
    void render();
};

#endif
