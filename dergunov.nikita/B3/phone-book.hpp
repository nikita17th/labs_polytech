#ifndef B3_PHONE_BOOK_HPP
#define B3_PHONE_BOOK_HPP

#include <string>
#include <list>
#include <vector>

namespace book
{

  class PhoneBook
  {
  public:

    struct phone_contact_t
    {
        std::string number;
        std::string name;
    };
    using iterator_t =  std::list<phone_contact_t>::iterator;

    PhoneBook() = default;
    PhoneBook(PhoneBook const & copyPhoneBook) = default;
    PhoneBook(PhoneBook && movePhoneBook) noexcept = default;

    ~PhoneBook() = default;

    PhoneBook & operator=(PhoneBook const & copyPhoneBook) = default;
    PhoneBook & operator=(PhoneBook && movePhoneBook) noexcept = default;

    void pushBackRecord(phone_contact_t const & contact);
    void addRecordAfter(const iterator_t iterator, phone_contact_t const & contact);
    void addRecordBefore(const iterator_t iterator, phone_contact_t const & contact);

    void deleteRecord(const iterator_t iterator);

    iterator_t getBegin();
    iterator_t getEnd();
    size_t getSize() const;

    bool isEmpty() const;

  private:
    std::list<phone_contact_t> phoneBook_;
  };

}

#endif
