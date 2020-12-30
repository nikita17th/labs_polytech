#include "shape.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <cstddef>
#include <boost/io/ios_state.hpp>
#include <unordered_map>

extern std::unordered_map<error_t, std::string> exceptionMessages;

static std::size_t countShapes = 0;

bool dergunov::isRectangle(Shape const & shape)
{
  size_t countOfVertex = shape.size();
  if (shape.size() != 4) {
    return false;
  }
  std::vector<unsigned int> squareEdges;
  for (std::size_t i = 1; i < countOfVertex; i++) {
    squareEdges.push_back(shape.at(i - 1).getDistanceSquare(shape.at(i)));
  }

  squareEdges.push_back(shape.at(3).getDistanceSquare(shape.at(0)));

  unsigned int diagonalSquareFromFirstToThirdVertex = shape.at(0).getDistanceSquare(shape.at(2));
  unsigned int diagonalSquareFromSecondToFourthVertex = shape.at(1).getDistanceSquare(shape.at(3));

  return (diagonalSquareFromFirstToThirdVertex == diagonalSquareFromSecondToFourthVertex) &&
      (squareEdges.at(0) == squareEdges.at(2)) && (squareEdges.at(1) == squareEdges.at(3));
}

bool dergunov::isSquare(Shape const & shape)
{
  if (!isRectangle(shape)){
    return false;
  }

  unsigned int topEdge = shape.at(0).getDistanceSquare(shape.at(1));
  unsigned int leftEdge = shape.at(0).getDistanceSquare(shape.at(3));

  return topEdge == leftEdge;
}

dergunov::figure_t dergunov::getTypeFigure(Shape const & shape)
{
  switch (shape.size()) {
    case 3:
      return figure_t::TRIANGLE;
    case 4:
      if (isSquare(shape)) {
        return figure_t::SQUARE;
      }
      if (isRectangle(shape)) {
        return figure_t::RECTANGLE;
      }
      return figure_t::QUADRANGLE;
    case 5:
      return figure_t::PENTAGON;
    default:
      return figure_t::OTHER;
  }
}

bool dergunov::operator<(const Shape &left, const Shape &right)
{
  return getTypeFigure(left) < getTypeFigure(right);
}

bool dergunov::operator>(const Shape &left, const Shape &right)
{
  return right < left;
}

std::istream &dergunov::operator>>(std::istream &in, Shape &shape)
{
  boost::io::ios_flags_saver ifs(in);
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  std::noskipws(in);
  int inputCountOfVertex = 0;
  in >> inputCountOfVertex ;
  if (inputCountOfVertex  <= 0) {
    in.setstate(std::istream::failbit);
    exceptionMessages[details::error_t::SHAPE] = INCORRECT_SHAPE + ERROR_NUMBER_POINTS;
    return in;
  }

  size_t countOfVertex = static_cast<std::size_t>(inputCountOfVertex);

  VectorOfIntPoints pointVector;
  for (size_t i = 0; i < countOfVertex; i++) {
    if ((in >> details::skipBlanks).eof() || in.peek() == '\n') {
      in.setstate(std::istream::failbit);
      exceptionMessages[details::error_t::SHAPE] = "index " + std::to_string(countShapes) + INCORRECT_SHAPE + LESS_POINTS;
      return in;
    }

    PointInt pointInt;
    if (!(in >> pointInt)) {
      exceptionMessages[details::error_t::SHAPE] = "index " + std::to_string(countShapes) + INCORRECT_SHAPE +
          INVALID_POINT + "index " + std::to_string(i);
      return in;
    }
    pointVector.push_back(pointInt);
  }

  if (!(in >> details::skipBlanks).eof() && in.peek() != '\n') {
    in.setstate(std::istream::failbit);
    exceptionMessages[details::error_t::SHAPE] = "index " + std::to_string(countShapes) + INCORRECT_SHAPE + MORE_POINTS;
    return in;
  }

  countShapes++;
  shape = std::move(pointVector);

  return in;
}

std::ostream &dergunov::operator<<(std::ostream &out, const Shape &shape)
{
  std::ostream::sentry sentry(out);
  if (sentry) {
    out << shape.size() << "  ";
    std::copy(shape.cbegin(), shape.cend(), std::ostream_iterator<PointInt>(out, " "));
  }
  return out;
}
