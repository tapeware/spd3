//
// Created by mikolaj on 6/8/25.
//

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

typedef std::vector<unsigned int> Range;
Range get_range(unsigned int beginning, unsigned int end);
std::ostream& operator<<(std::ostream& os, const Range& r);

typedef std::chrono::steady_clock::time_point time_measurement;


class Timer
{
    time_measurement begin;
    time_measurement end;
    bool measured;

public:
    Timer() {measured=false;}
    long double get_measurement() const;
    void start() {begin=std::chrono::steady_clock::now();}
    void stop() {end=std::chrono::steady_clock::now(); measured=true;}
    void print_measurement() const;
    std::string get_measurement_with_unit() const;
};

class Array2D
{
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<unsigned int>> a;
public:
    Array2D(unsigned int rows, unsigned int cols) : rows(rows), cols(cols)
    {
        std::vector<unsigned int> col;
        unsigned int blank=0;
        for (unsigned int c=0; c<cols; c++) col.push_back(blank);
        for (unsigned int r=0; r<rows; r++) a.push_back(col);
    }
    unsigned int get_at(unsigned int row, unsigned int col) const {return a.at(row).at(col);}
    void set_at(unsigned int row, unsigned int col, unsigned int value) {a[row][col]=value;}
    void print();
};

#endif //UTILS_H
