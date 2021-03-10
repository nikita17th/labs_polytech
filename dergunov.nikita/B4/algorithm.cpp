#include "algorithm.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

#include "data-struct.hpp"

void executeAlgorithm(std::istream & is, std::ostream & os)
{
  using input_iterator_t = std::istream_iterator<DataStruct>;
  input_iterator_t first = std::istream_iterator<DataStruct>(is);
  input_iterator_t last = std::istream_iterator<DataStruct>();

  DataStructVector dataStructVector(first, last);
  if (!is.eof())
  {
    throw std::invalid_argument("Input data is incorrect!");
  }

  std::sort(dataStructVector.begin(), dataStructVector.end());

  std::ostream_iterator<DataStruct> outIterator(os, "\n");
  std::copy(dataStructVector.begin(), dataStructVector.end(), outIterator);
}
