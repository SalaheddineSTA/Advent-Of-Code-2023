#include <iostream>
#include <numeric> 
#include <chrono>


#include "day_09.h"

int main(int argc, char *argv[])
{   
    std::cout << "################################" << std::endl;
    std::cout << "| Advent Of Code 2023 | Day 09 |" << std::endl;
    std::cout << "################################" << std::endl;
    
    if(argc<=1)
    {
        std::cout << "Argument needed: Input file ." << std::endl;    
        return 0;
    }

    std::string fileName(argv[1]);
    try
    {

        readFile(fileName);
        display();

        puzzlePart1();
        puzzlePart2();
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }


    return 1;
}