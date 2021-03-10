#include "exceptions-commands.hpp"


InvalidBookmark::InvalidBookmark():
  error_("<INVALID BOOKMARK>")
{}

InvalidBookmark::InvalidBookmark(const std::string & error):
  error_(error)
{}

const char *InvalidBookmark::what() const noexcept
{
  return error_.c_str();
}

InvalidStep::InvalidStep():
  error_("<INVALID STEP>")
{}

InvalidStep::InvalidStep(const std::string &error):
  error_(error)
{}

const char *InvalidStep::what() const noexcept
{
  return error_.c_str();
}

InvalidCommand::InvalidCommand():
  error_("<INVALID COMMAND>")
{}

InvalidCommand::InvalidCommand(const std::string &error):
  error_(error)
{}

const char *InvalidCommand::what() const noexcept
{
  return error_.c_str();
}

Empty::Empty():
  error_("<EMPTY>")
{}

Empty::Empty(const std::string &error):
  error_(error)
{}

const char *Empty::what() const noexcept
{
  return error_.c_str();
}
