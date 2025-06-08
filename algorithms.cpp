//
// Created by mikolaj on 6/8/25.
//

#include "algorithms.h"

Solution NEH(const Problem& p)
{
    Problem p_copy = p;
    p_copy.operations_length_sort();
    auto& p_copy_tasks = p_copy.access_tasks();
    Task shortest_task = p_copy_tasks[p_copy_tasks.size()-1];

    // p_copy_tasks.erase(
    //     std::remove_if(
    //         p_copy_tasks.begin(),
    //         p_copy_tasks.end(),
    //         [&shortest_task](const Task& t){return t==shortest_task;} ),
    //     p_copy_tasks.end());


    std:: cout << p_copy;

    return Solution(1);
}


Solution overview(const Problem& p)
{

    std::vector<Task> tasks = p.get_tasks();
    Range task_order = get_range(0, p.get_task_count()-1), optimal_order;
    Problem tmp=p, optimally_aranged_problem;
    unsigned int time=0, minimal_time=0;

    do
    {
        tmp=p;
        tmp.rearrange(task_order);
        time = tmp.simulate();
        if(time < minimal_time || minimal_time==0)
        {
            minimal_time = time;
            optimally_aranged_problem = tmp;
            optimal_order = task_order;
        }

    }
    while (std::next_permutation(task_order.begin(), task_order.end()));

    Solution result(minimal_time);
    std::cout << optimal_order << "\n";
    return result;
}


Solution johnson(const Problem &p)
{
    if (p.get_machine_count()!=2)
        throw std::runtime_error("This algorithm is implemented only for m=2!");

    std::vector<Task> front_vector;
    std::vector<Task> back_vector;
    std::vector<Task> tasks = p.get_tasks();


    for(unsigned int task_index=0; task_index<tasks.size(); task_index++)
    {
        if(tasks[task_index].get_operations()[0] > tasks[task_index].get_operations()[1])
            back_vector.insert(back_vector.begin(), tasks[task_index]);
        else
            front_vector.insert(front_vector.end(), tasks[task_index]);

    }
    front_vector.insert(front_vector.end(), back_vector.begin(), back_vector.end());

    Problem sorted(front_vector, 2);
    return Solution(sorted.simulate());
}
