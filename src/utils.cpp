#include "utils.h"
#include <algorithm>
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

RandomStream::RandomStream(int start, int stop)
    : start(start), stop(stop)
{
    last_rand = start - 1;
}

void RandomStream::init()
{
    // fill the empty bag
    for (int i = start; i <= stop; ++i)
    {
        bag.push_back(i);
    }

    std::random_device rd;
    auto rng = std::default_random_engine{rd()};
    std::shuffle(std::begin(bag), std::end(bag), rng);
}

int RandomStream::rand()
{
    if (bag.size() == 0)
    {
        init();
        while (bag.back() == last_rand)
        {
            bag.clear();
            init();
        }
    }

    last_rand = bag.back();
    bag.pop_back();
    return last_rand;
}
