#include <vector>
#include <string>


/// @brief read the input file into a vector. each line is in a case in the vector.
/// keep only the part after "Game ID:".
/// @param iFilePath file path
/// @return raw data as a vector.
std::vector<std::string> readFile(const std::string& iFilePath);

/// @brief check if game is possible
/// @param iStrings the input game lines. 
/// @return true if game is possible; else flase.
bool gameIsPossible (const std::string& iStrings);

/// @brief determine the possible games. the games that match the limits requirement.
/// @param iStrings the input game lines.
/// @return game IDs in a vector.
std::vector<unsigned> determinePossibleGames(const std::vector<std::string>& iStrings);

/// @brief split string into multiple sub strings using the input delimiter.
/// @param iString input string.
/// @param iDelimiter input delimiter.
/// @return vector of sub strings.
std::vector<std::string> splitString(const std::string& iString, const std::string& iDelimiter);

/// @brief check if char is a a digit
/// @param iChar 
/// @return true if is a digit; else false.
bool isADigit(const char& iChar);

/// @brief find the minimum set of cubes that must have been present in each game.
/// @param iStrings input game string.
/// @return the power of these sets (multiplication of the minimum cubes).
unsigned minimumCubes(const std::string& iStrings);

/// @brief find the power of sets for each game
/// @param iStrings games strings.
/// @return vector of the power of sets for each game.
std::vector<unsigned> determinePossibleGamesPart2(const std::vector<std::string> &iStrings);