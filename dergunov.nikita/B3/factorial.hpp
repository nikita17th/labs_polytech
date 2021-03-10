#ifndef B3_FACTORIAL_HPP
#define B3_FACTORIAL_HPP

#include <cstddef>
#include <iterator>

class Container
{
public:
  class Iterator;
  static Iterator begin();
  static Iterator end();
private:
  static const std::size_t BEGIN_NUMBER = 1;
  static const std::size_t END_NUMBER = 11;
  static const unsigned int BEGIN_FACTORIAL = 1;
  static const unsigned int END_FACTORIAL = 39916800;
};

class Container::Iterator: public std::iterator<std::bidirectional_iterator_tag,
        unsigned int, unsigned int, const unsigned int *, unsigned int>
{
public:
  explicit Iterator(std::size_t currentNumber = BEGIN_NUMBER, unsigned int factorial = BEGIN_FACTORIAL);

  const unsigned int & operator * () const;

  Iterator & operator++();
  const Iterator operator++(int);
  Iterator & operator--();
  const Iterator operator--(int);

  bool operator == (Iterator const & iterator) const;
  bool operator != (Iterator const & iterator) const;

private:
  std::size_t currentNumber_;
  unsigned int factorial_;
};


#endif
