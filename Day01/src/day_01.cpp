#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "day_01.h"

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
    while (file >> line)
        output.push_back(line);

    return output;
}

unsigned sumCalibrationValues(const std::vector<std::string>& iRawData)
{
    // output
    unsigned sum = 0;

    // loop on lines
    for (auto &line : iRawData)
    {
        //save calibrationValue for each line
        std::string calibrationValue = "";

        char firstDigit = NULL;
        char lastDigit = NULL;

        //loop on characters for each line
        for (auto &currentChar : line) 
        {
            if (currentChar >= '0' && currentChar <= '9') // check if the character is a digit
            {
                if (firstDigit == NULL) // if it is first digit keep it in firstDigit
                    firstDigit = currentChar;
                else // if it is not first digit keep it in lastDigit
                    lastDigit = currentChar;
            }
        }

        // transform the firstDigit and lastDigit toform a single two-digit number
        if (firstDigit != NULL)
        {
            calibrationValue += firstDigit;
            if (lastDigit != NULL)
                calibrationValue += lastDigit;
            else // if lastDigit is NULL (there is a signle digit in the line); then double the firstDigit.
                calibrationValue += firstDigit;
        }

        // sum up the calibration values
        sum += std::atoi(calibrationValue.c_str());
    }
    return sum;
}

unsigned sumCalibrationValuesPart2(const std::vector<std::string>& iRawData)
{
    // output
    unsigned sum = 0;

     // loop on lines
    for (auto &rawLine : iRawData)
    {
        //save calibrationValue for each line
        std::string calibrationValue = "";

        //transform the line to handle the digits-spelled-out-with-letters
        auto line = transformString(rawLine);

         char firstDigit = NULL;
        char lastDigit = NULL;

        //loop on characters for each line
        for (auto &currentChar : line) 
        {
            if (currentChar >= '0' && currentChar <= '9') // check if the character is a digit
            {
                if (firstDigit == NULL) // if it is first digit keep it in firstDigit
                    firstDigit = currentChar;
                else // if it is not first digit keep it in lastDigit
                    lastDigit = currentChar;
            }
        }

        // transform the firstDigit and lastDigit toform a single two-digit number
        if (firstDigit != NULL)
        {
            calibrationValue += firstDigit;
            if (lastDigit != NULL)
                calibrationValue += lastDigit;
            else // if lastDigit is NULL (there is a signle digit in the line); then double the firstDigit.
                calibrationValue += firstDigit;
        }

        // sum up the calibration values
        sum += std::atoi(calibrationValue.c_str());
    }
    return sum;
}

std::string transformString(const std::string& iStr)
{
    //make a copy
    std::string transformedStr = iStr;
    // list of the digits-spelled-out-with-letters
    std::vector<std::string> digits{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    //keep track of the digits and their position in the string(iStr)
    std::vector<std::pair<unsigned,unsigned>> digitsPoses;

    //loop on the digits-spelled-out-with-letters
    for (auto i = 0; i < digits.size(); i++)
    {
        //look for the i(th) digits-spelled-out-with-letters in the string
        auto digitPosition = transformedStr.find(digits[i]);

        //keep looking while there is digits-spelled-out-with-letters in the string.
        while (digitPosition != transformedStr.npos)
        {
            //save the digit and its position in the string
            digitsPoses.push_back(std::make_pair(i,digitPosition));
            
            //replace temporarly the digits-spelled-out-with-letters with "#" 
            // example nine => ####; two => ###...
            auto temp = std::string(digits[i].size(), '#');
            transformedStr = transformedStr.replace(digitPosition, digits[i].size(), temp);
            
            //keep looking for the i(th) 
            digitPosition = transformedStr.find(digits[i]);
        }

        //rollback to the original string
        transformedStr = iStr;
    }

    //insert the actual digit before each digits-spelled-out-with-letters
    //5nineseven => 59nine7seven
    //loop on the digitsPoses
    for(auto i=0; i < digitsPoses.size();i++)
    {
        //update the position for the next digits
        for(auto j=0; j < digitsPoses.size();j++)
            // if next digits position is greater than the actual position; then update it(+1 each insertion);
            if(digitsPoses[j].second > digitsPoses[i].second) 
                digitsPoses[j].second++;

        //insert the actual digit
        std::string digitToInsert = std::string(1, digitsPoses[i].first+'0');
        transformedStr.insert(digitsPoses[i].second,digitToInsert);
    }

    return transformedStr;
}
