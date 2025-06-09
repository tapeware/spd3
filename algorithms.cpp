//
// Created by mikolaj on 6/8/25.
//

#include "algorithms.h"



Solution NEH(const Problem& p)
{
    unsigned int current_time=0, min_time=0;
    Problem p_copy = p;
    p_copy.operations_length_sort();
    auto& p_copy_tasks = p_copy.access_tasks();
    Task shortest_task = p_copy_tasks[p_copy_tasks.size()-1];


    current_time = p_copy.simulate();
    //std::cout << p_copy << "^^ This evaluates to t=" << current_time<<"...\n\n";
    p_copy_tasks.pop_back();

    for(unsigned int offset=0; offset<p_copy.get_task_count(); offset++)
    {
        if(current_time < min_time || min_time==0) {
            min_time=current_time;
            //std::cout<<"min_time=" << min_time <<", time=" << current_time << "\n";
            //std::cout<<"min time is now " << min_time <<"\n";

        }
        //std::cout<<"OFFSET IS NOW " << offset <<"!!!\n";
        p_copy_tasks.insert(p_copy_tasks.begin()+offset, shortest_task);
        current_time = p_copy.simulate();
        //std::cout << p_copy << "^^ This evaluates to t=" << current_time<<"...\n\n";
        p_copy.remove_task(shortest_task);
    }



    //std:: cout << min_time;

    return Solution(min_time);
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

    std::vector<Task> set1, set2, optimal_order,
    tasks=p.get_tasks();

    for(unsigned int i=0;i<p.get_task_count(); i++)
    {
        if (tasks[i].get_operation(0) < tasks[i].get_operation(1))
            set1.push_back(tasks[i]);
        else set2.push_back(tasks[i]);
    }

    std::sort(set1.begin(), set1.end(), johnson_task_comp1);
    std::sort(set2.begin(), set2.end(), johnson_task_comp2);
    optimal_order.insert(optimal_order.begin(), set1.begin(), set1.end());
    optimal_order.insert(optimal_order.end(), set2.begin(), set2.end());

    return Solution(Problem(optimal_order, p.get_machine_count()).simulate());
}

Solution fNEH(const Problem& p)
{
    // unsigned int machine_count = p.get_machine_count(),
    // task_count =  p.get_tasks().size();
    // int sum=0;
    //
    // std::vector<Weight> weights(task_count);
    // std::vector<Task> optimally_arranged_tasks, tmp;
    // Problem tmp_p;
    //
    // for(unsigned int task_index=0; task_index<task_count; task_index++)
    // {
    //     sum = p.get_task_by_index(task_index).get_operations_time_sum();
    //     weights[task_index] = {-sum, task_index};
    // }
    //
    // std::sort(weights.begin(), weights.end(), weight_comp);
    //
    // for(unsigned int task_index=0; task_index<task_count; task_index++)
    // {
    //     unsigned int current_time=0, min_time=0, id = weights[task_index].id;
    //
    //     for(int offset=0; offset<= optimally_arranged_tasks.size(); offset++)
    //     {
    //         tmp=optimally_arranged_tasks;
    //         tmp.insert(tmp.begin()+offset, p.get_tasks()[id]);
    //         tmp_p = Problem(tmp, machine_count);
    //         current_time = tmp_p.simulate();
    //
    //         if(current_time < min_time || min_time==0)
    //         {
    //             min_time = current_time;
    //             optimally_arranged_tasks = tmp;
    //         }
    //     }
    // }
    // return Solution(Problem(optimally_arranged_tasks, machine_count).simulate());

    // Array2D lookup_table = p.get_table();
    // Array2D in = p.get_paths_in();
    // Array2D out = p.get_paths_out();
    //
    // Task to_insert;
    //
    // for (unsigned int task_index=0; task_index<p.get_task_count(); task_index++)
    // {
    //
    //
    // }

    //i.print();


    return Solution(0);
}