#pragma once

#include "components.h"

enum Shape {I, J, L, Q, S, T, Z};
enum Rotation {CLOCKWISE, ANTI_CLOCKWISE};

#define STARTING_X 3

class Tetromino
{
private:
    Shape shape;
    Block block[4];

    // store string representation of block
    std::string shape_str;

    // tracks the position of block str
    sf::Vector2i curr_pos = {STARTING_X, 0};


    void set_color(sf::Color color);
    static std::string get_block_str(Shape);
    void parse_block_str(std::string);
    bool is_valid_block_pos(std::string);

    // increment from current position
    int inc_position(sf::Vector2i);

public:
    Tetromino();
    void draw();
    int move(Direction);
    void rotate(Rotation);
};
