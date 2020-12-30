#ifndef B2_FUNCTIONS_HPP
#define B2_FUNCTIONS_HPP

#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>

#include "queue_with_priority.hpp"
#include "check-input.hpp"

extern const char * BAD_CIN;
extern const char * INVALID_COMMAND;

namespace dergunov
{

  void executeFirstTask(std::istream & in, std::ostream & out);
  void executeSecondTask(std::istream & in, std::ostream & out);

}

namespace details
{

  enum class Direction
  {
    FROM_LEFT_TO_RIGHT,
    FROM_RIGHT_TO_LEFT
  };

  const std::map<std::string, details::ElementPriority> MAP_OF_PRIORITY{
      {"high",   ElementPriority::HIGH},
      {"normal", ElementPriority::NORMAL},
      {"low",    ElementPriority::LOW}
  };

  void output(std::list<int> & intList, std::ostream & out);

  template<typename T>
  void add(std::ostream & out, std::istream & in, QueueWithPriority<T> & queueWithPriority);

  template<typename T>
  void get(std::ostream & out, std::istream &, QueueWithPriority<T> & queueWithPriority);

  template<typename T>
  void accelerate(std::ostream &, std::istream &, QueueWithPriority<T> & queueWithPriority);

  template<typename T>
  void executeConsoleQueue(std::ostream & out, std::istream & in, QueueWithPriority<T> & queue);

  template<typename T>
  void executeOperation(std::ostream & out, std::istream & in, QueueWithPriority<T> & queue);

  template<typename T>
  using function = std::function<void(std::ostream &out, std::istream &in,
      QueueWithPriority<T> &queueWithPriority)>;

  template<typename T>
  const std::map<std::string, function<T>> OPERATIONS{
      {"add",        add<T>},
      {"get",        get<T>},
      {"accelerate", accelerate<T>}
  };

  template<typename T>
  void add(std::ostream & out, std::istream & in, QueueWithPriority<T> & queueWithPriority)
  {
    std::string priority;
    in >> priority >> std::ws;

    if (details::MAP_OF_PRIORITY.count(priority) == 0) {
      out << INVALID_COMMAND;
      return;
    }

    details::ElementPriority elementPriority;
    elementPriority = MAP_OF_PRIORITY.at(priority);

    T data;
    std::getline(in, data);
    if (data.empty()) {
      out << INVALID_COMMAND;
      return;
    }

    queueWithPriority.push(data, elementPriority);
  }

  template<typename T>
  void get(std::ostream & out, std::istream &, QueueWithPriority<T> & queueWithPriority)
  {
    if (queueWithPriority.empty()) {
      out << "<EMPTY>\n";
    } else {
      out << queueWithPriority.top() << "\n";
      queueWithPriority.pop();
    }
  }

  template<typename T>
  void accelerate(std::ostream &, std::istream &, QueueWithPriority<T> &queueWithPriority)
  {
    queueWithPriority.accelerate();
  }

  template<typename T>
  void executeOperation(std::ostream & out, std::istream & in, QueueWithPriority<T> & queueWithPriority)
  {
    std::string command;
    in >> command >> std::ws;

    if (OPERATIONS<T>.count(command) == 0) {
      out << INVALID_COMMAND;
      return;
    }
    OPERATIONS<T>.at(command)(out, in, queueWithPriority);
  }

  template<typename T>
  void executeConsoleQueue(std::ostream & out, std::istream & in, QueueWithPriority<T> &queueWithPriority)
  {

    std::string inputString;

    while (std::getline(in, inputString)) {
      std::istringstream in(inputString);
      executeOperation(out, in, queueWithPriority);
    }

    details::checkRunTimeErrorInInput(in, BAD_CIN);

    std::string incorrectInput = "Incorrect input, expected sequence of commands view <command>"
        "[<priority> <data>], which end EOF!";
    details::checkInvalidValuesInInput(in, incorrectInput);

  }

}

#endif
