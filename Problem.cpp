//
// Created by mikolaj on 6/8/25.
//

#include "Problem.h"

#include <cmath>


Problem::Problem(const std::string& file_path)
{
    unsigned int task_count=0, machine_count=0, tmp_op=0, id=0;
    std::vector<unsigned int> tmp_ops;
    std::ifstream input(file_path);

    if(!input.is_open()) perror("File opening error");

    input >> task_count >> machine_count;
    this->machine_count = machine_count;


    for (unsigned int task_index=0; task_index<task_count; task_index++)
    {
        for (unsigned int op_index=0; op_index<machine_count; op_index++)
        {
            input >> tmp_op;
            tmp_ops.push_back(tmp_op);
        }

        Task tmp(tmp_ops, id++);
        append_task(tmp);
        tmp_ops.clear();
    }
}

std::ostream& operator<<(std::ostream& os, const Problem& p)
{
    std::stringstream formatted_string;

    unsigned int task_count = p.get_task_count();

    formatted_string << "Task count: " << task_count << "\n";
    formatted_string << "Machine count: " << p.get_machine_count() << "\n";

    Task tmp;
    for (unsigned int i=0; i<task_count; i++)
    {
        tmp = p.get_task_by_index(i);
        formatted_string << tmp << "\n";
    }

    os << formatted_string.str();
    return os;
}


unsigned int Problem::simulate() const
{
    //Array2D a(get_machine_count(), get_task_count());
    std::vector<unsigned int> machine_conveyors(machine_count, 0);

    for(const auto& i : to_do_list)
    {
        for (unsigned int j=0; j<machine_count; j++)
        {
            if(j==0) machine_conveyors[0] += i.get_operations()[0];
            else  machine_conveyors[j] = std::max(machine_conveyors[j],
                machine_conveyors[j-1]) + i.get_operations()[j];
            //a.set_at(j, i, machine_conveyors[j]);
        }
    }

    //a.print();
    return machine_conveyors[machine_count-1];
}

void Problem::rearrange(const Range& new_order)
{
    const std::vector<Task> old_one=get_tasks();
    std::vector<Task> new_one;
    for (unsigned int index : new_order) new_one.push_back(old_one[index]);
    to_do_list = new_one;
}

void Problem::remove_task(const Task& to_remove)
{
    to_do_list.erase(
        std::remove_if(
            to_do_list.begin(),
            to_do_list.end(),
            [&to_remove](const Task& t){return t==to_remove;} ),
        to_do_list.end());
}

Array2D Problem::get_table() const
{
    Array2D result(machine_count, get_task_count());
    for(unsigned int r=0; r<machine_count; r++)
        for (unsigned int c=0; c<get_task_count(); c++)
            result.set_at(r,c, to_do_list[c].get_operation(r));

    return result;
}
Array2D Problem::get_paths_in() const {
    int m = get_machine_count();
     int n = get_task_count();

    Array2D result(m, n);
    std::vector<int> machine_times(m, 0);

    for ( int i=0; i<n;++i) {
         const auto& ops = to_do_list[i].get_operations();

        machine_times[0] += ops[0];
        result.set_at(0, i, machine_times[0]);

        for ( int j=1; j<m;++j) {
            machine_times[j] = std::max(machine_times[j], machine_times[j - 1]) + ops[j];
            result.set_at(j, i, machine_times[j]);
        }
    }

    return result;
}


Array2D Problem::get_paths_out() const {
    int m = machine_count;
     int n = get_task_count();
    Array2D result(m, n);

    std::vector<int> suffix_sum(m, 0);
    const auto& last_ops = to_do_list.back().get_operations();

    for (int j= m-2; j>=0;--j) {
        suffix_sum[j] = last_ops[j+1] + suffix_sum[j+1];
    }

    std::vector<int> times(n, 0);

    for (int j=m-1; j>=0;--j) {
         times[n-1] = to_do_list[n-1].get_operation(j);
        if (j<m-1) times[n-1] += suffix_sum[j];
        result.set_at(j, n-1, times[n-1]);

        for (int i = n-2; i >= 0; --i) {
            times[i] = to_do_list[i].get_operation(j) + times[i+1];
              result.set_at(j, i, times[i]);
        }
    }

    return result;
}