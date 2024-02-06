#include "grid_entry.h"

extern Score score;

namespace BLOCK_INDEX_
{
// it will only track all of still blocks
bool GRID_[GRID_X][GRID_Y] = {{0}};

// stores blocks
Block INDEX_[GRID_X][GRID_Y];

bool has_entry(sf::Vector2i pos)
{
    return GRID_[pos.x][pos.y];
}

void delete_entry(sf::Vector2i pos)
{
    GRID_[pos.x][pos.y] = false;
}

void update_entry(Block b)
{
    GRID_[b.grid_pos.x][b.grid_pos.y] = true;

    INDEX_[b.grid_pos.x][b.grid_pos.y] = b;
}

Block get_entry(sf::Vector2i pos)
{
    return INDEX_[pos.x][pos.y];
}

void move_pos(sf::Vector2i old_pos, sf::Vector2i new_pos)
{
    GRID_[old_pos.x][old_pos.y] = false;
    GRID_[new_pos.x][new_pos.y] = true;

    // TODO: fix bug
    INDEX_[old_pos.x][old_pos.y].set_pos_forced(new_pos);

    INDEX_[new_pos.x][new_pos.y] = INDEX_[old_pos.x][old_pos.y];
}
} // namespace BLOCK_INDEX_

#include <iostream>
void debug()
{
    for (int col = 0; col < GRID_Y; col++)
    {
        std::cout << col << "\t";
        for (int row = 0; row < GRID_X; row++)
        {
            if (BLOCK_INDEX_::has_entry({row, col}))
            {
                auto e = BLOCK_INDEX_::get_entry({row, col}).grid_pos;
                std::cout << e.x << "," << e.y;
            }
            std::cout << "\t";
        }
        std::cout << "\n";
    }
}

void Grid_Entry::entry(Block b)
{
    BLOCK_INDEX_::update_entry(b);

    //    debug();
}

void Grid_Entry::delete_entry(sf::Vector2i pos)
{
    BLOCK_INDEX_::delete_entry(pos);
}

void shift_down(sf::Vector2i pos)
{
    BLOCK_INDEX_::move_pos(pos, {pos.x, pos.y + 1});
}

void shift_rows(int mark)
{
    // down to top shifting
    for (int c = mark - 1; c >= 0; c--)
    {
        for (int row = 0; row < GRID_X; row++)
        {
            if (BLOCK_INDEX_::has_entry({row, c}))
            {
                shift_down({row, c});
            }
        }
    }
}

void Grid_Entry::scan_row()
{
    std::vector<int> clean_list;

    for (int col = 0; col < GRID_Y;)
    {
        for (int row = 0; row < GRID_X; row++)
        {
            if (BLOCK_INDEX_::has_entry({row, col}) == false)
                goto next;
        }
        clean_list.push_back(col);
    next:
        col++;
    }

    // clean completed row
    for (auto &col : clean_list)
    {
        for (int row = 0; row < GRID_Y; row++)
            delete_entry({row, col});
    }
    for (auto &col : clean_list)
        shift_rows(col);

    // update score
    if (!clean_list.empty())
        score.add_points(clean_list.size());
}

void Grid_Entry::draw()
{
    for (int col = 0; col < GRID_Y; col++)
    {
        for (int row = 0; row < GRID_X; row++)
        {
            if (BLOCK_INDEX_::has_entry({row, col}))
            {
                BLOCK_INDEX_::get_entry({row, col}).draw();
            }
        }
    }
}

bool Grid_Entry::has_entry(sf::Vector2i pos)
{
    return BLOCK_INDEX_::has_entry(pos);
}
