#pragma once

#include "components.h"

namespace Grid_Entry
{
    // clear out compeleted row and increment score
    void scan_row();

    // delete block from given entry positon
    void delete_entry(sf::Vector2i pos);

    // store it to blocks
    void entry(Block b);

    // draw indexed blocks
    void draw();

    bool has_entry(sf::Vector2i pos);

    void reset();
};
