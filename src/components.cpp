#include <sstream>

#include "components.h"
#include "globals.h"

extern sf::RenderWindow *window;

#include "grid_entry.h"

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
        Grid_Entry::has_entry(pos))
    {
        return false;
    }

    return true;
}

// -------  class Score------------------

Score::Score() : rows(0), prev_rows(0), points(0)
{
    // load font
    font.loadFromFile("pixel_font.ttf");

    // Create a text
    text = sf::Text();
    text.setFont(font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);
    text.setFillColor(sf::Color::Yellow);

    // set position below of tetromino preview
    text.setPosition((10 * GRID_SIZE + 10), (GRID_SIZE * 10));
}

int Score::get_points()
{
    return points;
}

void Score::add_points(int rows_cleared)
{
    // Scoring System:
    // add points per rows cleared
    //(50, 150, 450, or 900), 900+500 = 1400
    switch (rows_cleared)
    {
    case 1:
        points += 50;
        break;
    case 2:
        points += 150;
        break;
    case 3:
        points += 450;
        break;
    case 4:
        points += 900;  // Tetris
        break;
    default:
        return;
    }

    // back-to-back Tetris
    if(prev_rows == 4 && rows_cleared == 4)
        points += 500;

    prev_rows = rows_cleared;
    rows += rows_cleared;
}

void Score::reset()
{
    points = 0;
}

void Score::draw()
{
    std::ostringstream os;
    os << "rows\n"
       << rows
       << "\n\n"
       << "score\n"
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

    set_pos_forced(pos);
    return 0;
}
void Block::set_pos_forced(sf::Vector2i pos)
{
    grid_pos = pos;
    box.setPosition(Grid::at(grid_pos.x, grid_pos.y));
}

void Block::set_color(sf::Color color)
{
    box.setFillColor(color);
}

void Block::draw()
{
    window->draw(box);
}
