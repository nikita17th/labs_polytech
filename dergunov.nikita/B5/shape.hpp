#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <unordered_map>
#include <string>
#include <cstddef>

#include "point.hpp"

namespace dergunov
{
  const std::string INCORRECT_SHAPE(" shape -> ");
  const std::string ERROR_NUMBER_POINTS("expected count of points more zero\n");
  const std::string INVALID_POINT("point incorrect\n");

  const std::string LESS_POINTS("vertices number less than specified number!\n");
  const std::string MORE_POINTS("vertices number more than specified number!\n");

  extern std::unordered_map<details::error_t, std::string> exceptionMessages;

  enum class figure_t
  {
    TRIANGLE,
    SQUARE,
    RECTANGLE,
    QUADRANGLE,
    PENTAGON,
    OTHER
  };

  using Shape = VectorOfIntPoints;
  using VectorOfShapes = std::vector<Shape>;
  using CountOfFigureTypes = std::unordered_map<figure_t, std::size_t>;

  bool isRectangle(Shape const &shape);
  bool isSquare(Shape const &shape);
  figure_t getTypeFigure(Shape const &shape);

  bool operator<(Shape const &left, Shape const &right);
  bool operator>(Shape const &left, Shape const &right);
  std::istream &operator>>(std::istream &in, Shape &shape);
  std::ostream &operator<<(std::ostream &out, Shape const &shape);
}

#endif
