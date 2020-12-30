#include "functions.hpp"

#include <map>
#include <sstream>
#include <functional>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

#include "check-input.hpp"
#include "phone-book.hpp"

namespace errorMessages
{

  const char * INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";
  const char * INVALID_STEP = "<INVALID STEP>\n";
  const char * INVALID_COMMAND = "<INVALID COMMAND>\n";

}

namespace book
{

  const char * EMPTY = "<EMPTY>\n";
  const char * DEFAULT_NAME_MARK = "current";
  struct steps_t {
    bool nowString;
    std::string stepsString;
    int stepsInt;
  };

}

namespace console
{

  using command_t = std::function<void(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out,
      std::istream & in)>;
  const std::map<std::string, command_t> OPERATIONS{
      {"add",    add},
      {"store",  store},
      {"insert", insert},
      {"delete", deleteMark},
      {"show",   show},
      {"move",   move}
  };

}

void console::executeConsoleMarkBook(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out,
    std::istream & in)
{
  markBook[book::DEFAULT_NAME_MARK] = phoneBook.getBegin();

  std::string input;
  while (std::getline(in, input)) {
    std::istringstream inputStream = std::istringstream(input);
    executeOperation(markBook, phoneBook, out, inputStream);
  }

  details::checkRunTimeErrorInInput(in);

  std::string incorrectInput = "Incorrect input, expected sequence of commands view <command> and"
      "[<markName> [<newMarkName>]] or [<number> <\"name\">] or [<markName> <number> <\"name\">] or "
      "[<markName> <steps>], which end EOF!";

  details::checkInvalidValuesInInput(in, incorrectInput);
}

void console::executeOperation(book::MarkBook &markBook, book::PhoneBook & phoneBook, std::ostream & out,
    std::istream & in)
{
  std::string command;
  in >> std::ws >> command >> std::ws;

  if (console::OPERATIONS.count(command) == 0) {
    out << errorMessages::INVALID_COMMAND;
    return;
  }

  OPERATIONS.at(command)(markBook, phoneBook, out, in);
}

void console::add(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out, std::istream & in)
{
  book::PhoneBook::phone_contact_t contact;
  if (!readContact(contact, out, in)) {
    out << errorMessages::INVALID_COMMAND;
    return;
  }

  phoneBook.pushBackRecord(contact);
  if (phoneBook.getSize() == 1) {
    markBook[book::DEFAULT_NAME_MARK] = phoneBook.getBegin();
  }
}

void console::store(book::MarkBook & markBook, book::PhoneBook &, std::ostream & out, std::istream & in)
{
  std::string markName;
  std::string newMarkName;

  if (!readMarkName(markName, out, in) || !readMarkName(newMarkName, out, in)) {
    out << errorMessages::INVALID_COMMAND;
    return;
  }

  if (!isBookMarkExist(markBook, markName)) {
    out << errorMessages::INVALID_BOOKMARK;
    return;
  }

  markBook[newMarkName] = markBook[markName];
}

void console::insert(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream & out, std::istream & in)
{
  std::string insertPlace;
  in >> std::ws >> insertPlace >> std::ws;

  if ((insertPlace != "before") && (insertPlace != "after")) {
    out << errorMessages::INVALID_COMMAND;
    return;
  }

  std::string markName;
  book::PhoneBook::phone_contact_t contact;

  if (!readMarkName(markName, out, in) || !readContact(contact, out, in)) {
    out << errorMessages::INVALID_COMMAND;
    return;
  }

  if (!isBookMarkExist(markBook, markName)) {
    out << errorMessages::INVALID_BOOKMARK;
    return;
  }

  if (insertPlace == "before") {
    phoneBook.addRecordBefore(markBook[markName], contact);
    book::PhoneBook::iterator_t iterator = markBook[markName];
    markBook[markName] = std::prev(iterator);
    return;
  }

  phoneBook.addRecordAfter(markBook[markName], contact);
  book::PhoneBook::iterator_t iterator = markBook[markName];
  markBook[markName] = std::next(iterator);
}

void console::deleteMark(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream &out, std::istream &in)
{
  std::string markName;

  if (!readMarkName(markName, out, in)) {
    out << errorMessages::INVALID_COMMAND;
    return;
  }

  if (!isBookMarkExist(markBook, markName))
  {
    out << errorMessages::INVALID_BOOKMARK;
    return;
  }

  if (phoneBook.isEmpty()) {
    out << book::EMPTY;
    return;
  }

  book::PhoneBook::iterator_t deletedElement = markBook[markName];

  for (book::iteratorMarkBook_t iterator = markBook.begin(); iterator != markBook.end(); iterator++) {
    if (iterator->second == deletedElement) {
      if (iterator->second == std::prev(phoneBook.getEnd())) {
        iterator->second = std::prev(iterator->second);
      } else {
        iterator->second = std::next(iterator->second);
      }
    }
  }

  phoneBook.deleteRecord(deletedElement);
}

