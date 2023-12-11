#include <vector>
#include <string>


/// @brief 
/// @param iFilePath 
/// @return 
std::string readFile(const std::string &iFilePath);

/// @brief read content into vectors
/// @param iContent 
void getContent(const std::string& iContent);

/// @brief find how many ways is possible to win the race
/// @param iTime time of thr race
/// @param iDistance current record of the race
/// @return number of ways to win
template<typename T>
T possibleWays(T iTime, T iDistance);

/// @brief 
void puzzlePart1();

/// @brief 
void puzzlePart2();

/// @brief 
void display();