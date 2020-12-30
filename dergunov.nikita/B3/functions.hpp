#ifndef B3_FUNCTIONS_HPP
#define B3_FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <map>

#include "phone-book.hpp"

namespace dergunov
{

  void executeFirstTask(std::istream & in = std::cin, std::ostream & out = std::cout);
  void executeSecondTask(std::istream & in = std::cin, std::ostream & out = std::cout);

}

namespace book {

  using MarkBook = std::map<std::string, book::PhoneBook::iterator_t>;
  using iteratorMarkBook_t = std::map<std::string, book::PhoneBook::iterator_t>::iterator;
  struct steps_t;

}

namespace console
{

  void executeConsoleMarkBook(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out = std::cout,
      std::istream & in = std::cin);
  void executeOperation(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out = std::cout,
      std::istream & in = std::cin);

  void add(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out = std::cout,
      std::istream & in = std::cin);
  void store(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out = std::cout,
      std::istream & in = std::cin);
  void insert(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out = std::cout,
      std::istream & in = std::cin);
  void deleteMark(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out = std::cout,
      std::istream & in = std::cin);
  void show(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out = std::cout,
      std::istream & in = std::cin);
  void move(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out = std::cout,
      std::istream & in = std::cin);

  bool readContact(book::PhoneBook::phone_contact_t &contact, std::ostream & out = std::cout,
      std::istream & in = std::cin);
  bool readMarkName(std::string & markName, std::ostream & out = std::cout, std::istream & in = std::cin);
  bool readStep(book::steps_t & steps, std::ostream & out = std::cout, std::istream & in = std::cin);

  bool isCorrectNumber(std::string const & number);
  bool isCorrectName(std::string const & name);
  bool isBookMarkExist(book::MarkBook & markBook, std::string const & markName);

}

#endif
