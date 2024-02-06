#include <SFML/Graphics.hpp>

#include "components.h"
#include "tetromino.h"

extern Score score;

void key_handler(sf::Keyboard::Key key, Tetromino_Controller &block)
{
    // modifier keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            block.rotate(Rotation::CLOCKWISE);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            block.rotate(Rotation::ANTI_CLOCKWISE);
        return;
    }

    switch (key)
    {
    case sf::Keyboard::Key::Down:
        block.move(Direction::Down);
        break;

    case sf::Keyboard::Key::Left:
        block.move(Direction::Left);
        break;

    case sf::Keyboard::Key::Right:
        block.move(Direction::Right);
        break;

    case sf::Keyboard::Key::Space:
        block.new_shape();
        break;
    default:
        break;
    }
}
