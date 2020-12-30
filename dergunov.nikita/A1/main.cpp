#include <iostream>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

const char* MESSAGE_OK = "Success test!";
const char* ERROR_PROGRAM = "Oops, Something went wrong in the program!";

void checkCircle();
void checkRectangle();

int main()
{
  try
  {
    std::cout << "TEST CIRCLE\n";
    checkCircle();

    std::cout << "\n\nTEST RECTANGLE\n";
    checkRectangle();
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << ERROR_PROGRAM;
    return 1;
  }
  std::cout << MESSAGE_OK;
  return 0;
}

void checkCircle()
{
  Shape *pCircle = new Circle(7.5, {40.3, 50.8});
  pCircle->showInformation(std::cout);

  std::cout << "Area circle: " << pCircle->getArea() << "\n";

  pCircle->move({6.7, -10.7});
  pCircle->showInformation(std::cout);

  pCircle->move(-10.7, 200.56);
  pCircle->showInformation(std::cout);

  std::cout << "Rectangle described:\n";
  Rectangle(pCircle->getFrameRect()).showInformation(std::cout);

  delete pCircle;
}

void checkRectangle()
{
  Shape *pRectangle = new Rectangle(4.5, 9.1, {5.6, 5.3});
  pRectangle->showInformation(std::cout);

  std::cout << "Area rectangle: " << pRectangle->getArea() << "\n";

  pRectangle->move({-4.4, 10.3});
  pRectangle->showInformation(std::cout);

  pRectangle->move(5.7, -100.3);
  pRectangle->showInformation(std::cout);

  std::cout << "Rectangle described:\n";
  Rectangle(pRectangle->getFrameRect()).showInformation(std::cout);

  delete pRectangle;
}
