#include <SFML/Graphics.hpp>

#include "components.h"
#include "tetromino.h"

extern Score score;

void key_handler(sf::Keyboard::Key key, Tetromino &block)
{
    switch (key)
    {

    case sf::Keyboard::Key::Down:
    {
        block.move(Direction::Down);
        break;
    }

    case sf::Keyboard::Key::Left:
    {
        block.move(Direction::Left);
        break;
    }

    case sf::Keyboard::Key::Right:
    {
        block.move(Direction::Right);
        break;
    }

    case sf::Keyboard::Key::A:
    {
        score.add_points(1);
        break;
    }
    case sf::Keyboard::Key::S:
    {
        score.reset_score();
        break;
    }
    // TODO: use key modifier
    case sf::Keyboard::Key::Q:
    {
        block.rotate(Rotation::ANTI_CLOCKWISE);
        break;
    }
    case sf::Keyboard::Key::W:
    {
        block.rotate(Rotation::CLOCKWISE);
        break;
    }

    default:
        break;
    }
}
