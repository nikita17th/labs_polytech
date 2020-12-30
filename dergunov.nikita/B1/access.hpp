#ifndef B1_ACCESS_HPP
#define B1_ACCESS_HPP

#include <cstddef>
#include <iterator>

namespace details
{

  template <typename Container>
  class AccessByBrackets
  {
  public:
    using returnTypeReference = typename Container::reference;
    using AccessType = typename Container::size_type;

    static AccessType getBegin(Container const &)
    {
      return 0;
    }

    static AccessType getEnd(Container const & container)
    {
      return container.size();
    }

    static returnTypeReference getElement(Container & container, AccessType index)
    {
      return container[index];
    }

  };

  template <typename Container>
  class AccessByAt
  {
  public:
    using returnTypeReference = typename Container::reference;
    using AccessType = typename Container::size_type;

    static AccessType getBegin(Container const &)
    {
      return 0;
    }

    static AccessType getEnd(Container const & container)
    {
      return container.size();
    }

    static returnTypeReference getElement(Container & container, AccessType index)
    {
      return container.at(index);
    }

  };

  template <typename Container>
  class AccessByListIterator
  {
  public:
    using returnTypeReference = typename Container::reference;
    using AccessType = typename Container::iterator;

    static AccessType getBegin(Container & container)
    {
      return container.begin();
    }

    static AccessType getEnd(Container & container)
    {
      return container.end();
    }

    static returnTypeReference getElement(Container &, AccessType iterator)
    {
      return *iterator;
    }
  };

}

#endif
