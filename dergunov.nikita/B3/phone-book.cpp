#include "phone-book.hpp"
#include <cstddef>

void PhoneBook::pushBackRecord(phone_contact_t const & contact)
{
  phoneBook_.push_back(contact);
}

void PhoneBook::addRecordAfter(const PhoneBook::iterator_t iterator, phone_contact_t const & contact)
{
  phoneBook_.insert(std::next(iterator), contact);
}

void PhoneBook::addRecordBefore(const PhoneBook::iterator_t iterator, phone_contact_t const & contact)
{
  phoneBook_.insert(iterator, contact);
}

void PhoneBook::deleteRecord(const PhoneBook::iterator_t iterator)
{
  phoneBook_.erase(iterator);
}

PhoneBook::iterator_t PhoneBook::getBegin()
{
  return phoneBook_.begin();
}

PhoneBook::iterator_t PhoneBook::getEnd()
{
  return phoneBook_.end();
}

size_t PhoneBook::getSize() const
{
  return phoneBook_.size();
}

bool PhoneBook::isEmpty() const
{
  return phoneBook_.empty();
}
