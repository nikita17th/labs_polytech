#include "functions.hpp"

#include <algorithm>
#include <iterator>
#include <iosfwd>
#include <ostream>

#include"factorial.hpp"

void dergunov::executeSecondTask(std::istream &, std::ostream &out)
{
  factorial::Container factorials;

  std::ostream_iterator<size_t> outIterator(out, " ");

  std::copy(factorials.begin(), factorials.end(), outIterator);
  out << "\n";
  
  std::reverse_copy(factorials.begin(), factorials.end(), outIterator);
  out << "\n";
}
