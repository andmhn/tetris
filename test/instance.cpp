#include "doctest.h"

int instance();

TEST_CASE("testing the instance function")
{
    CHECK(instance() == 0);
}
