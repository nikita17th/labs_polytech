#include "functions.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <functional>

const char * INVALID_COMMAND = "<INVALID COMMAND>\n";
const char * BAD_CIN = "Unknown error input stream!";

void details::output(std::list<int> & intList, std::ostream & out)
{
  using iteratorList = std::list<int>::iterator;

  details::Direction direction = Direction::FROM_LEFT_TO_RIGHT;
  iteratorList first = intList.begin();
  iteratorList last = intList.end();

  while (first != last) {
    if (direction == Direction::FROM_LEFT_TO_RIGHT) {
      out << *first;
      first++;
      direction = details::Direction::FROM_RIGHT_TO_LEFT;
    } else {
      last--;
      out << *last;
      direction = details::Direction::FROM_LEFT_TO_RIGHT;
    }

    if (first != last) {
      out << " ";
    }

  }
  out << "\n";
}
