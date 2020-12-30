#include <iostream>
#include <memory>
#include <stdexcept>

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"
#include "matrix.hpp"
#include "polygon.hpp"

void scaleShape(dergunov::Shape::ShapePtr shape);

int main()
{
  try
  {
    double radius = 7.4;
    dergunov::point_t startPosition {40.3, 50.8};
    std::cout << "TEST CIRCLE\n";
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));
    dergunov::point_t newPosition {30.3, 30.8};
    pCircle->move(newPosition);
    double dx = -10.1;
    double dy = 10.3;
    pCircle->move(dx, dy);
    scaleShape(pCircle);
    pCircle->showInformation(std::cout);

    std::cout << "\n\nTEST RECTANGLE\n";
    double width = 4.5;
    double height =14.3;
    dergunov::Shape::ShapePtr pRectangle =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(width, height, startPosition));
    newPosition = {-30.3, 30.8};
    pRectangle->move(newPosition);
    pRectangle->move(dx, dy);
    scaleShape(pRectangle);
    pRectangle->showInformation(std::cout);

    std::cout << "\n\nTEST POLYGON\n";
    dergunov::point_t firstPoint {-10.5, -10.5};
    dergunov::point_t secondPoint {-10.5, -5.5};
    dergunov::point_t thirdPoint  {-20.5, -10.5};
    dergunov::Shape::ShapePtr pPolygon =
        std::make_shared<dergunov::Polygon>(dergunov::Polygon({firstPoint, secondPoint, thirdPoint}));
    newPosition = {-5.5, -5.5};
    dx = 5.5;
    dy = 5.5;
    pPolygon->move(newPosition);
    pPolygon->move(dx, dy);
    pPolygon->rotate(90);
    pPolygon->scale(10);
    pPolygon->showInformation(std::cout);
    std::cout << "\n\nTEST COMPOSITE SHAPE\n";
    dergunov::CompositeShape compositeShape({pCircle});

    dx = 9.7;
    dy = -9.7;
    dergunov::point_t newCenter{16.4, -13.7};
    double scaleFactor = 5.5;

    compositeShape.pushBackShape(pRectangle);
    compositeShape.move(dx, dy);
    compositeShape.move(newCenter);
    compositeShape.scale(scaleFactor);
    compositeShape.rotate(90);
    compositeShape.showInformation(std::cout);

    std::cout << "\n\nTEST MATRIX\n";
    dergunov::Shape::ShapePtr pCompositeShape =
        std::make_shared<dergunov::CompositeShape>(compositeShape);

    radius = 100.7;
    dergunov::point_t circlePosition{1000.56, -2000.3};
    dergunov::Shape::ShapePtr newCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius,  circlePosition));

    width = 200.7;
    height = 440.65;
    dergunov::point_t rectPosition = {10.3, -0.8};
    dergunov::Shape::ShapePtr newRect =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(width,  height, rectPosition));
    dergunov::Matrix matrix({newCircle, newRect});
    matrix.addShape(pCompositeShape);
    matrix.addShape(pPolygon);

    size_t lines = matrix.getLines();
    size_t countShapesOfMatrix = 0;
    std::cout << "Matrix have " << lines << " layers\nScheme matrix:\n";
    for (size_t i = 0; i < lines; i++)
    {
      size_t countShapesOfLayer = matrix[i].getSize();
      countShapesOfMatrix += countShapesOfLayer;
      for (size_t j = 0; j < countShapesOfLayer; j++)
      {
        std::cout << "sh ";
      }
      std::cout << "\n";
    }
    std::cout << "Matrix have " << countShapesOfMatrix << " shapes\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << "Oops, Something went wrong in the program!";
    return 1;
  }
  std::cout << "Success test!";
  return 0;
}

void scaleShape(dergunov::Shape::ShapePtr shape)
{
  std::cout << "Shape before scale:\n";
  shape->showInformation(std::cout);

  double factor = 4.3;
  shape->scale(factor);

  std::cout << "Shape after scale:\n";
  shape->showInformation(std::cout);
}
