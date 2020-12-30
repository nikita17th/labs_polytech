#include "functions.hpp"

#include <iosfwd>

#include "phone-book.hpp"


void dergunov::executeFirstTask(std::istream & in, std::ostream & out)
{
  book::PhoneBook phoneBook;
  std::map<std::string, book::PhoneBook::iterator_t> markBook;

  console::executeConsoleMarkBook(markBook, phoneBook, out, in);
}
