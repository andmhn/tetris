#include "tetromino.h"
#include "utils.h"

#include <iostream>

// u32bit color values
unsigned int Block_color[] = {
    15790335,   // bright_cyan
    61695,      // strong_blue
    4037017855, // yellowish_orange
    4042260735, // sunny_yellow
    15728895,   // green
    2684416255, // voilet
    4026532095  // red
};

Tetromino::Tetromino()
{
    shape = (Shape)random_no(0, 6);
    parse_block_str(get_block_str());
    set_color(sf::Color(Block_color[shape]));
}

void Tetromino::draw()
{
    for (auto &b : block)
        b.draw();
}

void Tetromino::set_color(sf::Color color)
{
    for (auto &b : block)
        b.set_color(color);
}

void Tetromino::parse_block_str(std::string str)
{
    int block_i = 0;
    int str_i = 0;

    for (int col = 0; col < 4; col++)
    {
        for (int row = 3; row < 7; row++)
        {
            if (str[str_i] == '*')
            {
                block[block_i].set_pos({row, col});
                block_i++;
            }
            str_i++;
        }
    }
}

std::string Tetromino::get_block_str()
{
    switch (shape)
    {
    case I:
        return "..*."
               "..*."
               "..*."
               "..*.";
    case J:
        return "..*."
               "..*."
               ".**."
               "....";
    case L:
        return ".*.."
               ".*.."
               ".**."
               "....";
    case Q:
        return ".**."
               ".**."
               "...."
               "....";
    case S:
        return ".**."
               "**.."
               "...."
               "....";
    case T:
        return "***."
               ".*.."
               "...."
               "....";
    case Z:
        return ".**."
               "..**"
               "...."
               "....";
    }
    return "";
}
