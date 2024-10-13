// A demo of the physics library, using SMFL to display objects


#include <main.hpp>

int main()
{   
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Physics Simulation");
    // Physics Simulation related
    sf::Clock deltaClock;
    World world;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time dt = deltaClock.restart();
        world.update(dt.asSeconds());
        std::cout << dt.asSeconds() << std::endl;

        window.clear();
        window.display();
    }

    return 0;
}