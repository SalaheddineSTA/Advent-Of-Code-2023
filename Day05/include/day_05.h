#include <vector>
#include <string>


/// @brief read the input file into a matrix  of char (vector of vector).
/// @param iFilePath file path.
/// @return raw data as a matrix of char.
std::pair<std::vector<std::vector<unsigned>>,std::vector<std::vector<unsigned>>> readFile(const std::string& iFilePath);

/// @brief solve part one of day four; count the point for winning cards(if a card have more than one winning number,
///  double the point each winning number).
/// @param iwinning list of winning numbers.
/// @param iPlaying list of playing numbers.
/// @return the sum of the points.
unsigned countPoints(const std::vector<std::vector<unsigned>> &iwinning,const std::vector<std::vector<unsigned>> &iPlaying);

/// @brief solve part two of day four; count the number of cards. If a card have 'X' winning numbers, duplicate the 'X' next cards 
/// (including their copies) as much as the winning numbers. (if card1 have 2 winning numbers, make a copy of the 2 next cards and
/// do the same for each copy the 2 cards).
/// @param iwinning list of winning numbers.
/// @param iPlaying list of playing numbers.
/// @return the number of the cards.
unsigned countPointsWithRewards(const std::vector<std::vector<unsigned>> &iwinning,const std::vector<std::vector<unsigned>> &iPlaying);
