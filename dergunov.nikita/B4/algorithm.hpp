#ifndef B4_ALGORITHM_HPP
#define B4_ALGORITHM_HPP

#include <iostream>
#include <vector>

namespace dergunov
{
  namespace B4
  {
    void executeAlgorithmOne(std::istream &in = std::cin, std::ostream &out = std::cout);

    struct DataStruct;
    using DataStructVector = std::vector<DataStruct>;

    namespace console
    {
      void executeInput(dergunov::B4::DataStructVector &dataStructVector, std::istream &in = std::cin,
          std::ostream &out = std::cout);
      void executeOutput(dergunov::B4::DataStructVector const &dataStructVector, std::istream &in = std::cin,
          std::ostream &out = std::cout);
    }
  }
}
#endif
