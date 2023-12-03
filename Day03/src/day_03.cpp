#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>

#include "day_03.h"

std::vector<std::vector<char>> readFile(const std::string &iFilePath)
{
    // Open the file
    std::ifstream inputFile(iFilePath);

    // Check if the file is open
    if (!inputFile.is_open())
        throw std::invalid_argument("File <" + iFilePath + "> doesn't exists.");

    // Read the file line by line and store each line in a vector of strings
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    // Close the file
    inputFile.close();

    // Determine the dimensions of the matrix
    size_t numRows = lines.size();
    size_t maxCols = 0;
    for (const auto &str : lines)
    {
        maxCols = std::max(maxCols, str.size());
    }

    // Create a 2D matrix of chars
    std::vector<std::vector<char>> charMatrix(numRows, std::vector<char>(maxCols, ' '));

    // Fill the matrix with characters from the file
    for (size_t i = 0; i < numRows; ++i)
    {
        for (size_t j = 0; j < lines[i].size(); ++j)
        {
            charMatrix[i][j] = lines[i][j];
            // std::cout << "charMatrix[i][j]: "<< charMatrix[i][j] << std::endl;
        }
    }

    return charMatrix;
}

std::vector<std::vector<char>> expandMatrix(const std::vector<std::vector<char>> &iOriginalMatrix)
{
    std::vector<std::vector<char>> matrix(iOriginalMatrix.size() + 2, std::vector<char>(iOriginalMatrix[0].size() + 2, '.'));

    for (auto i = 0; i < iOriginalMatrix.size(); ++i)
    {
        for (auto j = 0; j < iOriginalMatrix[i].size(); ++j)
        {
            matrix[i + 1][j + 1] = iOriginalMatrix[i][j];
        }
    }

    return matrix;
}

bool hasAdjacentSymbol(const std::vector<std::vector<char>> &iMatrix, const unsigned iX, const unsigned iY)
{
    // check if the position are not out the matrix
    if (iX < 1 || iY < 1 || iX > iMatrix.size() - 1 || iY > iMatrix[0].size() - 1)
    {
        throw std::invalid_argument("False position provided.");
    }
    else
    { // check if a symbol exists in the 8 neighbors.
        for (auto i = -1; i <= 1; ++i)
        {
            for (auto j = -1; j <= 1; ++j)
            {
                if (isASymbol(iMatrix[iX + i][iY + j]))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::pair<int, int> hasAdjacentSymbolWithChanging(std::vector<std::vector<char>> &ioMatrix, const unsigned iX, const unsigned iY)
{
    // check if the position are not out the matrix
    if (iX < 1 || iY < 1 || iX > ioMatrix.size() - 1 || iY > ioMatrix[0].size() - 1)
    {
        throw std::invalid_argument("False position provided.");
    }
    else
    { // check if a symbol exists in the 8 neighbors.
        for (auto i = -1; i <= 1; ++i)
        {
            for (auto j = -1; j <= 1; ++j)
            {
                if (isASymbol(ioMatrix[iX + i][iY + j]))
                {
                    switch (ioMatrix[iX + i][iY + j])
                    {
                    case '*':
                        ioMatrix[iX + i][iY + j] = 'O';
                        break;
                    case 'O':
                        ioMatrix[iX + i][iY + j] = 'T';
                        break;
                    case 'T':
                        ioMatrix[iX + i][iY + j] = '#';
                        break;
                    }
                    return std::make_pair(iX + i, iY + j);
                }
            }
        }
    }

    return std::make_pair(-1, -1);
}

unsigned engineParts(const std::vector<std::vector<char>> &iMatrix)
{
    // init
    auto sum = 0;
    std::string digits = "";
    auto digitHasAdjacent = false;

    // loop on the matrix (start from 1 to size -1 to avoid the points '.' we added)
    for (auto i = 1; i < iMatrix.size() - 1; ++i)
    {
        for (auto j = 1; j < iMatrix[i].size() - 1; ++j)
        {
            // if is digit stack it
            if (isADigit(iMatrix[i][j]))
            {
                digits += std::string(1, iMatrix[i][j]);

                // if previous digit from same number has adjacent symbol do not check the others
                if (!digitHasAdjacent)
                {
                    digitHasAdjacent = hasAdjacentSymbol(iMatrix, i, j);
                }
            }
            else // we encouter a non digit
            {
                // we have stack a number
                if (!digits.empty())
                {
                    // if this number has an adjacent symbol sum it.
                    if (digitHasAdjacent)
                    {
                        auto digitNumber = std::atoi(digits.c_str());
                        sum += digitNumber;
                        digitHasAdjacent = false;
                    }
                    digits.clear();
                }
            }
        }
    }

    return sum;
}

unsigned engineGear(const std::vector<std::vector<char>> &iMatrix)
{

    // init
    auto sum = 0;
    std::vector<std::vector<char>> matrix = iMatrix;
    std::vector<std::tuple<int, int, int>> valueSymbolPosition;
    std::string digits = "";
    auto starPosition = std::make_pair(-1, -1);

    // loop on the matrix (start from 1 to size -1 to avoid the points '.' we added)
    for (auto i = 1; i < matrix.size() - 1; ++i)
    {
        for (auto j = 1; j < matrix[i].size() - 1; ++j)
        {
            // if is digit stack it
            if (isADigit(matrix[i][j]))
            {
                digits += std::string(1, matrix[i][j]);

                // if previous digit from same number has adjacent symbol do not check the others
                if (starPosition.first == -1 && starPosition.second == -1)
                {
                    //get symbol positions and change it in the matrix
                    starPosition = hasAdjacentSymbolWithChanging(matrix, i, j);
                }
            }
            else // we encouter a non digit
            {
                // we have stack a number
                if (!digits.empty())
                {
                    // if this number has an adjacent symbol keep track of the position the symbol and of the adjacent number.
                    if (starPosition.first != -1 && starPosition.second != -1)
                    {
                        auto digitNumber = std::atoi(digits.c_str());
                        valueSymbolPosition.push_back(std::make_tuple(digitNumber, starPosition.first, starPosition.second));
                        starPosition = std::make_pair(-1, -1);
                    }
                }
                digits.clear();
            }
        }
    }

    auto gearRatio = 0;
    for (auto i = 1; i < matrix.size() - 1; ++i)
    {
        for (auto j = 1; j < matrix[i].size() - 1; ++j)
        {
            // if its 'T' it means its a gear
            if (matrix[i][j] == 'T')
            {
                // loop on the vector that tracks the position with the adjacent numbers
                for (auto &t : valueSymbolPosition)
                {
                    auto posX = std::get<1>(t);
                    auto posY = std::get<2>(t);

                    // if it our gear symbol 
                    if (posX == i && posY == j)
                    {
                        // if it is the first number 
                        if (gearRatio == 0)
                        {
                            gearRatio = std::get<0>(t);
                        }
                        else // if it is the second number; multiply and sum
                        {
                            gearRatio *= std::get<0>(t);
                            sum += gearRatio;
                            gearRatio = 0;
                            break;
                        }
                    }
                }
            }
        }
    }

    return sum;
}

bool isASymbol(const char &iChar)
{
    return ((iChar != '.') && (iChar < '0' || iChar > '9'));
}

bool isADigit(const char &iChar)
{
    return (iChar >= '0' && iChar <= '9');
}

void displayMatrix(const std::vector<std::vector<char>> &iMatrix)
{
    for (const auto &row : iMatrix)
    {
        for (char ch : row)
        {
            std::cout << ch << ' ';
        }
        std::cout << std::endl;
    }
}