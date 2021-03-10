#ifndef B3_PHONE_BOOK_HPP
#define B3_PHONE_BOOK_HPP

#include <string>
#include <list>
#include <vector>
#include <cstddef>

class PhoneBook
{
public:
  struct phone_contact_t
  {
    std::string number;
    std::string name;
  };
  using iterator_t =  std::list<phone_contact_t>::iterator;

  void pushBackRecord(phone_contact_t const & contact);
  void addRecordAfter(const iterator_t iterator, phone_contact_t const & contact);
  void addRecordBefore(const iterator_t iterator, phone_contact_t const & contact);

  void deleteRecord(const iterator_t iterator);

  iterator_t getBegin();
  iterator_t getEnd();
  std::size_t getSize() const;

  bool isEmpty() const;

private:
  std::list<phone_contact_t> phoneBook_;
};

#endif
