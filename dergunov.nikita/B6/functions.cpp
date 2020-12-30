#include "functions.hpp"
#include <algorithm>

#include <iterator>
#include <functional>

#include "statistic-functor.hpp"
void dergunov::B6::executeTask(std::istream &in, std::ostream &out)
{
  StatisticFunctor state;
  std::for_each(std::istream_iterator<int>(in), std::istream_iterator<int>(), std::ref(state));
  if (!in.eof()) {
    throw std::invalid_argument("");
  }
  out << state;
}
