#include <vector>
#include <string>

/// @brief read the input file into a vector. each line is in a case in the vector.
/// @param iFilePath file path
/// @return raw data as a vector.
std::vector<std::string> readFile(const std::string& iFilePath);

/// @brief extract digits from each line 
/// @param iRawData raw data.
/// @return osum of calibration values.
unsigned sumCalibrationValues(const std::vector<std::string>& iRawData);

/// @brief extract digits from each line. consediring the digits-spelled-out-with-letters.
/// using transformString
/// @param iRawData raw data.
/// @return osum of calibration values.
unsigned sumCalibrationValuesPart2(const std::vector<std::string>& iRawData);

/// @brief instert before the digits-spelled-out-with-letters the actual digit in the input string.
/// ~~~~~~~
/// 8sevenjkdsfhfive2kfdh ==> 87sevenjkdsfh5five2kfdh
/// ~~~~~~~
/// @param iStr input string.
/// @return transformed string.
std::string transformString(const std::string& iStr);