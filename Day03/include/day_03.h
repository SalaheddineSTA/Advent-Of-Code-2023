#include <vector>
#include <string>


/// @brief read the input file into a matrix  of char (vector of vector).
/// @param iFilePath file path.
/// @return raw data as a matrix of char.
std::vector<std::vector<char>> readFile(const std::string& iFilePath);

/// @brief add surrounding symbol '.' to the matrix.
/// @param iOriginalMatrix the input matrix.
/// @return expanded matrix.
std::vector<std::vector<char>> expandMatrix(const std::vector<std::vector<char>>& iOriginalMatrix);

/// @brief check if the element (iX,iY) in the matrix has an adjacent symbol.
/// @param iMatrix input matrix.
/// @param iX x position.
/// @param iY y position.
/// @return true if has an adjacent symbol.
bool hasAdjacentSymbol(const std::vector<std::vector<char>>& iMatrix, const unsigned iX,const unsigned iY);

/// @brief check if the element (iX,iY) in the matrix has an adjacent symbol.
/// if yes return its position and change the symbol ('*' -> 'O' -> 'T' -> '#'); else return (-1,-1).
/// @param iMatrix the input matrix.
/// @param iX x position.
/// @param iY y position.
/// @return '*' position it found, else (-1,-1).
std::pair<int, int> hasAdjacentSymbolWithChanging(std::vector<std::vector<char>> &ioMatrix, const unsigned iX, const unsigned iY);

/// @brief solve the part one of day 3. sum all the numbers that have an adjacent symbol.
/// @param iMatrix the input matrix.
/// @return the sum of all the numbers that have adjacent symbol.
unsigned engineParts(const std::vector<std::vector<char>>& iMatrix);

/// @brief solve the part two of day 3. sum all the gearRation (Multiply the two numbers that have a shared adjacent '*'). 
/// @param iMatrix the input matrix.
/// @return the sum of all the numbers that have adjacent symbol.
unsigned engineGear(const std::vector<std::vector<char>>& iMatrix);

/// @brief check if char is a symbol(!= '.' < '0' > '9')
/// @param iChar 
/// @return true if is a symbol; else false.
bool isASymbol(const char& iChar);

/// @brief check if char is a digit
/// @param iChar 
/// @return true if is a digit; else false.
bool isADigit(const char &iChar);

/// @brief diplay the matrix
/// @param iMatrix input matrix
void displayMatrix(const std::vector<std::vector<char>>& iMatrix );