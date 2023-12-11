#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>

#include "day_04.h"

std::pair<std::vector<std::vector<unsigned>>, std::vector<std::vector<unsigned>>> readFile(const std::string &iFilePath)
{

    // Open the file
    std::ifstream inputFile(iFilePath);

    // Check if the file is open
    if (!inputFile.is_open())
        throw std::invalid_argument("File <" + iFilePath + "> doesn't exists.");

    // Read the file line by line and store each line in a vector of strings
    std::vector<std::vector<unsigned>> winningNumbers;
    std::vector<std::vector<unsigned>> playingNumbers;

    std::string line;
    while (std::getline(inputFile, line))
    {
        auto pos = line.find(":");
        if (pos != line.npos)
        {
            // remove Card Ids
            auto subString = line.substr(pos + 1, line.size());

            // split the line 
            auto pos2 = subString.find("|");
            if (pos2 != subString.npos)
            {
                std::string winningNumbersString = subString.substr(0, pos2);
                std::string playingNumbersString = subString.substr(pos2 + 1, subString.size());

                std::istringstream winningStreamString(winningNumbersString);
                std::istringstream playingStreamString(playingNumbersString);

                // create a list of winning numbers
                std::vector<unsigned> winningNumberByLine;
                unsigned winningNum;
                while (winningStreamString >> winningNum)
                {
                    winningNumberByLine.push_back(winningNum);
                }
                winningNumbers.push_back(winningNumberByLine);

                // create a list of playing numbers
                std::vector<unsigned> playingNumberByLine;
                unsigned playingNum;
                while (playingStreamString >> playingNum)
                {
                    playingNumberByLine.push_back(playingNum);
                }
                playingNumbers.push_back(playingNumberByLine);
            }
        }
    }

    // Close the file
    inputFile.close();

    return std::make_pair(winningNumbers, playingNumbers);
}

unsigned countPoints(const std::vector<std::vector<unsigned>> &iwinning, const std::vector<std::vector<unsigned>> &iPlaying)
{

    auto sum = 0;
    auto pointsTotalPerCard = 0;
    // loop on cards
    for (auto i = 0; i < iPlaying.size(); i++)
    {
        //for each number in each card
        for (auto &num : iPlaying[i])
        {
            //check if it is in the winning list
            auto found = std::find(iwinning[i].begin(), iwinning[i].end(), num);
            if (found != iwinning[i].end())
            {
                // if it is the first, count 1
                if (pointsTotalPerCard == 0)
                {
                    pointsTotalPerCard = 1;
                }
                // if not the first double the points
                else
                {
                    pointsTotalPerCard *= 2;
                }
            }
        }
        // sum the total
        sum += pointsTotalPerCard;
        pointsTotalPerCard = 0;
    }
    return sum;
}

unsigned countPointsWithRewards(const std::vector<std::vector<unsigned>> &iwinning,
 const std::vector<std::vector<unsigned>> &iPlaying)
{
    // rewards are the copies number
    auto rewards = std::vector<unsigned>(iPlaying.size(), 1);
    auto sum =0;
    auto winNumberCounter = 0;

    // loop on the cards
    for (auto i = 0; i < iPlaying.size(); i++)
    {
        //for each number in each card
        for (auto &num : iPlaying[i])
        {
            // check if the num it is in the winning list
            auto found = std::find(iwinning[i].begin(), iwinning[i].end(), num);
            if (found != iwinning[i].end())
            {
                winNumberCounter++; // count the number of winning numbers per card
            }
        }

        // if a card have a winning number
        // reward the "winNumberCounter" next cards (make copies)
        for (auto l = 0; l < winNumberCounter; l++)
        {
            //for each copy we do the same (thats why i added rewards[i] -> number of copies in i_th card)
            rewards[i + l + 1] += rewards[i];
        }
        winNumberCounter = 0;
        sum += rewards[i];
    }

    return sum;
}