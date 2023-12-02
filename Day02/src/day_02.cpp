#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <tuple>

#include "day_02.h"

//challenge global information
const std::string _RED = "red";
const std::string _GREEN = "green";
const  std::string _BLUE = "blue";
const auto _REDLIMIT = 12;
const auto _GREENLIMIT = 13;
const auto _BLUELIMIT = 14;

std::vector<std::string> readFile(const std::string& iFilePath)
{
    // output
    std::vector<std::string> output;

    // read file
    std::ifstream file(iFilePath);

    // check if file exists
    if (!file.good())
        throw std::invalid_argument("File <" + iFilePath + "> doesn't exists.");

    // put the file data line by line into the vector
    std::string line;
    while (std::getline(file, line))
    {
        auto pos = line.find(":");
        if(pos!=line.npos)
        {
            std::string subString = line.substr(pos+1,line.size());
            output.push_back(subString);
        }
    }
        
    return output;
}

bool gameIsPossible(const std::string& iStrings)
{
    // init 
    bool isPossible = true;
    std::string digits = ""; 

    // split the game string to sets
    auto splittedString = splitString(iStrings,";");
    
    // loop on sets
    for(auto& ss :splittedString)
    {
        // init counters for each set.
        auto redCounter = 0;
        auto greenCounter = 0;
        auto blueCounter = 0;

        // count reds
        // look for word "red", and split the line(set).
        auto reds = splitString(ss,_RED);
        
        // keep the first element it contains the number of red cubes.
        auto temp = reds[0];

        // if the first item have one digit we do -2 position.
        temp.size() > 2 ? temp= temp.substr(temp.size()-3,temp.size()) : temp= temp.substr(temp.size()-2,temp.size());

        // clear digit variable
        digits.clear();
        // convert the digits and count them.
        for(auto &c: temp)
        {
            if(isADigit(c))
                digits+= std::string(1,c);
        }
        if(!digits.empty())
            redCounter += std::atoi(digits.c_str());

        // count greens 
        // look for word "green", and split the line(set).
        auto greens = splitString(ss,_GREEN);

        // keep the first element it contains the number of red cubes.
        temp = greens[0];

        // if the first item have one digit we do -2 position.
        temp.size()>2 ? temp= temp.substr(temp.size()-3,temp.size()) : temp= temp.substr(temp.size()-2,temp.size());
        
        // clear digit variable
        digits.clear();
        // convert the digits and count them.
        for(auto &c: temp)
        {
            if(isADigit(c))
                digits+= std::string(1,c);
        }
        if(!digits.empty())
            greenCounter += std::atoi(digits.c_str());

        // count blues
        // look for word "blue", and split the line(set).
        auto blues = splitString(ss,_BLUE);

        // keep the first element it contains the number of red cubes.
        temp = blues[0];

        // if the first item have one digit we do -2 position.
        temp.size()>2 ? temp= temp.substr(temp.size()-3,temp.size()) : temp= temp.substr(temp.size()-2,temp.size());
        
        // clear digit variable
        digits.clear();
        // convert the digits and count them.
        for(auto &c: temp)
        {
            if(isADigit(c))
                digits+= std::string(1,c);
        }
        if(!digits.empty())
            blueCounter += std::atoi(digits.c_str());
        
        // check if the cubes respect the limits; if not return false.
        if( redCounter > _REDLIMIT || greenCounter > _GREENLIMIT || blueCounter > _BLUELIMIT)
        {
            isPossible = false;
            break;
        }
    }

    return isPossible;
}

std::vector<unsigned> determinePossibleGames(const std::vector<std::string> &iStrings)
{
     std::vector<unsigned> gameIDs;

     // loop on games
    for(auto i =0; i < iStrings.size(); i++)
        //check if game is possible; insert game ID
        if(gameIsPossible(iStrings[i]))
            gameIDs.push_back(i+1);

    return gameIDs;
}

