//
// Created by mikolaj on 6/8/25.
//

#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Task.h"

class Solution
{
    unsigned int c_max;

public:
    explicit Solution(unsigned int c_max) : c_max(c_max) {}
    Solution() = default;
    unsigned int get_c_max() const {return c_max;}
};

std::ostream& operator<<(std::ostream& os, const Solution& s);

#endif //SOLUTION_H
