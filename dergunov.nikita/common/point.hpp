#ifndef B5_POINT_HPP
#define B5_POINT_HPP

#include <iostream>
#include <vector>
#include <boost/io/ios_state.hpp>
#include <unordered_map>

#include "base-types.hpp"

namespace dergunov
{
  const std::string INCORRECT_POINT(" point -> ");
  const std::string ERROR_OPEN_BRACKET("expected (\n");
  const std::string ERROR_X_COORDINATE("expected X coordinate\n");
  const std::string ERROR_SEMICOLON("expected ;\n");
  const std::string ERROR_Y_COORDINATE("expected Y coordinate\n");
  const std::string ERROR_CLOSE_BRACKET("expected )\n");

  extern std::unordered_map<details::error_t, std::string> exceptionMessages;

  template<typename T>
  class Point
  {
  public:
    T getDistanceSquare(Point const &point) const;
    template<typename T1>
    friend std::istream &operator>>(std::istream &in, Point<T1> &point);
    template<typename T1>
    friend std::ostream &operator<<(std::ostream &out, Point<T1> const &point);
  private:
    T x;
    T y;
    static const char OPEN_BRACKET = '(';
    static const char SEMICOLON = ';';
    static const char CLOSE_BRACKET = ')';
  };

  using PointInt = Point<int>;
  using VectorOfIntPoints = std::vector<PointInt>;

  template<typename T>
  T Point<T>::getDistanceSquare(Point const &point) const
  {
    int dx = x - point.x;
    int dy = y - point.y;
    return (dx * dx) + (dy * dy);
  }

  template<typename T>
  std::istream &operator>>(std::istream &in, Point<T> &point)
  {
    boost::io::ios_flags_saver ifs(in);
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }

    std::noskipws(in);
    int x = 0, y = 0;

    if (!details::skipSymbol(Point<T>::OPEN_BRACKET, in >> details::skipBlanks)) {
      exceptionMessages[details::error_t::POINT] = INCORRECT_POINT + ERROR_OPEN_BRACKET;
      return in;
    }

    if (!(in >> details::skipBlanks >> x)) {
      exceptionMessages[details::error_t::POINT] = INCORRECT_POINT + ERROR_X_COORDINATE;
      return in;
    }
    if (!details::skipSymbol(Point<T>::SEMICOLON, in >> details::skipBlanks)) {
      exceptionMessages[details::error_t::POINT] = INCORRECT_POINT + ERROR_SEMICOLON;
      return in;
    }
    if (!(in >> details::skipBlanks >> y)) {
      exceptionMessages[details::error_t::POINT] = INCORRECT_POINT + ERROR_Y_COORDINATE;
      return in;
    }
    if (!details::skipSymbol(Point<T>::CLOSE_BRACKET, in >> details::skipBlanks)) {
      exceptionMessages[details::error_t::POINT] = INCORRECT_POINT + ERROR_CLOSE_BRACKET;
      return in;
    }

    point.x = x;
    point.y = y;

    return in;
  }

  template<typename T>
  std::ostream &operator<<(std::ostream &out, const Point<T> &point)
  {
    std::ostream::sentry sentry(out);
    if (sentry) {
      out << Point<T>::OPEN_BRACKET << point.x << Point<T>::SEMICOLON << point.y << Point<T>::CLOSE_BRACKET;
    }
    return out;
  }
}

#endif
