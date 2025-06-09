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
    unsigned int get_operation(unsigned int index) const {return operations[index];}
};

std::ostream& operator<<(std::ostream& os, const Task& t);
bool operator==(const Task& t1, const Task& t2);

inline bool johnson_task_comp1(const Task& t1, const Task& t2)
{return t1.get_operation(0)<t2.get_operation(0);}

inline bool johnson_task_comp2(const Task& t1, const Task& t2)
{return t1.get_operation(0)>t2.get_operation(0);}

// inline std::vector<Task> concatenate_task_vectors
// (const std::vector<Task>& v1, const std::vector<Task>& v2)
// {
//     std::vector<Task> result(v1.size()+v2.size());
//     std::cout<<"result will have size of "<< result.size() << "\n";
//
//     for (auto& t : v1) {
//         result.push_back(t);
//         std::cout << "ok1\n";
//     }
//     for (auto& t : v2) {
//         result.push_back(t);
//         std::cout << "ok2\n";
//     }
//
//     std::cout<<"size=" << result.size() << "\n";
//     return result;
// }

#endif //TASK_H
