#include <iostream>
#include <numeric>  

#include "day_03.h"

int main(int argc, char *argv[])
{   
    std::cout << "################################" << std::endl;
    std::cout << "| Advent Of Code 2023 | Day 03 |" << std::endl;
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

        auto expandedData = expandMatrix(data);
        //displayMatrix(expandedData);

        auto result = engineParts(expandedData);
        std::cout << "sum: "<< result << std::endl;

        auto result2 = engineGear(expandedData);
        std::cout << "sum2: "<< result2 << std::endl;
       
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }


    return 1;
}