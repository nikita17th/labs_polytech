#include "phone-book.hpp"

#include <iterator>

void book::PhoneBook::pushBackRecord(phone_contact_t const & contact)
{
  phoneBook_.push_back(contact);
}

void book::PhoneBook::addRecordAfter(const PhoneBook::iterator_t iterator, phone_contact_t const & contact)
{
  phoneBook_.insert(std::next(iterator), contact);
}

void book::PhoneBook::addRecordBefore(const PhoneBook::iterator_t iterator, phone_contact_t const & contact)
{
  phoneBook_.insert(iterator, contact);
}

void book::PhoneBook::deleteRecord(const PhoneBook::iterator_t iterator)
{
  phoneBook_.erase(iterator);
}

book::PhoneBook::iterator_t book::PhoneBook::getBegin()
{
  return phoneBook_.begin();
}

book::PhoneBook::iterator_t book::PhoneBook::getEnd()
{
  return phoneBook_.end();
}

size_t book::PhoneBook::getSize() const
{
  return phoneBook_.size();
}

bool book::PhoneBook::isEmpty() const
{
  return phoneBook_.empty();
}
