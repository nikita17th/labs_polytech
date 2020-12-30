#include <iostream>
#include <exception>
#include <stdexcept>
#include "functions.hpp"

int main()
{
  try
  {
    dergunov::B6::executeTask();
  }
  catch (std::invalid_argument  const & invalidArgumentException)
  {
    std::cerr << invalidArgumentException.what();
    return 1;
  }
  catch (std::exception const & exception) {
    std::cerr << exception.what();
    return 2;
  }
  return 0;
}
