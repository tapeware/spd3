//
// Created by mikolaj on 6/8/25.
//

#include "utils.h"

#include <iostream>

void Array2D::print() {
    for(unsigned int i=0; i<rows; i++) {
        for(unsigned int j=0; j<cols; j++) {
            std::cout<<a[i][j] <<", ";
        }
        std::cout<<"\n";
    }
}

Range get_range(unsigned int beginning, unsigned int end)
{
    std::vector<unsigned int> result;

    for (unsigned int i=beginning; i<=end; i++) result.push_back(i);

    return result;
}

std::ostream& operator<<(std::ostream& os, const Range& r)
{
    std::stringstream formatted_string;
    unsigned int counter=0;

    for (unsigned int i : r)
    {
        if(++counter == 1) formatted_string << "[" << i << ", ";
        else if(counter != r.size()) formatted_string << i << ", ";
        else formatted_string << i << "]";
    }

    os << formatted_string.str();
    return os;
}


long double Timer::get_measurement() const
{
    if(!measured)
        return 0.0;

    return static_cast<long double> (std::chrono::duration_cast<std::chrono::nanoseconds>
    (end - begin).count());
}

std::string Timer::get_measurement_with_unit() const
{
    if (!measured) return "0s";

    long double duration = get_measurement();
    long double number_to_print;
    std::string unit;
    std::stringstream result;

    if(duration <= 1000.0)
    {
        unit = "ns";
        number_to_print = duration;
    }
    else if(duration <= 1000'000.0)
    {
        unit = "us";
        number_to_print = duration/1000.0;
    }
    else if(duration <= 1000'000'000.0)
    {
        unit = "ms";
        number_to_print = duration/1000'000.0;
    }
    else
    {
        unit = "s";
        number_to_print = duration/1000'000'000.0;
    }

    result << std::fixed << std::setprecision(3)<< number_to_print << unit << "\n";
    return result.str();
}

void Timer::print_measurement() const
{
    if (!measured) return;
    std::cout << "time: " << get_measurement_with_unit();
}