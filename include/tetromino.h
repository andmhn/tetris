#pragma once

#include "components.h"

enum Shape {I, J, L, Q, S, T, Z};
enum Rotation {CLOCKWISE, ANTI_CLOCKWISE};

#define STARTING_X 3

class Tetromino
{
public:
    Block blocks[4];
};

class Tetromino_Controller
{
private:
    Shape shape;
    Tetromino curr_tetromino;

    // store string representation of block
    std::string shape_str;

    // tracks the position of block str
    sf::Vector2i curr_pos = {STARTING_X, 0};


    void set_color(sf::Color color);

    // wrapper for static function
    void parse_block_str(std::string);

    bool is_valid_block_pos(std::string);

    // increment from current position
    int inc_position(sf::Vector2i);

    void init_shape(Shape);

public:
    Tetromino_Controller();
    void draw();
    int move(Direction);
    void rotate(Rotation);

    void new_shape(Shape);

    bool has_block_finished();

    static std::string get_block_str(Shape);

    // parse tetromino string and set position
    static void parse_block_str(std::string str, Tetromino &, sf::Vector2i & pos);

};


// sidebar preview of next tetromino
class Tetromino_Preview
{
    Shape shape;

    void create();

public:
    Tetromino preview;

    Tetromino_Preview();
    void draw();
    void submit_tetromino(Tetromino_Controller &);
};

