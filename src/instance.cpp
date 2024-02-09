#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "components.h"
#include "globals.h"
#include "tetromino.h"
#include "grid_entry.h"

sf::RenderWindow *window;
sf::Clock clk;
Score score = Score();


void draw_border_col(int pos);
void draw_border_row(int pos);
void draw_grid_debug();

void key_handler(sf::Keyboard::Key key, Tetromino_Controller &block);

int instance()
{
    auto shape = Tetromino_Controller();
    auto preview = Tetromino_Preview();
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris",
                                  sf::Style::Close);
    window->setFramerateLimit(60);

    while (window->isOpen())
    {
        sf::Event evnt;
        while (window->pollEvent(evnt))
        {
            if (evnt.type == sf::Event::Closed)
                window->close();

            if (evnt.type == sf::Event::KeyPressed)
            {
                key_handler(evnt.key.code, shape);
            }
        }
        window->clear();

        draw_border_col(SEPERATOR_POS);

        // draw the active tetromino
        shape.draw();

        // display score
        score.draw();

        // display the preview of next tetromino
        preview.draw();

        // enable falling blocks
        if (static_cast<unsigned int>(clk.getElapsedTime().asMilliseconds()) > 1000)
        {
            if(!shape.has_block_finished())
                shape.move(Down);

            // spawn new block after time limit
            else
                 preview.submit_tetromino(shape);

            clk.restart();
        }

        // draw grid for debugging
        draw_grid_debug();
        window->display();
    }
    delete window;
    return 0;
}
