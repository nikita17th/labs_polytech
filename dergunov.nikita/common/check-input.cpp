#include "check-input.hpp"

#include <string>
#include <iostream>
#include <stdexcept>

void details::checkRunTimeErrorInInput(std::istream const & in, std::string const & error)
{
  if (in.bad()) {
    throw std::runtime_error(error);
  }
}

void details::checkInvalidValuesInInput(std::istream const & in, std::string const & error)
{
  if (!in.eof() && in.fail()) {
    throw std::invalid_argument(error);
  }
}

void details::checkInvalidInputIterator(std::istream const & in, std::string const & error)
{
  if (!in.eof()) {
    throw std::invalid_argument(error);
  }
}
