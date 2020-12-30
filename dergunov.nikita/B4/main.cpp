#include <iostream>
#include <stdexcept>
#include <exception>

#include "algorithm.hpp"

int main()
{
  try
  {
    dergunov::B4::executeAlgorithmOne(std::cin, std::cout);
  }
  catch (std::invalid_argument const & invalidArgumentException) {
    std::cerr << invalidArgumentException.what();
    return 1;
  }
  catch (std::exception const & exception) {
    std::cerr << exception.what();
    return 2;
  }

  return 0;
}
