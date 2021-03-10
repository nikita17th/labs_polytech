#include "mark-book.hpp"

#include <iostream>
#include <algorithm>

#include "exceptions-commands.hpp"

MarkBook::MarkBook(const std::shared_ptr<PhoneBook>& phoneBook):
  phoneBook_(phoneBook)
{
  markBook_["current"] = phoneBook->getBegin();
}

void MarkBook::add(const PhoneBook::phone_contact_t &contact)
{
  phoneBook_->pushBackRecord(contact);
  if (phoneBook_->getSize() == 1)
  {
    std::for_each(markBook_.begin(), markBook_.end(), [&](auto& it)
    {
      it.second = phoneBook_->getBegin();
    });
  }
}

void MarkBook::store(const std::string &markName, const std::string &newMarkName)
{
  MarkBook::iterator it = find(markName);
  markBook_[newMarkName] = it->second;
}

void MarkBook::insertAfter(const std::string &markName, const PhoneBook::phone_contact_t &contact)
{
  if (phoneBook_->isEmpty())
  {
    add(contact);
    return;
  }
  MarkBook::iterator it = find(markName);
  phoneBook_->addRecordAfter(it->second, contact);
}

void MarkBook::insertBefore(const std::string &markName, const PhoneBook::phone_contact_t &contact)
{
  if (phoneBook_->isEmpty())
  {
    add(contact);
    return;
  }
  MarkBook::iterator it = find(markName);
  phoneBook_->addRecordBefore(it->second, contact);
}

void MarkBook::deleteBookmarkNote(const std::string &markName)
{
  if (phoneBook_->getSize() == 0)
  {
    throw Empty();
  }

  MarkBook::iterator it = find(markName);
  if (it->second != phoneBook_->getEnd())
  {
    PhoneBook::iterator_t deleteIt = it->second;
    for (auto& mark : markBook_)
    {
      if (mark.second == deleteIt)
      {
        if (std::next(mark.second) != phoneBook_->getEnd())
        {
          mark.second = std::next(deleteIt);
        }
        else
        {
          mark.second = std::prev(deleteIt);
        }
      }
    }
    phoneBook_->deleteRecord(deleteIt);
  }
}

void MarkBook::show(const std::string &markName, std::ostream & os)
{
  MarkBook::iterator it = find(markName);
  if (phoneBook_->getSize() == 0)
  {
    throw Empty();
  }

  os << it->second->number << " " << it->second->name << "\n";
}

void MarkBook::move(const std::string &markName, int step)
{
  MarkBook::iterator it = find(markName);

  if (((step < 0) && std::distance(phoneBook_->getBegin(), it->second) < (-1 * step)) ||
      ((step > 0) && std::distance(it->second, phoneBook_->getEnd()) < step))
  {
    throw std::out_of_range("Out of the phoneBook, when move!");
  }
  std::advance(it->second, step);
}

void MarkBook::move(const std::string &markName, MarkBook::MovePosition pos)
{
  MarkBook::iterator it = find(markName);

  if (pos == MovePosition::FIRST)
  {
    it->second = phoneBook_->getBegin();
  }
  else
  {
    it->second = --phoneBook_->getEnd();
  }
}

MarkBook::iterator MarkBook::find(const std::string &markName)
{
  MarkBook::iterator it = markBook_.find(markName);
  if (it == markBook_.end())
  {
    throw InvalidBookmark();
  }
  return it;
}
