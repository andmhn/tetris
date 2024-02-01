#include <sstream>

#include "components.h"
#include "globals.h"

extern sf::RenderWindow *window;

// TODO: check out of bound

sf::Vector2f Grid::at(int x, int y)
{
    return {float(x * GRID_SIZE), float(y * GRID_SIZE)};
}

void Grid::draw(sf::RectangleShape box)
{
    window->draw(box);
}

void Grid::draw(sf::RectangleShape box, int grid_x, int grid_y)
{
    box.setPosition(Grid::at(grid_x, grid_y));
    window->draw(box);
}

// -------  class Score------------------

Score::Score() : points(0)
{
    // load font
    font.loadFromFile("pixel_font.ttf");

    // Create a text
    text = sf::Text();
    text.setFont(font);
    text.setCharacterSize(40);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Green);

    // drawing position
    text.setPosition(10 * GRID_SIZE + 10, WINDOW_HEIGHT - (GRID_SIZE * 4));
}

int Score::get_points()
{
    return points;
}

void Score::add_points(int amount)
{
    points += amount;
}

void Score::reset_score()
{
    points = 0;
}

void Score::draw()
{
    std::ostringstream os;
    os << "score\n"
       << points;

    text.setString(os.str());

    window->draw(text);
}