void console::show(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream &out, std::istream &in)
{
  std::string markName;

  if (!readMarkName(markName, out, in)) {
    out << errorMessages::INVALID_COMMAND;
    return;
  }

  if (!isBookMarkExist(markBook, markName)) {
    out << errorMessages::INVALID_BOOKMARK;
    return;
  }

  if (phoneBook.isEmpty()) {
    out << book::EMPTY;
    return;
  }

  book::PhoneBook::phone_contact_t contact = *markBook[markName];
  out << contact.number << " " << contact.name << "\n";
}

void console::move(book::MarkBook & markBook, book::PhoneBook & phoneBook, std::ostream &out, std::istream &in)
{
  std::string markName;

  book::steps_t steps {false, "", 0};

  if (!readMarkName(markName, out, in)) {
    out << errorMessages::INVALID_COMMAND;
    return;
  }

  if (!isBookMarkExist(markBook, markName)) {
    out << errorMessages::INVALID_BOOKMARK;
    return;
  }

  if (!readStep(steps, out, in)) {
    out << errorMessages::INVALID_STEP;
    return;
  }

  if (steps.nowString) {
    if (steps.stepsString == "first") {
      markBook[markName] = phoneBook.getBegin();
      return;
    }

    if (steps.stepsString == "last") {
      markBook[markName] = std::prev(phoneBook.getEnd());
      return;
    }
  }

  int intSteps = steps.stepsInt;

  if (((intSteps < 0) && std::distance(phoneBook.getBegin(), markBook[markName]) < (-1 * intSteps)) ||
      ((intSteps > 0) && std::distance(markBook[markName], phoneBook.getEnd()) < intSteps)) {
    throw std::out_of_range("Out of the phoneBook, when move!");
  }

  std::advance(markBook[markName], intSteps);
}

bool console::readContact(book::PhoneBook::phone_contact_t & contact, std::ostream &, std::istream & in)
{
  in >> std::ws >> contact.number >> std::ws;

  if (!isCorrectNumber(contact.number)) {
    return false;
  }

  std::getline(in, contact.name);

  if (!isCorrectName(contact.name)) {
    return false;
  }

  for (std::string::iterator iterator = contact.name.begin(); iterator != contact.name.end(); iterator++) {
    if ((*iterator != contact.name.back()) && (*iterator == '\\') && (*std::next(iterator) == '\"')) {
      contact.name.erase(iterator);
    }
  }

  contact.name.erase(contact.name.begin());
  if (contact.name.back() == '\"') {
    contact.name.pop_back();
  }

  return true;
}

bool console::readMarkName(std::string & markName, std::ostream &, std::istream & in)
{
  in >> std::ws >> markName >> std::ws;

  if (markName.empty()) {
    return false;
  }

  return std::find_if(markName.begin(), markName.end(), [](char compareChar) {return (std::isalpha(compareChar) == 0) &&
      (std::isdigit(compareChar) == 0) && compareChar != '-';}) == markName.end();
}

bool console::readStep(book::steps_t & steps, std::ostream &, std::istream &in)
{
  std::string input;
  in >> std::ws >> input >> std::ws;

  if ((input == "first") || (input == "last")) {
    steps.nowString = true;
    steps.stepsString = input;
    return true;
  }
  try
  {
    steps.stepsInt = std::stoi(input);
    steps.nowString = false;
    return true;
  }
  catch (std::invalid_argument const & invalidArgument) {
    return false;
  }
  catch (...) {
    throw;
  }
}

bool console::isCorrectNumber(std::string const & number)
{
  if (number.empty()) {
    return false;
  }

  return std::find_if(number.begin(), number.end(), [](char compareChar) {return std::isdigit(compareChar) == 0;}) ==
      number.end();
}

bool console::isCorrectName(std::string const & name)
{
  if (name.empty() || (name.front() != '\"') || (name.back() != '\"')) {
    return false;
  }

  return std::find_if(name.begin(), name.end(), [](char compareChar) { return (std::isalpha(compareChar) == 0) &&
      (compareChar != '\\') && (compareChar != '\"') && (compareChar != ' ') && (compareChar != ',');}) == name.end();
}

bool console::isBookMarkExist(book::MarkBook & markBook, std::string const & markName)
{
  return 0 != markBook.count(markName);
}
