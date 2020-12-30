#include "functions.hpp"

#include <iosfwd>

#include "queue_with_priority.hpp"

void dergunov::executeFirstTask(std::istream & in, std::ostream & out)
{
  details::QueueWithPriority<std::string> queueWithPriority;
  details::executeConsoleQueue(out, in, queueWithPriority);
}
