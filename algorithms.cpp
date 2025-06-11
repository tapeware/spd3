//
// Created by mikolaj on 6/8/25.
//

#include "algorithms.h"



Solution NEH(const Problem& p)
{
    Problem sorted = p;
    sorted.operations_length_sort();
    Task current_task;

    std::vector<Task> sorted_tasks = sorted.get_tasks();
    std::vector<Task> neh_sol;
    std::vector<Task> temp_test;
     int best_time =0;
     int best_position =0;

    for ( int i=0; i < sorted_tasks.size(); ++i) {
        current_task = sorted_tasks[i];

        best_time=0;
        best_position=0;

        for ( int offset=0; offset <= neh_sol.size();++offset) {
            temp_test = neh_sol;
            temp_test.insert(temp_test.begin() + offset, current_task);
            Problem t_problem(temp_test, p.get_machine_count());
             int time = t_problem.simulate();

            if (time< best_time|| offset==0)
            {
                best_time = time;
                best_position = offset;
            }
        }

        neh_sol.insert(neh_sol.begin() + best_position, current_task);
    }

    Problem fin_problem(neh_sol, p.get_machine_count());
    return Solution(fin_problem.simulate());
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

int eval_insert_makespan(
    std::vector<Task>& current,
    Task& task,
    int pos,
    Array2D& in,
    Array2D& out,
    int machines
) {
    auto ops = task.get_operations();
    std::vector<int> pre(machines, 0);
    std::vector<int> suf(machines, 0);
    std::vector<int> end(machines, 0);
    int max_val = 0;

    if (pos > 0) {
        for (int m=0; m <machines; m++) {
            pre[m]=in.get_at(m, pos - 1);
        }
    }

    if (pos < current.size()) {
        for (int m =0; m < machines; m++) {
            suf[m] =out.get_at(m, pos);
        }
    }

    for (int m =0; m < machines; m++) {
        if (m ==0) {
            end[m] = pre[m]+ops[m];
        } else {
            int prev = end[m-1];
            if (pre[m] > prev) {
                prev = pre[m];
            }
            end[m] = prev+ops[m];
        }

        int total = end[m]+suf[m];
        if (total>max_val) {
            max_val = total;
        }
    }

    return max_val;
}

int best_insert_pos(
    std::vector<Task>& tasks,
    Task& task,
    int machines
) {
   unsigned int count = tasks.size();
    Array2D in(machines, count);
    Array2D out(machines, count);

    std::vector<int> front(machines, 0);
    for (int i=0; i<count; i++) {
        auto ops = tasks[i].get_operations();
        front[0] += ops[0];
        in.set_at(0, i, front[0]);

        for (int m=1; m<machines; m++) {
            if (front[m-1] > front[m]) {
                front[m] = front[m-1];
            }
            front[m] += ops[m];
            in.set_at(m, i, front[m]);
        }
    }

    std::vector<int> back(machines, 0);
    for (int i=count-1; i>=0; i--) {
        auto ops = tasks[i].get_operations();
        back[machines-1] += ops[machines-1];
        out.set_at(machines-1, i, back[machines-1]);

        for (int m=machines-2; m>=0;m--) {
            if (back[m+1] > back[m]) {
                back[m] = back[m+1];
            }
            back[m]+=ops[m];
            out.set_at(m, i, back[m]);
        }
    }

    int best =0;
    int best_time =-1;

    for (int i=0; i<=count;i++) {
        int t=eval_insert_makespan(tasks, task, i, in, out, machines);
        if (best_time==-1 || t<best_time) {
            best_time =t;
            best = i;
        }
    }

    return best;
}

Solution fNEH(const Problem& p) {
    Problem sorted = p;
    sorted.operations_length_sort();
    std::vector<Task> tasks = sorted.get_tasks();

    std::vector<Task> result;
    result.reserve(tasks.size());

    for (unsigned int i=0; i<tasks.size(); i++) {
        int pos = best_insert_pos(result, tasks[i], p.get_machine_count());
        result.insert(result.begin()+pos, tasks[i]);
    }

    Problem final(result, p.get_machine_count());
    return Solution(final.simulate());
}


