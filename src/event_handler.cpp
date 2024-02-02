#include <SFML/Graphics.hpp>

#include "components.h"

extern Score score;

void key_handler(sf::Keyboard::Key key, Block &box)
{
    switch (key)
    {
    // TODO: should be removed
    case sf::Keyboard::Key::Up:
    {
        auto pos = box.get_pos();
        pos.y--;
        box.set_pos(pos);
        break;
    }
    case sf::Keyboard::Key::Down:
    {
        auto pos = box.get_pos();
        pos.y++;
        box.set_pos(pos);
        break;
    }

    case sf::Keyboard::Key::Left:
    {
        auto pos = box.get_pos();
        pos.x--;
        box.set_pos(pos);
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

    case sf::Keyboard::Key::Right:
    {
        auto pos = box.get_pos();
        pos.x++;
        box.set_pos(pos);
        break;
    }

    default:
        break;
    }
}
