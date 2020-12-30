#include "tasks.hpp"

#include <iostream>

#include "function.hpp"

const int NUMBER_OF_ONE = 3;
const int INSERT_ONE = 1;

namespace details
{
  void deleteEvenElements(std::vector<int> & intVector);
  void addThreeOneAfterElementsDivisibleByThree(std::vector<int> & intVector);
}

void dergunov::executeThirdTask()
{
  int inputNumber = 0;
  details::vectorInt intVector;

  while (std::cin >> inputNumber) {
    if (inputNumber == 0) {
      break;
    }
    intVector.push_back(inputNumber);

  }

  if (std::cin.bad()) {
    throw std::runtime_error("Unknown error input stream in fail!");
  }

  if (inputNumber != 0) {
    throw std::invalid_argument("Incorrect input, expected end symbol zero!");
  }

  if (!std::cin.eof() && std::cin.fail()) {
    throw std::invalid_argument("Incorrect input, expected sequence of integers, which end 0!") ;
  }

  if (intVector.empty()) {
    return;
  }

  int lastInt = intVector.back();
  switch (lastInt) {
    case 1:
      details::deleteEvenElements(intVector);
      break;
    case 2:
      details::addThreeOneAfterElementsDivisibleByThree(intVector);
      break;
    default:
      break;
  }

  details::showContainer(intVector);

}

void details::deleteEvenElements(vectorInt & intVector)
{
  for (iteratorVector nowElement = intVector.begin(); nowElement != intVector.end(); nowElement++) {
    if (*nowElement % 2 == 0) {
      intVector.erase(nowElement--);
    }
  }
}

void details::addThreeOneAfterElementsDivisibleByThree(vectorInt & intVector)
{
  for (iteratorVector nowElement = intVector.begin(); nowElement != intVector.end(); nowElement++) {
    if (*nowElement % 3 == 0) {
      nowElement = intVector.insert(++nowElement, NUMBER_OF_ONE, INSERT_ONE) + (NUMBER_OF_ONE - 1);
    }
  }
}
