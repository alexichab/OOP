#include "shapes.hpp"
#include <SFML/Graphics.hpp>
#include <time.h>

#define FIGURS 1

int main(void)
{
    srand(time(NULL));
    sf::Vector2i win(720, 480);
    sf::RenderWindow window(sf::VideoMode(win.x, win.y), "human");

    Human shapes(10.0);
    // Human shapes;
    std::vector<Shape *> child = shapes.getChild();

    shapes.setPosition(rand() % win.x, rand() % win.y);
    shapes.moveElements(&shapes);

    // sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
            if (e.type == sf::Event::Closed)
                window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            shapes.control(win, LEFT, &shapes);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            shapes.control(win, RIGHT, &shapes);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            shapes.control(win, TOP, &shapes);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            shapes.control(win, BOT, &shapes);

        window.clear(sf::Color::Black);

        window.draw(shapes);
        for (int i = 0; i < 5; i++)
            window.draw(*child[i]);

        window.display();
    }
    return EXIT_SUCCESS;
}