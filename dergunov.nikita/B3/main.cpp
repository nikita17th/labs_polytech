#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>
#include <map>
#include <functional>

#include "functions.hpp"

namespace details
{
  enum struct TaskNumber
  {
      FIRST = 1,
      SECOND = 2
  };

  using taskFunction_t = std::function<void(std::istream & in, std::ostream & out)>;
  const std::map<TaskNumber, taskFunction_t> TASKS {
      {TaskNumber::FIRST, dergunov::executeFirstTask},
      {TaskNumber::SECOND, dergunov::executeSecondTask}
  };
}


int main(int argc, char * argv[])
{
  if (argc != 2) {
    std::cerr << "Incorrect count parameters, expected one parameter!";
    return 1;
  }

  try
  {
    details::TaskNumber taskNumber = static_cast<details::TaskNumber>(std::stoul(argv[1]));

    if (details::TASKS.count(taskNumber) == 0) {
      std::cerr << "Invalid sub-job number entered, expected one or two";
      return 1;
    }

    details::TASKS.at(taskNumber)(std::cin, std::cout);
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
