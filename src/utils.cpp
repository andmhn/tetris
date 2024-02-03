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

// Left Rotation of a String
std::string left_rotate(std::string s, int n)
{
    std::string ret_s;
    for (int col = n - 1; col >= 0; col--)
        for (int row = 0; row < n; row++)
            // store current [row][col] of 1D string
            ret_s += s[(row * n) + col];

    return ret_s;
}

// Right Rotation of a String
std::string right_rotate(std::string s, int n)
{
    std::string ret_s;
    for (int col = 0; col < n; col++)
        for (int row = n - 1; row >= 0; row--)
            ret_s += s[(row * n) + col];

    return ret_s;
}
