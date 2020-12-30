#include "tasks.hpp"

#include <stdexcept>
#include <memory>
#include <fstream>

#include "function.hpp"


const char * SEPARATION_SYMBOL = "";
const double MAGNIFICATION_RATIO = 1.7;
const size_t BUFFER = 32;
const size_t START_CAPACITY = 64;

void dergunov::executeSecondTask(const char * fileName)
{
  if (fileName == nullptr) {
    throw std::invalid_argument("Empty string, expected file name!");
  }

  std::ifstream inputFile(fileName);

  if (!inputFile.is_open()) {
    throw std::runtime_error("File opening error!");
  }

  size_t capacity = START_CAPACITY;
  size_t sizeGetRead = 0;
  std::unique_ptr<char[]> charArray = std::make_unique<char[]>(capacity);

  if (charArray == nullptr) {
    throw std::bad_alloc();
  }

  if (inputFile.peek() == EOF) {
    return;
  }

  while (inputFile.good()) {
    inputFile.read(&charArray[sizeGetRead], BUFFER);
    sizeGetRead += inputFile.gcount();

    if (capacity - sizeGetRead <= BUFFER) {
      size_t newCapacity = static_cast<size_t>(static_cast<double>(capacity) * MAGNIFICATION_RATIO);
      std::unique_ptr<char[]> newCharArray = std::make_unique<char[]>(newCapacity);
      for (size_t i = 0; i < sizeGetRead; i++) {
        newCharArray[i] = charArray[i];
      }

      if (newCharArray == nullptr) {
        throw std::bad_alloc();
      }

      std::swap(newCharArray, charArray);
      capacity = newCapacity;
    }
  }

  if (inputFile.bad())
  {
    throw std::runtime_error("Unknown error input from file in fail second_task.cpp, on line 63!");
  }

  if (!inputFile.eof() && inputFile.fail()) {
    throw std::invalid_argument("Incorrect input from file, ""expected text chars, which end EOF,"
        " on file second_task.cpp!");
  }

  details::vectorChar charVector(&charArray[0], &charArray[sizeGetRead]);

  details::showContainer(charVector, SEPARATION_SYMBOL );

}
