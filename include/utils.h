#pragma once

#include<string>
#include<vector>

void die(char* err);
int random_no(int start, int stop);

std::string left_rotate(std::string s, int width);
std::string right_rotate(std::string s, int width);

// Tetris randomizer
class RandomStream
{
    int start , stop;
    std::vector<int> bag;

    int last_rand;

    void init();

public:
    RandomStream(int start, int stop);
    int rand();
};
