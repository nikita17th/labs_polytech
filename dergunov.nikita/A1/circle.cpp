#include "circle.hpp"
#include <ostream>
#include <stdexcept>
#include <cmath>
#include "base-types.hpp"

const char* ERROR_RADIUS = "Invalid radius format, it less than 0";

Circle::Circle(const double radius, const point_t& center):
  radius_(radius),
  center_(center)
{
  if (radius_ < 0)
  {
    throw std::invalid_argument(ERROR_RADIUS);
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, center_};
}

void Circle::move(const point_t& toPoint)
{
  center_ = toPoint;
}

void  Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::showInformation(std::ostream& out) const
{
  out << "Information about circle:\nRadius: " << radius_
      << "\nCenter x, y: " << center_.x << " " << center_.y << "\n";
}
