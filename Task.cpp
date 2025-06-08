//
// Created by mikolaj on 6/8/25.
//

#include "Task.h"




std::ostream& operator<<(std::ostream& os, const Task& t)
{
    std::stringstream stream;
    stream << t.get_id()+1 << ") ";
    for (auto& op : t.get_operations()) stream << op << ", ";
    os << stream.str();
    return os;
}

bool operator==(const Task& t1, const Task& t2)
{
    return t1.get_id() == t2.get_id() &&
           t1.get_operations() == t2.get_operations();
}

unsigned int Task::get_operations_time_sum() const
{
    unsigned int sum=0;
    for (auto& op : operations) sum += op;
    return sum;
}