#include <iostream>
#include <memory>
#include <stdexcept>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

void moveShape(dergunov::Shape::ShapePtr shape);
void scaleShape(dergunov::Shape::ShapePtr shape);
void showInformationShape(dergunov::Shape::ShapePtr shape);

int main()
{
  try
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    std::cout << "TEST CIRCLE\n";
    dergunov::Shape::ShapePtr pCircle =
        std::make_shared<dergunov::Circle>(dergunov::Circle(radius, startPosition));
    moveShape(pCircle);
    scaleShape(pCircle);

    double width = 4.5;
    double height =14.3;
    std::cout << "\n\nTEST RECTANGLE\n";
    dergunov::Shape::ShapePtr pRectangle =
        std::make_shared<dergunov::Rectangle>(dergunov::Rectangle(width, height, startPosition));
    moveShape(pRectangle);
    scaleShape(pRectangle);

    std::cout << "\n\nTEST COMPOSITE SHAPE\n";
    dergunov::CompositeShape compositeShape({pCircle});

    double dx = 9.7;
    double dy = -9.7;
    dergunov::point_t newCenter{16.4, -13.7};
    double scaleFactor = 0;

    compositeShape.pushBackShape(pRectangle);
    compositeShape.move(dx, dy);
    compositeShape.move(newCenter);
    compositeShape.scale(scaleFactor);
    compositeShape.showInformation(std::cout);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << "Oops, Something went wrong in the program!";
    return 1;
  }
  std::cout << "Success test!";
  return 0;
}

void moveShape(dergunov::Shape::ShapePtr shape)
{
  dergunov::point_t newPosition = {10.3, -0.8};
  double dx = 4.6;
  double dy = -5.7;
  shape->showInformation(std::cout);

  shape->move(newPosition);
  shape->showInformation(std::cout);

  shape->move(dx, dy);
  shape->showInformation(std::cout);

  showInformationShape(shape);
}

void scaleShape(dergunov::Shape::ShapePtr shape)
{
  std::cout << "Shape before scale:\n";
  showInformationShape(shape);

  double factor = 4.3;
  shape->scale(factor);

  std::cout << "Shape after scale:\n";
  showInformationShape(shape);
}

void showInformationShape(dergunov::Shape::ShapePtr shape)
{
  std::cout << "Area shape: " << shape->getArea() << "\n";
  std::cout << "Rectangle described:\n";
  dergunov::Rectangle(shape->getFrameRect()).showInformation(std::cout);
}
