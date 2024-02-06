#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "globals.h"

namespace Grid
{
// return the cocoordinate of grid position
sf::Vector2f at(int grid_x, int grid_y);

// check if the position is inside grid
bool is_valid_pos(sf::Vector2i);
}; // namespace Grid

class Score
{
    unsigned int points;
    sf::Text text;
    sf::Font font;

  public:
    Score();

    int get_points();
    void add_points(int amount);

    /// reset score to 0
    void reset_score();

    // draw the score at bottom right
    void draw();
};

class Block
{
public:
    sf::RectangleShape box = sf::RectangleShape({GRID_SIZE, GRID_SIZE});

    sf::Vector2i grid_pos;

    // set position to {0, 0} and color to White
    Block();

    // create a box in grid position
    Block(sf::Vector2i grid_pos, sf::Color color);

    // return grid position
    sf::Vector2i get_pos();

    // set grid position and
    // returns -1 on out of bound
    //          0 on successful move
    int set_pos(sf::Vector2i grid_pos);

    void set_color(sf::Color color);

    // draw to window
    void draw();
};

enum Direction {Left, Right, Down};
