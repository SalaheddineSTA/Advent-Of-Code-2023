#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cmath>

#include "day_09.h"


std::vector<std::vector<unsigned>> oases;

void readFile(const std::string &iFilePath)
{
     // Open the file
    std::ifstream inputFile(iFilePath);

    // Check if the file is open
    if (!inputFile.is_open())
        throw std::invalid_argument("File <" + iFilePath + "> doesn't exists.");

    std::string line;
    while(std::getline(inputFile,line))
    {
        std::vector<unsigned> oasis;
        std::stringstream lineNumbers(line);
        int number;
        while(lineNumbers>>number)
        {
            oasis.push_back(number);
        }
        oases.push_back(oasis);
    }
}


unsigned prediction(const std::vector<unsigned>& iOasis )
{
    std::vector<std::vector<unsigned>> predicitons;
    predicitons.push_back(iOasis);
    std::vector<unsigned> tmpPredictions;
    auto allNull = false;
    while(!allNull)
    {
        allNull = true;
        tmpPredictions.clear();
        auto lastPredictions = predicitons[predicitons.size()-1];
        for(auto i= 0; i<lastPredictions.size()-1;i++)
        {
            tmpPredictions.push_back(lastPredictions[i+1]- lastPredictions[i]);
            if(allNull && tmpPredictions[i]!=0)  
            {
                allNull = false;
            }
        }
        predicitons.push_back(tmpPredictions);
    }

    int nextNumber =0;
    for(auto i = predicitons.size()-1; i>0; i--)
    {
        auto linePrediction = predicitons[i];
        nextNumber += linePrediction[linePrediction.size()-1];
    }
    return nextNumber+iOasis[iOasis.size()-1];
}

void puzzlePart1()
{
    auto result =0;
    for(auto &oasis: oases)
    {
        result+= prediction(oasis);
    }
   std::cout << "result: " << result << std::endl;
}

void puzzlePart2()
{
 auto result =0;
    for(auto oasis: oases)
    {
        std::reverse(oasis.begin(),oasis.end());
        result+= prediction(oasis);
    }
   std::cout << "result: " << result << std::endl;
}
void display()
{
   for (const auto& row : oases) {
        for (const auto& element : row) {
            std::cout << element << "\t"; // Adjust formatting as needed
        }
        std::cout << std::endl;
    }
}
