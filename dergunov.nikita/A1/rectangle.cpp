#include "rectangle.hpp"
#include <ostream>
#include <stdexcept>
#include "base-types.hpp"

const char* ERROR_WIDTH = "Invalid Width Format, it less than 0";
const char* ERROR_HEIGHT = "Invalid Height Format, it less than 0";

Rectangle::Rectangle(const double width, const double height, const point_t& pos):
  rectangle_{width, height, pos}
{
  if (width < 0)
  {
    throw std::invalid_argument(ERROR_WIDTH);
  }
  if (height < 0)
  {
    throw std::invalid_argument(ERROR_HEIGHT);
  }
}

Rectangle::Rectangle(const rectangle_t& rectangle):
  rectangle_{rectangle}
{
  if (rectangle.width < 0)
  {
    throw std::invalid_argument(ERROR_WIDTH);
  }
  if (rectangle.height < 0)
  {
    throw std::invalid_argument(ERROR_HEIGHT);
  }
}

double Rectangle::getArea() const
{
  return rectangle_.width * rectangle_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}

void Rectangle::move(const point_t& toPoint)
{
  rectangle_.pos = toPoint;
}

void Rectangle::move(const double dx, const double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

void Rectangle::showInformation(std::ostream& out) const
{
  out << "Information about rectangle:\nWidth: " << rectangle_.width
      << "\nHeight: " << rectangle_.height << "\nCenter x, y: " << rectangle_.pos.x
      << " " << rectangle_.pos.y << "\n";
}
