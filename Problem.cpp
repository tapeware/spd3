//
// Created by mikolaj on 6/8/25.
//

#include "Problem.h"


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
    std::vector<unsigned int> machine_conveyors(machine_count, 0);

    for(unsigned int i=0; i <to_do_list.size(); i++ )
    {
        for (unsigned int j=0; j<machine_count; j++)
        {
            if(j==0) machine_conveyors[0] += to_do_list[i].get_operations()[0];
            else  machine_conveyors[j] = std::max(machine_conveyors[j],
                machine_conveyors[j-1]) + to_do_list[i].get_operations()[j];
        }
    }
    return machine_conveyors[machine_count-1];
}

void Problem::rearrange(const Range& new_order)
{
    const std::vector<Task> old_one=get_tasks();
    std::vector<Task> new_one;
    for (unsigned int index : new_order) new_one.push_back(old_one[index]);
    to_do_list = new_one;
}

// void Problem::match_to_machines(const based_number& matching)
// {
//     //if (matching.size() != get_task_count()) return;
//
//     for (unsigned int index=0; index<get_task_count(); index++)
//     {
//         to_do_list[index].match_to_machine(matching[index]);
//
//         //std::cout << "matched task nr" << to_do_list[index].get_id()
//         //<< " to machine nr" << to_do_list[index].get_machine_id() << "!\n";
//     }
// }


