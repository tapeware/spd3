#include <iostream>
#include "Problem.h"
#include "Solution.h"
#include "Task.h"
#include "algorithms.h"
#include <cstdlib>
#include "utils.h"


int main()
{

    srand(time(nullptr));
    unsigned int time=0;
    const std::string filename = "test2";
    const std::string test_file_path = "../" + filename;


    Problem p(test_file_path);


    if(johnson(p).get_c_max() == overview(p).get_c_max())
        std::cout << "dzoiala!";


    //std::cout << "Hello, World!" << std::endl;
    return 0;
}
