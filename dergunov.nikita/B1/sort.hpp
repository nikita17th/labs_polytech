#ifndef B1_SORT_HPP
#define B1_SORT_HPP

#include <cstring>

#include "access.hpp"

extern const char * EMPTY_ORDER;

namespace details
{

  enum struct typeSorting
  {
      ASCENDING,
      DESCENDING
  };

  inline typeSorting chooseSortDirection(const char *order)
  {
    if (order == nullptr) {
      throw std::invalid_argument(EMPTY_ORDER);
    }

    if (std::strcmp(order, "ascending") == 0) {
      return details::typeSorting::ASCENDING;
    }

    if (std::strcmp(order, "descending") == 0) {
      return details::typeSorting::DESCENDING;
    }

    throw std::invalid_argument("Error, the string does not match, expected ascending or descending!");
  }

  template<typename T>
  bool compare(T const &itemNow, T const &itemNext, typeSorting order)
  {
    if ((order == typeSorting::ASCENDING) && (itemNext < itemNow)) {
      return true;
    }

    if ((order == typeSorting::DESCENDING) && (itemNow < itemNext)) {
      return true;
    }

    return false;
  }

  template<typename Access, typename Container>
  void bubbleSort(Container &container, typeSorting order)
  {
    if (container.empty()) {
      return;
    }
    using AccessType = typename Access::AccessType;
    AccessType first = Access::getBegin(container);
    AccessType second = Access::getBegin(container);
    second++;
    AccessType finish = Access::getEnd(container);

    for (AccessType iteration = first; iteration != finish; iteration++) {

      bool doesPlacements = false;
      for (AccessType nowElement = first, compareElement = second; compareElement != finish;
           compareElement++, nowElement++) {
        if (compare(Access::getElement(container, nowElement), Access::getElement(container, compareElement), order)) {
          std::swap(Access::getElement(container, nowElement), Access::getElement(container, compareElement));
          doesPlacements = true;
        }
      }
      if (!doesPlacements) {
        break;
      }
    }
  }

}

#endif
