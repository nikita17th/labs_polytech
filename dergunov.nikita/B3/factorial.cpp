#include "factorial.hpp"

#include <cstddef>
#include <stdexcept>

const std::out_of_range ITERATOR_OUT_OF_RANGE("Iterator out of range, it must be more or equal 1 and less 11");

Container::Iterator Container::begin()
{
  return Iterator();
}

Container::Iterator Container::end()
{
  return Iterator(END_NUMBER, END_FACTORIAL);
}

Container::Iterator::Iterator(std::size_t currentNumber, unsigned int factorial):
  currentNumber_(currentNumber),
  factorial_(factorial)
{}


const unsigned int & Container::Iterator::operator*() const
{
  if ((currentNumber_ >= END_NUMBER) || (currentNumber_ < BEGIN_NUMBER))
  {
    throw std::out_of_range(ITERATOR_OUT_OF_RANGE);
  }
  return factorial_;
}

Container::Iterator & Container::Iterator::operator++()
{
  if ((currentNumber_ + 1) > END_NUMBER)
  {
    throw ITERATOR_OUT_OF_RANGE;
  }
  factorial_ *= ++currentNumber_;
  return *this;
}

const Container::Iterator Container::Iterator::operator++(int)
{
  if ((currentNumber_ + 1) > END_NUMBER)
  {
    throw ITERATOR_OUT_OF_RANGE;
  }
  Container::Iterator oldIterator = *this;
  ++*this;
  return oldIterator;
}

Container::Iterator & Container::Iterator::operator--()
{
  if ((currentNumber_ - 1) < BEGIN_NUMBER)
  {
    throw std::out_of_range(ITERATOR_OUT_OF_RANGE);
  }
  factorial_ /= currentNumber_--;
  return *this;
}

const Container::Iterator Container::Iterator::operator--(int)
{
  if ((currentNumber_ - 1) < BEGIN_NUMBER)
  {
    throw ITERATOR_OUT_OF_RANGE;
  }
  Container::Iterator oldIterator = *this;
  --*this;
  return oldIterator;
}

bool Container::Iterator::operator == (Container::Iterator const & iterator) const
{
  return currentNumber_ == iterator.currentNumber_;
}

bool Container::Iterator::operator != (Container::Iterator const & iterator) const
{
  return !(*this == iterator);
}
