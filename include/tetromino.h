#pragma once

#include "components.h"

enum Shape {I, J, L, Q, S, T, Z};

class Tetromino
{
private:
    Shape shape;
    Block block[4];

    void set_color(sf::Color color);
    std::string get_block_str();
    void parse_block_str(std::string);

    // increment from current position
    int inc_position(sf::Vector2i);

public:
    Tetromino();
    void draw();
    int move(Direction);
    //TODO: rotation
};
