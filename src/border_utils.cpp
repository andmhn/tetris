#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "globals.h"

extern sf::RenderWindow window;

void draw_border_col(int pos, sf::Color color)
{
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(pos, 0), color),
        sf::Vertex(sf::Vector2f(pos, WINDOW_HEIGHT), color)};

    window.draw(line, 2, sf::Lines);
}

void draw_border_row(int pos, sf::Color color)
{
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(0, pos), color),
        sf::Vertex(sf::Vector2f(GRID_SIZE * GRID_X, pos), color)};

    window.draw(line, 2, sf::Lines);
}

void draw_border_col(int pos) { draw_border_col(pos, sf::Color::Yellow); }
void draw_border_row(int pos) { draw_border_row(pos, sf::Color::Yellow); }

void draw_grid_debug()
{
    auto color = sf::Color(255, 255, 255, 100);

    // draw rows
    for (int i = 0; i < GRID_Y; i++)
        draw_border_row(i * GRID_SIZE, color);

    // draw cols
    for (int i = 0; i < GRID_X; i++)
        draw_border_col(i * GRID_SIZE, color);
}
