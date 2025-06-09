#include <iostream>
#include "Problem.h"
#include "Solution.h"
#include "Task.h"
#include "algorithms.h"
#include <cstdlib>
#include "utils.h"

void test_algorithm(Solution (*algorithm) (const Problem& p), const Problem& p, const std::string& name)
{
    Solution s{};
    Timer t;

    t.start();
    s = algorithm(p);
    t.stop();

    std::cout << name << ": " << s.get_c_max()
    << " (" << t.get_measurement_with_unit()
    << ")\n";
}

void test_all_algorithms(const Problem& p)
{
    test_algorithm(overview, p, "Revision");
    test_algorithm(johnson, p, "Johnson");
    test_algorithm(NEH, p, "NEH");
    test_algorithm(fNEH, p, "fNEH");
}

int main()
{

    srand(time(nullptr));
    unsigned int time=0;
    const std::string filename = "test1";
    const std::string test_file_path = "../" + filename;


    Problem p(test_file_path);

    //test_all_algorithms(p);
    //p.rearrange({0,2,1,3});
    //std::cout << fNEH(p);
    p.simulate();

    //fNEH(p);
    //std::cout << "Johnson: " << johnson(p) << "\n";
    //std::cout << "NEH:" << NEH(p) <<"\n";

    //if(johnson(p).get_c_max() == NEH(p).get_c_max())
    //   std::cout << "dzoiala!";


    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
