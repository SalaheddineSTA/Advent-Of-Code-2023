#include <iostream>
#include <numeric>  

#include "day_02.h"

int main(int argc, char *argv[])
{   
    std::cout << "################################" << std::endl;
    std::cout << "| Advent Of Code 2023 | Day 02 |" << std::endl;
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

        //Part 1
        auto possibleGames = determinePossibleGames(data);
        std::cout <<"sum: "<< std::accumulate(possibleGames.begin(),possibleGames.end(),0) << std::endl;

        //Part 2
        auto possibleGames2 = determinePossibleGamesPart2(data);
        std::cout <<"sum2: "<< std::accumulate(possibleGames2.begin(),possibleGames2.end(),0) << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }


    return 1;
}