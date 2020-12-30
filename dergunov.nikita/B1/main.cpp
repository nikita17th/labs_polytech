#include <iostream>
#include <exception>
#include <string>

#include "tasks.hpp"

const char * INVALID_COUNT_PARAMETERS = "The number of parameters does not match, expected ";
const char * INVALID_TASK_NUMBER = "Invalid sub-job number entered, expected  from one to four!";

enum struct TaskNumber: int
{
  FIRST = 1,
  SECOND = 2,
  THIRD = 3,
  FOURTH = 4
};

int main(int argc, char * argv[])
{
  try
  {
    if (argc < 2 || argc > 4) {
      std::cerr << INVALID_COUNT_PARAMETERS << "from one two three parameters!";
      return 1;
    }

    TaskNumber taskNumber = static_cast<TaskNumber>(std::stoul(argv[1]));

    switch (taskNumber) {
      case TaskNumber::FIRST:
        if (argc != 3) {
          std::cerr << INVALID_COUNT_PARAMETERS << "two parameters!";
          return 1;
        }
        dergunov::executeFirstTask(argv[2]);
        break;
      case TaskNumber::SECOND:
        if (argc != 3) {
          std::cerr << INVALID_COUNT_PARAMETERS << "two parameters!";
          return 1;
        }
        dergunov::executeSecondTask(argv[2]);
        break;
      case TaskNumber::THIRD:
        if (argc != 2) {
          std::cerr << INVALID_COUNT_PARAMETERS << "one parameter!";
          return 1;
        }
        dergunov::executeThirdTask();
        break;
      case TaskNumber::FOURTH:
        if (argc != 4) {
          std::cerr << INVALID_COUNT_PARAMETERS << "three parameters!";
          return 1;
        }
        dergunov::executeFourthTask(argv[2], argv[3]);
        break;
      default:
        std::cerr << INVALID_TASK_NUMBER;
        return 1;
    }

  }
  catch (std::exception const & exception)
  {
    std::cerr << exception.what();
    return 1;
  }

  return 0;
}
