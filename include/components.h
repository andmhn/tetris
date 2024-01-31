#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "globals.h"

namespace Grid
{
// return the cocoordinate of grid position
sf::Vector2f at(int grid_x, int grid_y);

// Draw at given grid coordinate
void draw(sf::RectangleShape, int grid_x, int grid_y);

void draw(sf::RectangleShape box);

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
