//
// Created by mikolaj on 6/8/25.
//

#include "Solution.h"

#include "Problem.h"


std::ostream& operator<<(std::ostream& os, const Solution& s)
{
    std::stringstream formatted_string;
    formatted_string << "C_max = " << s.get_c_max();
    os << formatted_string.str();
    return os;
}
