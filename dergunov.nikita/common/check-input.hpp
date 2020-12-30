#ifndef COMMON_CHECK_INPUT_HPP
#define COMMON_CHECK_INPUT_HPP

#include <iosfwd>
#include <string>

namespace details
{
  const std::string BAD_CIN = "Unknown error input stream!";
  const std::string INCORRECT_INPUT =  "Incorrect input, expected right dats!";

  void checkRunTimeErrorInInput(std::istream const & in, std::string const & error = BAD_CIN);
  void checkInvalidValuesInInput(std::istream const & in, std::string const & error = INCORRECT_INPUT);
  void checkInvalidInputIterator(std::istream const & in, std::string const & error = INCORRECT_INPUT);
}

#endif
