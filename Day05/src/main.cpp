#include <iostream>
#include <numeric> 
#include <chrono>


#include "day_05.h"

int main(int argc, char *argv[])
{   
    std::cout << "################################" << std::endl;
    std::cout << "| Advent Of Code 2023 | Day 05 |" << std::endl;
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
        for (size_t ii = 0; ii < 5; ii++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < 100000; i++)
            {
                countPointsWithRewards(winningNumbers,playingNumbers);
            }
                auto end = std::chrono::high_resolution_clock::now();
                // Calculate the duration in microseconds
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start );

            // Output the duration
            std::cout << "Time spent: " << duration.count() << " seconds" << std::endl;
        }
        
       
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