#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "components.h"
#include "globals.h"
#include "tetromino.h"

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

    auto shape_I = Tetromino();

    while (window->isOpen())
    {
        sf::Event evnt;
        while (window->pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window->close();

            if (evnt.type == sf::Event::KeyPressed)
            {
                // key_handler(evnt.key.code, box);
            }
        }
        window->clear();

        draw_border_col(SEPERATOR_POS);
        draw_grid_debug();

        shape_I.draw();

        score.draw();

        window->display();
    }
    delete window;
    return 0;
}
