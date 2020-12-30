#include "algorithm.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

#include "check-input.hpp"
#include "data-struct.hpp"


void dergunov::B4::executeAlgorithmOne(std::istream & in, std::ostream & out)
{
  DataStructVector dataStructVector;

  console::executeInput(dataStructVector, in, out);
  std::sort(dataStructVector.begin(), dataStructVector.end());
  console::executeOutput(dataStructVector, in, out);
}

void dergunov::B4::console::executeInput(dergunov::B4::DataStructVector & dataStructVector, std::istream & in,
    std::ostream & )
{
  using input_iterator_t = std::istream_iterator<DataStruct>;
  input_iterator_t first = std::istream_iterator<DataStruct>(in);
  input_iterator_t last = std::istream_iterator<DataStruct>();

  std::vector<DataStruct> inputVector(first, last);

  details::checkRunTimeErrorInInput(in);
  details::checkInvalidValuesInInput(in, errorMessages:: INCORRECT_INPUT);

  dataStructVector = std::move(inputVector);
}

void dergunov::B4::console::executeOutput(dergunov::B4::DataStructVector const & dataStructVector, std::istream &,
    std::ostream & out)
{
  std::ostream_iterator<DataStruct> outIterator(out, "\n");
  std::copy(dataStructVector.begin(), dataStructVector.end(), outIterator);
}
