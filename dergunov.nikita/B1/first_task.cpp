#include "tasks.hpp"
#include <stdexcept>
#include <forward_list>
#include <iostream>

#include "access.hpp"
#include "sort.hpp"
#include "function.hpp"

const char * EMPTY_ORDER = "Empty string, expected ascending or descending!";
const char * BAD_CIN = "Unknown error input stream!";
const char * INCORRECT_INPUT = "Incorrect input, expected sequence of integers, which end EOF!";

void dergunov::executeFirstTask(const char * order)
{
  if (order == nullptr)
  {
    throw std::invalid_argument(EMPTY_ORDER);
  }
  details::typeSorting directionOrder = details::chooseSortDirection(order);

  details::vectorInt bracketsVector;
  details::vectorInt atVector;
  std::forward_list<int> forwardList;

  int inputNumber = 0;
  while (std::cin >> inputNumber) {
    bracketsVector.push_back(inputNumber);
    atVector.push_back(inputNumber);
    forwardList.push_front(inputNumber);
  }

  if (std::cin.bad())
  {
    throw std::runtime_error(BAD_CIN);
  }

  if (!std::cin.eof() && std::cin.fail()) {
    throw std::invalid_argument(INCORRECT_INPUT) ;
  }


  if (bracketsVector.empty()) {
    return;
  }


  details::bubbleSort<details::AccessByBrackets<details::vectorInt>>(bracketsVector, directionOrder);
  details::bubbleSort<details::AccessByAt<details::vectorInt>>(atVector, directionOrder);
  details::bubbleSort<details::AccessByListIterator<std::forward_list<int>>>(forwardList, directionOrder);

  details::showContainer(bracketsVector);
  details::showContainer(atVector);
  details::showContainer(forwardList);
}
