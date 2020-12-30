#include "tasks.hpp"

#include <unordered_set>
#include <iterator>
#include <string>
#include <iostream>

#include "check-input.hpp"

void dergunov::B5::executeFirstTask(std::istream & in, std::ostream & out)
{
  std::unordered_set<std::string> uniqueWords((std::istream_iterator<std::string>(in)),
                                              std::istream_iterator<std::string>());
  ::details::checkRunTimeErrorInInput(in);
  ::details::checkInvalidInputIterator(in);

  std::copy(uniqueWords.cbegin(), uniqueWords.cend(), std::ostream_iterator<std::string>(out, "\n"));
}
