#include "tasks.hpp"

#include <string>
#include <random>
#include <stdexcept>

#include "access.hpp"
#include "sort.hpp"
#include "function.hpp"

extern const char * EMPTY_ORDER;

namespace details
{
  void fillRandom(double * array, int size);
}

void dergunov::executeFourthTask(const char * order, const char * size)
{
  if (order == nullptr) {
    throw std::invalid_argument(EMPTY_ORDER);
  }

  if (size == nullptr) {
    throw std::invalid_argument("Empty string, expected size of array double!");
  }

  size_t sizeVector = std::stoul(size);
  details::vectorDouble doubleVector(sizeVector);

  details::fillRandom(&doubleVector[0], sizeVector);

  details::typeSorting directionOrder = details::chooseSortDirection(order);

  details::showContainer(doubleVector);

  details::bubbleSort<details::AccessByBrackets<details::vectorDouble>>(doubleVector, directionOrder);

  details::showContainer(doubleVector);
}

void details::fillRandom(double * array, int size)
{
  if (array == nullptr) {
    throw std::invalid_argument("Error passed a null pointer to an array, in file random.cpp");
  }

  if (size < 0) {
    throw std::invalid_argument("Invalid array size, expected  number more or equal zero, in fail random.cpp");
  }

  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);

  size_t sizeArray = static_cast<size_t>(size);
  for (size_t i = 0; i < sizeArray; i++) {
    array[i] = distribution(generator);
  }
}
