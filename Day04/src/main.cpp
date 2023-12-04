#include <iostream>
#include <numeric>  

#include "day_04.h"

int main(int argc, char *argv[])
{   
    std::cout << "################################" << std::endl;
    std::cout << "| Advent Of Code 2023 | Day 04 |" << std::endl;
    std::cout << "################################" << std::endl;
    
    if(argc<=1)
    {
        std::cout << "Argument needed: Input file ." << std::endl;    
        return 0;
    }

    std::string fileName(argv[1]);
    try
    {
        //read input data
        auto data = readFile(fileName);

        auto winningNumbers = data.first;
        auto playingNumbers = data.second; 

        // part 1
        auto result = countPoints(winningNumbers,playingNumbers);
        std::cout << "result: "<< result <<std::endl;

        // part 2
        auto result2 = countPointsWithRewards(winningNumbers,playingNumbers);
        std::cout << "result2: "<< result2 <<std::endl;
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }


    return 1;
}