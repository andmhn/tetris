#include "grid_entry.h"

// it will only track all of still blocks
bool GRID_INDEX[GRID_X][GRID_Y] = {{0}};

// stores blocks
Block BLOCK_INDEX_[GRID_X][GRID_Y];

#include <iostream>
void print()
{
    for (size_t col = 0; col < GRID_Y; col++)
    {
        for (size_t row = 0; row < GRID_X; row++)
            std::cout << bool(GRID_INDEX[row][col]) << " ";
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void Grid_Entry::entry(Block b)
{
    BLOCK_INDEX_[b.grid_pos.x][b.grid_pos.y] = b;
    GRID_INDEX[b.grid_pos.x][b.grid_pos.y] = true;

    scan_row();
}

void Grid_Entry::delete_entry(sf::Vector2i pos)
{
    GRID_INDEX[pos.x][pos.y] = false;
}

void shift_down(sf::Vector2i pos)
{
    sf::Vector2i inc = {0, 1};

    GRID_INDEX[pos.x][pos.y] = false;
    GRID_INDEX[pos.x][pos.y + 1] = true;
    BLOCK_INDEX_[pos.x][pos.y].set_pos(pos + inc);
    //    BLOCK_INDEX_[new_pos.x][new_pos.y] = BLOCK_INDEX_[prev_pos.x][prev_pos.y];
}

void shift_rows(std::vector<int> clean_list)
{
    for (auto mark : clean_list)
    {
        // down to top shifting
        for (int c = mark - 1; c > 0; c--)
        {
            for (int row = 0; row < GRID_X; row++)
            {
                if (GRID_INDEX[row][c])
                {
                    shift_down({row, c});
                }
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
            if (GRID_INDEX[row][col] == false)
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
    shift_rows(clean_list);
}

void Grid_Entry::draw()
{
    for (size_t col = 0; col < GRID_Y; col++)
    {
        for (size_t row = 0; row < GRID_X; row++)
        {
            if (GRID_INDEX[row][col] == true)
                BLOCK_INDEX_[row][col].draw();
        }
    }
}
