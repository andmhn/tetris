#include "tetromino.h"
#include "utils.h"

#include <iostream>

#include "grid_entry.h"

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

RandomStream tetromino_stream_(0, 6);

Tetromino_Controller::Tetromino_Controller()
{
    init_shape((Shape)tetromino_stream_.rand());
}

void Tetromino_Controller::init_shape(Shape s)
{
    shape = s;
    shape_str = get_block_str(shape);

    parse_block_str(shape_str);

    set_color(sf::Color(Block_color[shape]));
}

void Tetromino_Controller::new_shape(Shape s)
{
    curr_pos = {STARTING_X, 0};

    // store old blocks
    for (auto &b : curr_tetromino.blocks)
        Grid_Entry::entry(b);

    // scan completed rows now
    Grid_Entry::scan_row();

    init_shape(s);
}

void Tetromino_Controller::draw()
{
    for (auto &b : curr_tetromino.blocks)
        b.draw();

    Grid_Entry::draw();
}

void Tetromino_Controller::set_color(sf::Color color)
{
    for (auto &b : curr_tetromino.blocks)
        b.set_color(color);
}

void Tetromino_Controller::parse_block_str(std::string str, Tetromino &tetromino, sf::Vector2i &pos)
{
    int block_i = 0;
    int str_i = 0;

    for (int col = pos.y; col < pos.y + 4; col++)
    {
        for (int row = pos.x; row < pos.x + 4; row++)
        {
            if (str[str_i] == '*')
            {
                tetromino.blocks[block_i].set_pos_forced({row, col});
                block_i++;
            }
            str_i++;
        }
    }
}

void Tetromino_Controller::parse_block_str(std::string str)
{
    parse_block_str(str, curr_tetromino, curr_pos);
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

bool Tetromino_Controller::has_block_finished()
{
    for (auto b : curr_tetromino.blocks)
    {
        auto pos = b.get_pos();

        // collision with other blocks
        if (Grid_Entry::has_entry({pos.x, pos.y + 1}))
            return true;

        // collision with ground
        if (pos.y == GRID_Y - 1)
            return true;
    }
    return false;
}

//---------------------- Tetromino_Preview ------------------------------

Tetromino_Preview::Tetromino_Preview()
{
    create();
}

void Tetromino_Preview::create()
{
    sf::Vector2i pos = {PREVIEW_X, PREVIEW_Y};
    shape = (Shape)tetromino_stream_.rand();
    std::string shape_str = Tetromino_Controller::get_block_str(shape);

    Tetromino_Controller::parse_block_str(shape_str, preview, pos);

    for (auto &b : preview.blocks)
        b.set_color(sf::Color(Block_color[shape]));
}

void Tetromino_Preview::draw()
{
    for (auto &b : preview.blocks)
        b.draw();
}

void Tetromino_Preview::submit_tetromino(Tetromino_Controller &controller)
{
    controller.new_shape(shape);
    create();
}
