#include "factorial.hpp"

#include <stdexcept>

const char * ITERATOR_OUT_OF_RANGE = "Iterator out of range, it must be more or equal 1 and less 11";

factorial::Container::Iterator factorial::Container::begin()
{
  return Iterator();
}

factorial::Container::Iterator factorial::Container::end()
{
  return Iterator(END_NUMBER, END_FACTORIAL);
}

factorial::Container::Iterator::Iterator(size_t currentNumber, unsigned int factorial):
  currentNumber_(currentNumber),
  factorial_(factorial)
{}


const unsigned int & factorial::Container::Iterator::operator*() const
{
  if ((currentNumber_ >= END_NUMBER) || (currentNumber_ < BEGIN_NUMBER)) {
    throw std::out_of_range(ITERATOR_OUT_OF_RANGE);
  }
  return factorial_;
}

const unsigned int * factorial::Container::Iterator::operator->() const
{
  if ((currentNumber_ >= END_NUMBER) || (currentNumber_ < BEGIN_NUMBER)) {
    throw std::out_of_range(ITERATOR_OUT_OF_RANGE);
  }
  return &factorial_;
}

factorial::Container::Iterator & factorial::Container::Iterator::operator++()
{
  if ((currentNumber_ + 1) > END_NUMBER) {
    throw std::out_of_range(ITERATOR_OUT_OF_RANGE);
  }
  factorial_ *= ++currentNumber_;
  return *this;
}

const factorial::Container::Iterator factorial::Container::Iterator::operator++(int)
{
  if ((currentNumber_ + 1) > END_NUMBER) {
    throw std::out_of_range(ITERATOR_OUT_OF_RANGE);
  }
  Container::Iterator oldIterator = *this;
  factorial_ *= ++currentNumber_;
  return oldIterator;
}

factorial::Container::Iterator & factorial::Container::Iterator::operator--()
{
  if ((currentNumber_ - 1) < BEGIN_NUMBER) {
    throw std::out_of_range(ITERATOR_OUT_OF_RANGE);
  }
  factorial_ /= currentNumber_--;
  return *this;
}

const factorial::Container::Iterator factorial::Container::Iterator::operator--(int)
{
  if ((currentNumber_ - 1) < BEGIN_NUMBER) {
    throw std::out_of_range(ITERATOR_OUT_OF_RANGE);
  }
  Container::Iterator oldIterator = *this;
  factorial_ /= currentNumber_--;
  return oldIterator;
}

bool factorial::Container::Iterator::operator == (factorial::Container::Iterator const & iterator) const
{
  return currentNumber_ == iterator.currentNumber_;
}

bool factorial::Container::Iterator::operator != (factorial::Container::Iterator const & iterator) const
{
  return currentNumber_ != iterator.currentNumber_;
}