std::vector<std::string> splitString(const std::string& iString, const std::string& iDelimiter)
{
    std::vector<std::string> splittedString;
    std::string strCopy = iString;

    //find first delimiter position
    auto pos = strCopy.find(iDelimiter);
    while(pos!=strCopy.npos)
    {
        //split the string using the first delimiter position
        std::string subString = strCopy.substr(0,pos);
        splittedString.push_back(subString);
        
        //copy the rest of the string and keep looking for the delimiter till there is no more.
        strCopy = strCopy.substr(pos+1,strCopy.size());
        pos = strCopy.find(iDelimiter);
    }
    // if there is no more delimiters, add the last part (in case the line do not end with delimiter).
    if(!strCopy.empty())
        splittedString.push_back(strCopy);

    return splittedString;
}

bool isADigit(const char &iChar)
{
    return (iChar >= '0' && iChar <= '9');
}

unsigned minimumCubes(const std::string& iStrings)
{
    // init max cubes per game
    auto maxRed = 0;
    auto maxGreen = 0;
    auto maxBlue = 0;
    std::string digits = "";

    // split the game line into multiple sets
    auto splittedString = splitString(iStrings,";");

    // loop on sets
    for(auto& ss :splittedString)
    {
        // init counters for each set.
        auto redCounter = 0;
        auto greenCounter = 0;
        auto blueCounter = 0;

        // count reds
        // look for word "red", and split the line(set).
        auto reds = splitString(ss,_RED);
        
        // keep the first element it contains the number of red cubes.
        auto temp = reds[0];

        // if the first item have one digit we do -2 position.
        temp.size() > 2 ? temp= temp.substr(temp.size()-3,temp.size()) : temp= temp.substr(temp.size()-2,temp.size());

        // clear digit variable
        digits.clear();
        // convert the digits and count them.
        for(auto &c: temp)
        {
            if(isADigit(c))
                digits+= std::string(1,c);
        }
        if(!digits.empty())
            redCounter += std::atoi(digits.c_str());

        // count greens 
        // look for word "green", and split the line(set).
        auto greens = splitString(ss,_GREEN);

        // keep the first element it contains the number of red cubes.
        temp = greens[0];

        // if the first item have one digit we do -2 position.
        temp.size()>2 ? temp= temp.substr(temp.size()-3,temp.size()) : temp= temp.substr(temp.size()-2,temp.size());
        
        // clear digit variable
        digits.clear();
        // convert the digits and count them.
        for(auto &c: temp)
        {
            if(isADigit(c))
                digits+= std::string(1,c);
        }
        if(!digits.empty())
            greenCounter += std::atoi(digits.c_str());

        // count blues
        // look for word "blue", and split the line(set).
        auto blues = splitString(ss,_BLUE);

        // keep the first element it contains the number of red cubes.
        temp = blues[0];

        // if the first item have one digit we do -2 position.
        temp.size()>2 ? temp= temp.substr(temp.size()-3,temp.size()) : temp= temp.substr(temp.size()-2,temp.size());
        
        // clear digit variable
        digits.clear();
        // convert the digits and count them.
        for(auto &c: temp)
        {
            if(isADigit(c))
                digits+= std::string(1,c);
        }
        if(!digits.empty())
            blueCounter += std::atoi(digits.c_str());
        
        //keep the max number per color
        if( maxRed < redCounter) maxRed = redCounter;
        if( maxGreen< greenCounter) maxGreen = greenCounter; 
        if( maxBlue < blueCounter)  maxBlue = blueCounter;
    }

    if( maxRed == 0 ) maxRed = 1;
    if( maxGreen== 0 ) maxGreen = 1;
    if( maxBlue == 0 ) maxBlue = 1;

    return maxRed * maxGreen * maxBlue;
}

std::vector<unsigned> determinePossibleGamesPart2(const std::vector<std::string> &iStrings)
{
     std::vector<unsigned> minPossibleCubes;

     // loop on games
    for(auto i =0; i < iStrings.size(); i++)
        minPossibleCubes.push_back(minimumCubes(iStrings[i]));
    
    return minPossibleCubes;
}