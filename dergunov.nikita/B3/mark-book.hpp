#ifndef B3_MARK_BOOK_HPP
#define B3_MARK_BOOK_HPP

#include <memory>
#include <map>
#include <string>
#include <iosfwd>

#include "phone-book.hpp"

class MarkBook
{
public:
  enum class MovePosition
  {
    FIRST,
    LAST
  };
  using iterator = std::map<std::string, PhoneBook::iterator_t>::iterator;

  explicit MarkBook(const std::shared_ptr<PhoneBook>& phoneBook);

  void add(const PhoneBook::phone_contact_t & contact);
  void store(const std::string & markName, const std::string & newMarkName);
  void insertAfter(const std::string & markName, const PhoneBook::phone_contact_t & contact);
  void insertBefore(const std::string & markName, const PhoneBook::phone_contact_t & contact);
  void deleteBookmarkNote(const std::string & markName);
  void show(const std::string & markName, std::ostream & os);
  void move(const std::string & markName, int step);
  void move(const std::string & markName, MovePosition pos);
private:
  std::shared_ptr<PhoneBook> phoneBook_;
  std::map<std::string, PhoneBook::iterator_t> markBook_;
  iterator find(const std::string& markName);
};

#endif
