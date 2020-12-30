#ifndef B6_SATATISTICFUNCTOR_HPP
#define B6_SATATISTICFUNCTOR_HPP

#include <cstddef>
#include <iosfwd>

namespace dergunov
{
  namespace B6
  {
    class StatisticFunctor
    {
    public:
      StatisticFunctor();
      void operator() (int value);
      friend std::ostream &operator<<(std::ostream &out, StatisticFunctor const &state);
    private:
      int max_;
      int min_;
      std::size_t countOfPositive_;
      std::size_t countOfNegative_;
      std::size_t countOfNumbers_;
      long long oddSum_;
      long long evenSum_;
      int first_;
      int last_;
    };

    std::ostream &operator<<(std::ostream &out, StatisticFunctor const &state);
  }
}


#endif
