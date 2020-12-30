#include "tasks.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <unordered_map>
#include <string>
#include <stdexcept>

#include "point.hpp"
#include "base-types.hpp"
#include "shape.hpp"
#include "check-input.hpp"

namespace dergunov {
  std::unordered_map<details::error_t, std::string> exceptionMessages {
      {details::error_t::SHAPE, {}},
      {details::error_t::POINT, {}}
  };
}

void dergunov::B5::executeSecondTask(std::istream & in, std::ostream & out)
{
  VectorOfShapes shapes((std::istream_iterator<Shape>(in)), std::istream_iterator<Shape>());
  ::details::checkRunTimeErrorInInput(in);
  if (!in.eof()) {
    std::istream::iostate stateSaver(in.rdstate());
    in.clear();
    std::string nearErrorInput;
    std::getline(in, nearErrorInput);
    std::string exceptionMessage = "Error input near \'" + nearErrorInput + "\':\n" +
                                   exceptionMessages[details::error_t::SHAPE] +
                                   exceptionMessages[details::error_t::POINT];
    in.setstate(stateSaver);
    throw std::invalid_argument(exceptionMessage);
  }

  std::size_t countOfVertexes = 0;
  VectorOfIntPoints vectorOfPoints;
  CountOfFigureTypes countOfFigureTypes {
      {figure_t::TRIANGLE, 0},
      {figure_t::SQUARE, 0},
      {figure_t::RECTANGLE, 0}
  };

  auto executeStatsCount = [&countOfVertexes, &vectorOfPoints, &countOfFigureTypes](const Shape & shape)
  {
      countOfVertexes += shape.size();
      figure_t figureType = getTypeFigure(shape);
      if (figureType != figure_t::PENTAGON) {
        vectorOfPoints.push_back(shape.at(0));
      }
      countOfFigureTypes[figureType]++;
  };
  std::for_each(shapes.begin(), shapes.end(), executeStatsCount);

  auto isPentagon = [](Shape & shape) {
      return getTypeFigure(shape) == figure_t::PENTAGON;
  };
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), isPentagon), shapes.end());

  std::sort(shapes.begin(), shapes.end());

  std::ostream::sentry sentry(out);
  if (!sentry) {
    return;
  }
  out << "Vertices: " << countOfVertexes << "\n"
      << "Triangles: " << countOfFigureTypes.at(figure_t::TRIANGLE) << "\n"
      << "Squares: " << countOfFigureTypes.at(figure_t::SQUARE) << "\n"
      << "Rectangles: " << countOfFigureTypes.at(figure_t::RECTANGLE) +
                           countOfFigureTypes.at(figure_t::SQUARE) << std::endl
      << "Points: ";

  std::copy(vectorOfPoints.cbegin(), vectorOfPoints.cend(), std::ostream_iterator<PointInt>(out, "  "));

  std::cout << "\nShapes:\n";
  if (!shapes.empty()) {
    std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
  }
}
