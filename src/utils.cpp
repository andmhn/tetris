#include "utils.h"
#include <iostream>
#include <random>

void die(char *err)
{
    std::cerr << err;
    exit(EXIT_FAILURE);
}

int random_no(int start, int stop)
{
    std::random_device dev;
    std::mt19937 rng(dev());

    // distribution in range [1, 6]
    std::uniform_int_distribution<std::mt19937::result_type> dist6(start, stop);

    return dist6(rng);
}
