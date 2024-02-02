#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "components.h"
#include "globals.h"

sf::RenderWindow *window;
Score score = Score();

void draw_border_col(int pos, sf::Color color);
void draw_border_row(int pos, sf::Color color);
void draw_border_col(int pos);
void draw_border_row(int pos);
void draw_grid_debug();

void key_handler(sf::Keyboard::Key key, Block &box);

int instance()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris",
                                  sf::Style::Close);
    window->setFramerateLimit(60);

    auto box = Block({4, 19}, sf::Color::Cyan);

    while (window->isOpen())
    {
        sf::Event evnt;
        while (window->pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window->close();

            if (evnt.type == sf::Event::KeyPressed)
            {
                key_handler(evnt.key.code, box);
            }
        }
        window->clear();

        box.draw();

        draw_border_col(SEPERATOR_POS);
        draw_grid_debug();

        score.draw();

        window->display();
    }
    delete window;
    return 0;
}
