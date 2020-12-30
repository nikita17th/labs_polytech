#include "circle.hpp"

#include <ostream>
#include <stdexcept>
#include <cmath>

#include "base-types.hpp"

dergunov::Circle::Circle(double radius, const point_t& center):
  radius_(radius),
  center_(center)
{
  if (radius_ < 0)
  {
    throw std::invalid_argument("Invalid radius format, it less than 0");
  }
}

double dergunov::Circle::getRadius() const
{
  return radius_;
}

dergunov::point_t dergunov::Circle::getCenter() const
{
  return center_;
}

double dergunov::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

dergunov::rectangle_t dergunov::Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, center_};
}

void dergunov::Circle::move(const point_t& toPoint)
{
  center_ = toPoint;
}

void dergunov::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void dergunov::Circle::scale(double scaleFactor)
{
  if (scaleFactor < 0)
  {
    throw std::invalid_argument("Invalid scale factor, it less than 0");
  }
  radius_ *= scaleFactor;
}

void dergunov::Circle::rotate(double)
{}

void dergunov::Circle::showInformation(std::ostream& out) const
{
  rectangle_t frameRect {getFrameRect()};
  out << "Information about circle:\nRadius: " << radius_
      << "\nCenter x, y: " << getCenter().x << " " << getCenter().y
      << "\nArea: " << getArea() << "\nRectangle described:\nCenter: "
      << frameRect.pos.x << " " << frameRect.pos.y << "\nWidth: " << frameRect.width
      << "\nHeight: " << frameRect.height << "\n";
}
