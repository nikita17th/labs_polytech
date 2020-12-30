#ifndef B1_FUNCTION_HPP
#define B1_FUNCTION_HPP

#include <vector>
#include <cstring>
#include <iostream>

namespace details
{

  using vectorInt = std::vector<int>;
  using vectorChar = std::vector<char>;
  using vectorDouble = std::vector<double>;
  using iteratorVector = std::vector<int>::iterator;

  template<typename Container>
  void showContainer(Container & container, const char * separationSymbol = " ")
  {
    for (typename Container::iterator item = container.begin(); item != container.end(); item++) {
      std::cout << *item << separationSymbol;
    }

    if (strcmp(separationSymbol, " ") == 0) {
      std::cout << "\n";
    }
  }

}

#endif
