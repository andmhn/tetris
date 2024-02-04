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

Tetromino_Controller::Tetromino_Controller()
{
    init_shape();
}

void Tetromino_Controller::init_shape()
{
    shape = (Shape)random_no(0, 6);
    shape_str = get_block_str(shape);

    parse_block_str(shape_str);

    set_color(sf::Color(Block_color[shape]));
}

void Tetromino_Controller::new_shape()
{
    prev_tetrominoes.push_back(curr_tetromino);
    curr_pos = {STARTING_X, 0};
    for (auto &b : curr_tetromino.blocks)
        b.index_pos();

    init_shape();
}

void Tetromino_Controller::draw()
{
    for (auto &b : curr_tetromino.blocks)
        b.draw();

    for (auto &t : prev_tetrominoes)
        for (auto &b : t.blocks)
        {
            b.draw();
        }
}

void Tetromino_Controller::set_color(sf::Color color)
{
    for (auto &b : curr_tetromino.blocks)
        b.set_color(color);
}

void Tetromino_Controller::parse_block_str(std::string str)
{
    int block_i = 0;
    int str_i = 0;

    for (int col = curr_pos.y; col < curr_pos.y + 4; col++)
    {
        for (int row = curr_pos.x; row < curr_pos.x + 4; row++)
        {
            if (str[str_i] == '*')
            {
                curr_tetromino.blocks[block_i].set_pos({row, col});
                block_i++;
            }
            str_i++;
        }
    }
}

std::string Tetromino_Controller::get_block_str(Shape shape)
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

int Tetromino_Controller::inc_position(sf::Vector2i increase)
{
    for (auto &b : curr_tetromino.blocks)
    {
        if (!Grid::is_valid_pos(b.get_pos() + increase))
            return -1;
    }
    for (auto &b : curr_tetromino.blocks)
    {
        b.set_pos(b.get_pos() + increase);
    }
    curr_pos += increase;
    return 0;
}

int Tetromino_Controller::move(Direction dir)
{
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

void Tetromino_Controller::rotate(Rotation r)
{
    // Do not rotate cube
    if (shape == Shape::Q)
        return;

    std::string temp_str;
    switch (r)
    {
    case Rotation::CLOCKWISE:
        temp_str = right_rotate(shape_str, 4);

        if (is_valid_block_pos(temp_str))
        {
            shape_str = temp_str;
            parse_block_str(shape_str);
        }
        break;

    case Rotation::ANTI_CLOCKWISE:
        temp_str = left_rotate(shape_str, 4);

        if (is_valid_block_pos(temp_str))
        {
            shape_str = temp_str;
            parse_block_str(shape_str);
        }
        break;
    }
}

bool Tetromino_Controller::is_valid_block_pos(std::string str)
{
    int str_i = 0;
    for (int col = curr_pos.y; col < curr_pos.y + 4; col++)
        for (int row = curr_pos.x; row < curr_pos.x + 4; row++, str_i++)
            if (str[str_i] == '*' &&
                !Grid::is_valid_pos({row, col}))
                return false;
    return true;
}
