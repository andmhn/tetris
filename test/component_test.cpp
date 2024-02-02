#include "doctest.h"

#include "components.h"

template <typename T>
bool vec2_cmp(sf::Vector2<T> vec1, sf::Vector2<T> vec2)
{
    if (vec1.x == vec2.x &&
        vec1.y == vec2.y)
        return true;
    return false;
}

TEST_CASE("testing the Grid::at() return values")
{
    CHECK(vec2_cmp(Grid::at(3, 5), {3 * GRID_SIZE, 5 * GRID_SIZE}));
    CHECK(!vec2_cmp(Grid::at(3, 5), {2 * GRID_SIZE, 5 * GRID_SIZE}));
}

TEST_CASE("testing the Grid::is_valid_pos")
{
    // valid position
    CHECK(Grid::is_valid_pos({0, 0}) == true);
    CHECK(Grid::is_valid_pos({5, 5}) == true);
    CHECK(Grid::is_valid_pos({9, 1}) == true);
    CHECK(Grid::is_valid_pos({9, 19}) == true);
    CHECK(Grid::is_valid_pos({0, 19}) == true);

    // invalid position
    CHECK(Grid::is_valid_pos({15, 5}) == false);
    CHECK(Grid::is_valid_pos({-1, 5}) == false);
    CHECK(Grid::is_valid_pos({5, -1}) == false);
    CHECK(Grid::is_valid_pos({-1, -1}) == false);
    CHECK(Grid::is_valid_pos({10, 5}) == false);
    CHECK(Grid::is_valid_pos({10, 20}) == false);
    CHECK(Grid::is_valid_pos({-5, -6}) == false);
}

TEST_CASE("Testing Score functionality")
{
    auto score = Score();
    CHECK(score.get_points() == 0);

    for (int i = 1; i < 10; i++)
    {
        score.add_points(1);
        CHECK(score.get_points() == i);
    }

    score.reset_score();
    CHECK(score.get_points() == 0);
}

sf::Vector2i pos = {8, 0};
auto block = Block(pos, sf::Color::Black);

TEST_CASE("Testing Block class")
{

    CHECK(vec2_cmp(block.get_pos(), {8, 0}));

    pos.x++;
    block.set_pos(pos);
    CHECK(vec2_cmp(block.get_pos(), {9, 0}));
}

TEST_CASE("testing Block out of bound")
{
    pos.x++;
    block.set_pos(pos);
    CHECK(!vec2_cmp(block.get_pos(), {10, 0}));

    block.set_pos({0, -1});
    CHECK(!vec2_cmp(block.get_pos(), {0, -1}));

    block.set_pos({10, 0});
    CHECK(!vec2_cmp(block.get_pos(), {0, -1}));
}

TEST_CASE("old Block position remains unchanged with out of bounary value")
{
    block.set_pos({0, 0});

    block.set_pos({0, 20});
    CHECK(vec2_cmp(block.get_pos(), {0, 0}));

    block.set_pos({10, 20});
    CHECK(vec2_cmp(block.get_pos(), {0, 0}));

    block.set_pos({-1, -1});
    CHECK(vec2_cmp(block.get_pos(), {0, 0}));
}
