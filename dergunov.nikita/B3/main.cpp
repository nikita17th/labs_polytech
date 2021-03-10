#include <iostream>
#include <string>
#include <stdexcept>
#include "tasks.hpp"

int main(int args, char *argv[])
{
  if (args != 2)
  {
    std::cerr << "Incorrect number of parameters";
    return 1;
  }

  try
  {
    switch (std::stoi(argv[1]))
    {
      case 1:
      {
        executeFirstTask();
        break;
      }
      case 2:
      {
        executeSecondTask();
        break;
      }
      default:
      {
        std::cerr << "Invalid parameters";
        return 1;
      }
    }
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
