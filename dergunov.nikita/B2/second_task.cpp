#include "functions.hpp"

#include <list>
#include <iostream>
#include "check-input.hpp"

extern const char * BAD_CIN;

void dergunov::executeSecondTask(std::istream & in, std::ostream & out)
{
  std::list<int> intList;
  int inputNumber = 0;
  while (in >> inputNumber) {
    if (inputNumber < 1 || inputNumber > 20) {
      throw std::invalid_argument("Incorrect input, expected number from 1 to 20!");
    }
    intList.push_back(inputNumber);
  }

  details::checkRunTimeErrorInInput(in, BAD_CIN);

  std::string incorrectInput = "Incorrect input, expected sequence of integers, which end EOF!";
  details::checkInvalidValuesInInput(in, incorrectInput);

  if (intList.empty()) {
    return;
  }

  if (intList.size() > 20) {
    throw std::invalid_argument("Incorrect input, expected count of numbers from 0 to 20!");
  }

  details::output(intList, out);
}
