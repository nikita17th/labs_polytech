#include <iostream>
#include <stdexcept>

#include "algorithm.hpp"

int main()
{
  try
  {
    executeAlgorithm();
  }
  catch (const std::invalid_argument &ex)
  {
    std::cerr << ex.what();
    return 1;
  }
  catch (const std::out_of_range &ex)
  {
    std::cerr << ex.what();
    return 1;
  }

  return 0;
}
