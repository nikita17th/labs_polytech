#include "console-interface.hpp"

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <boost/io/ios_state.hpp>

#include "common-functions.hpp"
#include "phone-book.hpp"
#include "exceptions-commands.hpp"

const std::map<std::string, console_t> OPERATIONS{
  {"add",    add},
  {"store",  store},
  {"insert", insert},
  {"delete", deleteMark},
  {"show",   show},
  {"move",   move}
};

struct steps_t {
  bool nowString;
  std::string stepsString;
  int stepsInt;
};

void executeConsoleMarkBook(MarkBook & markBook, std::ostream & os, std::istream & is)
{
  boost::io::ios_flags_saver ifs(is);
  std::skipws(is);

  while (!(is >> std::ws).eof())
  {
    try
    {
      executeOperation(markBook, os, is);
    }
    catch (const InvalidBookmark & invalidBookmark)
    {
      os << invalidBookmark.what() << std::endl;
    }
    catch (const InvalidStep & invalidStep)
    {
      os << invalidStep.what() << std::endl;
    }
    catch (const InvalidCommand & invalidCommand)
    {
      os << invalidCommand.what() << std::endl;
    }
    catch (const Empty & empty)
    {
      os << empty.what() << std::endl;
    }
  }

  if (!is.eof())
  {
    throw std::invalid_argument("Input data is incorrect");
  }
}

void executeOperation(MarkBook &markBook, std::ostream & os, std::istream & is)
{
  std::string command;
  is >> detail::skipBlanks >> command;

  auto found = OPERATIONS.find(command);

  if (found == OPERATIONS.end())
  {
    throw InvalidCommand();
  }
  OPERATIONS.at(command)(os, is)(markBook, os);
}

command_t add(std::ostream & os, std::istream & is)
{
  PhoneBook::phone_contact_t contact;
  readContact(contact, os, is);
  return [contact](MarkBook & markBook, std::ostream &)
  {
    markBook.add(contact);
  };
}

command_t store(std::ostream & os, std::istream & is)
{
  std::string markName;
  std::string newMarkName;

  readMarkName(markName, os, is);
  readMarkName(newMarkName, os, is);

  return [markName, newMarkName](MarkBook & markBook, std::ostream &)
  {
    markBook.store(markName, newMarkName);
  };
}

command_t insert(std::ostream & os, std::istream & is)
{
  std::string insertPlace;
  is >> detail::skipBlanks >> insertPlace;

  std::string markName;
  PhoneBook::phone_contact_t contact;

  readMarkName(markName, os, is);
  readContact(contact, os, is);
  if ((insertPlace != "before") && (insertPlace != "after"))
  {
    throw InvalidCommand();
  }

  return [insertPlace, markName, contact](MarkBook & markBook, std::ostream&)
  {
    if (insertPlace == "before")
    {
      markBook.insertBefore(markName, contact);
      return;
    }
    markBook.insertAfter(markName, contact);
  };
}

command_t deleteMark(std::ostream &os, std::istream &is)
{
  std::string markName;

  readMarkName(markName, os, is);

  return [markName](MarkBook & markBook, std::ostream &)
  {
    markBook.deleteBookmarkNote(markName);
  };
}

command_t show(std::ostream &os, std::istream &is)
{
  std::string markName;

  readMarkName(markName, os, is);

  return [markName](MarkBook & markBook, std::ostream & os)
  {
    markBook.show(markName, os);
  };
}

command_t move(std::ostream &os, std::istream &is)
{
  std::string markName;
  steps_t steps {false, "", 0};

  readMarkName(markName, os, is);

  try
  {
    readStep(steps, os, is);
  }
  catch (const std::invalid_argument &)
  {
    throw InvalidStep();
  }

  return [steps, markName](MarkBook & markBook, std::ostream &)
  {
    if (steps.nowString)
    {
      if (steps.stepsString == "first")
      {
        markBook.move(markName, MarkBook::MovePosition::FIRST);
      }

      if (steps.stepsString == "last")
      {
        markBook.move(markName, MarkBook::MovePosition::LAST);
      }
    }
    markBook.move(markName, steps.stepsInt);
  };
}

void readContact(PhoneBook::phone_contact_t & contact, std::ostream &, std::istream & is)
{
  is >> detail::skipBlanks >> contact.number;
  std::getline(is >> detail::skipBlanks , contact.name);

  if (!isCorrectNumber(contact.number))
  {
    throw InvalidCommand();
  }

  if (!isCorrectName(contact.name))
  {
    throw InvalidCommand();
  }

  for (std::string::iterator iterator = contact.name.begin(); iterator != contact.name.end(); iterator++)
  {
    if ((*iterator != contact.name.back()) && (*iterator == '\\') && (*std::next(iterator) == '\"'))
    {
      contact.name.erase(iterator);
    }
  }

  contact.name.erase(contact.name.begin());
  if (contact.name.back() == '\"')
  {
    contact.name.pop_back();
  }
}

void readMarkName(std::string & markName, std::ostream &, std::istream & is)
{
  is >> detail::skipBlanks >> markName;

  auto compareFunction = [](char compareChar)
  {
    return (std::isalpha(compareChar) == 0) && (std::isdigit(compareChar) == 0) && (compareChar != '-');
  };

  if (markName.empty() ||
      (std::find_if(markName.begin(), markName.end(), compareFunction) != markName.end()))
  {
    throw InvalidBookmark();
  }
}

void readStep(steps_t & steps, std::ostream &, std::istream &is)
{
  std::string input;
  is >> detail::skipBlanks >> input;

  if ((input == "first") || (input == "last"))
  {
    steps.nowString = true;
    steps.stepsString = input;
    return;
  }

  steps.stepsInt = std::stoi(input);
  steps.nowString = false;
}

bool isCorrectNumber(std::string const & number)
{
  if (number.empty())
  {
    return false;
  }

  return std::find_if(number.begin(), number.end(), [](char compareChar)
  {
    return std::isdigit(compareChar) == 0;
  }) == number.end();
}

bool isCorrectName(std::string const & name)
{
  if (name.empty() || (name.front() != '\"') || (name.back() != '\"'))
  {
    return false;
  }

  return std::find_if(name.begin(), name.end(), [](char compareChar)
  {
    return (std::isalpha(compareChar) == 0) && (compareChar != '\\') && (compareChar != '\"') &&
        (compareChar != ' ') && (compareChar != ',');
  }) == name.end();
}
