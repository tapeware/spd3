//
// Created by mikolaj on 6/8/25.
//

#ifndef TASK_H
#define TASK_H

#include <vector>
#include <iostream>
#include <sstream>

class Task {

    //unsigned int machine_count;
    std::vector<unsigned int> operations;
    unsigned id;


public:
    Task() {operations = {};}
    Task(const std::vector<unsigned int>& operations, unsigned int id)
    : operations(operations), id(id){}
    std::vector<unsigned int> get_operations() const {return operations;}
    unsigned int operate()
    {
        if (operations.empty()) return 0;

        unsigned int to_pop = operations[operations.back()];
        operations.pop_back();
        return to_pop;
    }
    unsigned int get_operations_time_sum() const;
    unsigned int get_id() const {return id;}
};

std::ostream& operator<<(std::ostream& os, const Task& t);
bool operator==(const Task& t1, const Task& t2);

#endif //TASK_H
