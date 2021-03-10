#ifndef B3_CONSOLE_INTERFACE_HPP
#define B3_CONSOLE_INTERFACE_HPP

#include <map>
#include <iostream>
#include <string>
#include <functional>

#include "phone-book.hpp"
#include "mark-book.hpp"
struct steps_t;

void executeConsoleMarkBook(MarkBook & markBook, std::ostream & os = std::cout, std::istream & is = std::cin);
void executeOperation(MarkBook & markBook, std::ostream & os = std::cout, std::istream & is = std::cin);

using command_t = std::function<void(MarkBook & markBook, std::ostream & os)>;
using console_t = std::function<command_t (std::ostream & os, std::istream & is)>;

command_t add(std::ostream & os = std::cout, std::istream & is = std::cin);
command_t store(std::ostream & os = std::cout, std::istream & is = std::cin);
command_t insert(std::ostream & os = std::cout, std::istream & is = std::cin);
command_t deleteMark(std::ostream & os = std::cout, std::istream & is = std::cin);
command_t show(std::ostream & os = std::cout, std::istream & is = std::cin);
command_t move(std::ostream & os = std::cout, std::istream & is = std::cin);

std::istream& operator>>(std::istream & is, command_t & command);

void readContact(PhoneBook::phone_contact_t &contact, std::ostream & os = std::cout, std::istream & is = std::cin);
void readMarkName(std::string & markName, std::ostream & os = std::cout, std::istream & is = std::cin);
void readStep(steps_t & steps, std::ostream & os = std::cout, std::istream & is = std::cin);

bool isCorrectNumber(std::string const & number);
bool isCorrectName(std::string const & name);

#endif
