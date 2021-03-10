#include "tasks.hpp"

#include <iosfwd>

#include "phone-book.hpp"
#include "console-interface.hpp"
#include "mark-book.hpp"

#include <memory>

void executeFirstTask(std::istream & in, std::ostream & out)
{
  MarkBook markBook(std::make_shared<PhoneBook>(PhoneBook()));
  executeConsoleMarkBook(markBook, out, in);
}

