#pragma once

#include "components.h"

enum Shape {I, J, L, Q, S, T, Z};

class Tetromino
{
private:
    Shape shape;
    Block block[4];
    Block block_temp[4];

    void set_color(sf::Color color);
    std::string get_block_str();
    void parse_block_str(std::string);

public:
    Tetromino();
    void draw();
    void move(Direction);
    //TODO: rotation
};
