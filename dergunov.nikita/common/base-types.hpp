#ifndef A2_BASE_TYPES_HPP
#define A2_BASE_TYPES_HPP

#include <cmath>
#include <memory>
#include <iostream>
#include <cctype>

namespace dergunov
{
  struct point_t {
      using ArrayPoint = std::unique_ptr<dergunov::point_t[]>;
      double x;
      double y;
  };

  struct rectangle_t {
      double width;
      double height;
      point_t pos;
  };

  bool checkIntersection(const rectangle_t &frameRectFirstShape, const rectangle_t &frameRectSecondShape);

  namespace details
  {
    template< class CharT, class Traits >
    std::basic_istream<CharT,Traits>& skipBlanks(std::basic_istream<CharT, Traits>& in) {
      std::istream::sentry sentry(in);
      if (sentry) {
        while (std::isblank(in.peek()) && in.get());
      }
      return in;
    }

    bool skipSymbol(char symbol, std::istream &in = std::cin, std::ostream &out = std::cout);

    enum struct error_t {
        SHAPE,
        POINT
    };
  }
}

#endif
