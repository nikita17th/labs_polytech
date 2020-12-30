#include <iostream>
#include <stdexcept>
#include <exception>

#include "functions.hpp"

enum struct TaskNumber
{
    FIRST = 1,
    SECOND = 2
};

int main(int argc, char * argv[])
{

  if (argc != 2) {
    std::cerr << "Incorrect count parameters, expected one parameter!";
    return 1;
  }

  TaskNumber taskNumber = static_cast<TaskNumber>(std::stoul(argv[1]));

  try
  {
    switch (taskNumber) {
      case TaskNumber::FIRST:
        dergunov::executeFirstTask(std::cin, std::cout);
        break;
      case TaskNumber::SECOND:
        dergunov::executeSecondTask(std::cin, std::cout);
        break;
      default:
        std::cerr << "Invalid sub-job number entered, expected one or two";
        return 1;
    }
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
