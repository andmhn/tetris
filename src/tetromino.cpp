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
    shape_str = get_block_str(shape);

    parse_block_str(shape_str);

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

    for (int col = curr_pos.y; col < curr_pos.y + 4; col++)
    {
        for (int row = curr_pos.x; row < curr_pos.x + 4; row++)
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

std::string Tetromino::get_block_str(Shape shape)
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

int Tetromino::inc_position(sf::Vector2i increase)
{
    for (auto &b : block)
    {
        if (!Grid::is_valid_pos(b.get_pos() + increase))
            return -1;
    }
    for (auto &b : block)
    {
        b.set_pos(b.get_pos() + increase);
    }
    curr_pos += increase;
    return 0;
}

int Tetromino::move(Direction dir)
{
    std::cout << curr_pos.x << "\t" << curr_pos.y << "\n";
    switch (dir)
    {
    case Direction::Left:
        return inc_position({-1, 0});
        break;

    case Direction::Right:
        return inc_position({1, 0});
        break;

    case Direction::Down:
        return inc_position({0, 1});
        break;
    }
    return -1;
}

void Tetromino::rotate(Rotation r)
{
    // TODO: only allow valid rotation
    //       do not rotate cube
    switch (r)
    {
    case Rotation::CLOCKWISE:
        shape_str = left_rotate(shape_str, 4);
        parse_block_str(shape_str);
        break;

    case Rotation::ANTI_CLOCKWISE:
        shape_str = right_rotate(shape_str, 4);
        parse_block_str(shape_str);
        break;
    }
}
