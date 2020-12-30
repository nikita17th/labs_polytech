#include <iostream>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

const char* MESSAGE_OK = "Success test!";
const char* ERROR_PROGRAM = "Oops, Something went wrong in the program!";

void moveShape(dergunov::Shape *shape);
void scaleShape(dergunov::Shape *shape);

int main()
{
  dergunov::Shape *pShape = nullptr;
  try
  {
    double radius = 7.4;
    dergunov::point_t startPosition = {40.3, 50.8};
    std::cout << "TEST CIRCLE\n";
    pShape = new dergunov::Circle(radius, startPosition);
    moveShape(pShape);
    scaleShape(pShape);
    delete pShape;

    double width = 4.5;
    double height =14.3;
    std::cout << "\n\nTEST RECTANGLE\n";
    pShape = new dergunov::Rectangle(width, height, startPosition);
    moveShape(pShape);
    scaleShape(pShape);
    delete pShape;
  }
  catch (std::invalid_argument& error)
  {
    delete pShape;
    std::cerr << ERROR_PROGRAM;
    return 1;
  }
  std::cout << MESSAGE_OK;
  return 0;
}

void moveShape(dergunov::Shape *shape)
{
  dergunov::point_t newPosition = {10.3, -0.8};
  double dx = 4.6;
  double dy = -5.7;
  shape->showInformation(std::cout);

  std::cout << "Area shape: " << shape->getArea() << "\n";

  shape->move(newPosition);
  shape->showInformation(std::cout);

  shape->move(dx, dy);
  shape->showInformation(std::cout);

  std::cout << "Rectangle described:\n";
  dergunov::Rectangle(shape->getFrameRect()).showInformation(std::cout);
}

void scaleShape(dergunov::Shape *shape)
{
  std::cout << "Shape before scale:\n";
  shape->showInformation(std::cout);

  double factor = 4.3;
  shape->scale(factor);

  std::cout << "Shape after scale:\n";
  shape->showInformation(std::cout);
}
