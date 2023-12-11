#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cmath>

#include "day_06.h"


std::vector<std::pair<unsigned,unsigned>> races;

std::string readFile(const std::string &iFilePath)
{
     // Open the file
    std::ifstream inputFile(iFilePath);

    // Check if the file is open
    if (!inputFile.is_open())
        throw std::invalid_argument("File <" + iFilePath + "> doesn't exists.");

    // Get conent from file
    std::string content((std::istreambuf_iterator<char>(inputFile) ),
                       (std::istreambuf_iterator<char>()));

    return content;
}

void getContent(const std::string &iContent)
{
    // get line jump
    auto firstJumpLine = iContent.find_first_of("\n");

    //get each line
    std::string timeLine = iContent.substr(0,firstJumpLine);
    std::string distanceLine = iContent.substr(firstJumpLine+1,iContent.size());
    
    //remove unwanted text
    timeLine.erase(0, timeLine.find_first_of("0123456789"));
    distanceLine.erase(0, distanceLine.find_first_of("0123456789"));
    
    // get each number from the lines into a vector
    std::stringstream timeStream(timeLine);
    std::stringstream distanceStream(distanceLine);
    
    std::vector<unsigned> time;
    std::vector<unsigned> distance;

    unsigned number;
    while(timeStream >> number) time.push_back(number);
    while(distanceStream >> number) distance.push_back(number);

    // merge teh vectors
    for(auto i=0;i<time.size();i++)
    {
        races.push_back(std::make_pair(time[i],distance[i]));
    }

}

template <typename T>
T possibleWays(T iTime, T iDistance)
{
    T possibleWays = 0;
    //May be it would be better to find a math function to find the minHoldTime
    auto minHoldTime =static_cast<T>(1);
    for(minHoldTime=static_cast<T>(1);minHoldTime<iTime;minHoldTime++)
        if((minHoldTime* (iTime-minHoldTime)) > iDistance) possibleWays++;

    return possibleWays;
}

void puzzlePart1()
{
    auto result = 1;
    for(auto& race: races)
    {
        auto raceTime = race.first; 
        auto currentRecord = race.second;

        result *= possibleWays(raceTime, currentRecord);
    }

    std::cout << "result: " << result <<std::endl;
}

void puzzlePart2()
{
    std::string time;
    std::string distance;
    for(auto& race: races)
    {
        auto raceTime = race.first; 
        auto currentRecord = race.second;

        time+= std::to_string(raceTime);
        distance+= std::to_string(currentRecord);
    }

    uint64_t timeInteger;
    std::stringstream ss(time);
    ss >> timeInteger;

    uint64_t distanceInteger;
    std::stringstream ss1(distance);
    ss1 >> distanceInteger;

    std::cout << "result 2: " << possibleWays(timeInteger, distanceInteger) << std::endl;
}
void display()
{
   for(auto i=0;i<races.size();i++)
    {
        std::cout << "race "<< i+1 << ": " << races[i].first <<  "," << races[i].second << std::endl;
    }
}
