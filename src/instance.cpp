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

bool detect_lose(Tetromino tetromino)
{
    // if there are blocks in starting pos
    for(auto &b : tetromino.blocks)
    {
        sf::Vector2i spawning_pos = b.grid_pos;
        spawning_pos.x -= (PREVIEW_X - STARTING_X);
        spawning_pos.y -= PREVIEW_Y;

        if(Grid_Entry::has_entry(spawning_pos))
             return true;

    }
    return false;
}

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

        if(detect_lose(preview.preview))
            exit(0);

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
