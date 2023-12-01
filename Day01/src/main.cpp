#include <iostream>

#include "day_01.h"

int main(int argc, char *argv[])
{   
    std::cout << "hello world" << std::endl;
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

        // resolve part 1
        auto result = sumCalibrationValues(data);
        std::cout << "result: " <<result << std::endl;

        // resolve part 2
        auto result2 = sumCalibrationValuesPart2(data);
        std::cout << "result2: " <<result2 << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }


    return 1;
}