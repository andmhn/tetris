#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int instance()
{
    sf::RenderWindow window(sf::VideoMode(300, 200), "Tetris",
                            sf::Style::Close);

    window.setPosition({10, 10});

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        window.display();
    }
    return 0;
}
