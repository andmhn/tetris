#include <sstream>

#include "components.h"
#include "globals.h"

extern sf::RenderWindow *window;

extern bool GRID_INDEX[GRID_X][GRID_Y];

// ------- namespace Grid ---------------

sf::Vector2f Grid::at(int x, int y)
{
    return {float(x * GRID_SIZE), float(y * GRID_SIZE)};
}

bool Grid::is_valid_pos(sf::Vector2i pos)
{
    if (pos.x < 0 ||
        pos.y < 0 ||
        pos.x > GRID_X - 1 ||
        pos.y > GRID_Y - 1 ||
        GRID_INDEX[pos.x][pos.y] == true)
    {
        return false;
    }

    return true;
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

//---------- class Block ----------

Block::Block()
    : grid_pos({0, 0})
{
    box.setFillColor(sf::Color::White);
    set_pos(grid_pos);
}

Block::Block(sf::Vector2i grid_pos, sf::Color color)
    : grid_pos(grid_pos)
{
    box.setFillColor(color);
    set_pos(grid_pos);
}

sf::Vector2i Block::get_pos()
{
    return grid_pos;
}

int Block::set_pos(sf::Vector2i pos)
{
    if (!Grid::is_valid_pos(pos))
        return -1;

    grid_pos = pos;
    box.setPosition(Grid::at(grid_pos.x, grid_pos.y));
    return 0;
}

void Block::set_color(sf::Color color)
{
    box.setFillColor(color);
}

void Block::draw()
{
    window->draw(box);
}
