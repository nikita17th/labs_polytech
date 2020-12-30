#include "rectangle.hpp"

#include <ostream>
#include <cmath>
#include <stdexcept>

#include "base-types.hpp"

dergunov::Rectangle::Rectangle(double width, double height, const point_t &pos, double angle):
  Rectangle(rectangle_t{width, height, pos}, angle)
{
  if (width < 0)
  {
    throw std::invalid_argument("Invalid Width Format, it less than 0");
  }
  if (height < 0)
  {
    throw std::invalid_argument("Invalid Height Format, it less than 0");
  }
}

dergunov::Rectangle::Rectangle(const rectangle_t &rectangle, double angle):
  height_(rectangle.height),
  width_(rectangle.width),
  center_(rectangle.pos)
{
  if (rectangle.width < 0)
  {
    throw std::invalid_argument("Invalid Width Format, it less than 0");
  }
  if (rectangle.height < 0)
  {
    throw std::invalid_argument("Invalid Height Format, it less than 0");
  }
  double dx = rectangle.width / 2;
  double dy = rectangle.height / 2;
  double leftX = center_.x - dx;
  double rightX = center_.x + dx;
  double topY = center_.y + dy;
  double bottomY = center_.y - dy;

  leftBottomConner_ = {leftX, bottomY};
  leftTopConner_ = {leftX, topY};
  rightTopConner_ = {rightX, topY};
  rightBottomConner_ = {rightX, bottomY};

  angle = fmod(angle, 360);
  if (angle < 0)
  {
    angle += 360;
  }
  rotate(angle);
}

double dergunov::Rectangle::getHeight() const
{
  return height_;
}

double dergunov::Rectangle::getWidth() const
{
  return width_;
}

dergunov::point_t dergunov::Rectangle::getCenter() const
{
  return center_;
}

double dergunov::Rectangle::getArea() const
{
  return width_ * height_;
}

dergunov::rectangle_t dergunov::Rectangle::getFrameRect() const
{
  double right = std::max(leftTopConner_.x, leftBottomConner_.x);
  right = std::max(right, rightBottomConner_.x);
  right = std::max(right, rightTopConner_.x);
  double top = std::max(leftTopConner_.y, leftBottomConner_.y);
  top = std::max(top, rightBottomConner_.y);
  top = std::max(top, rightTopConner_.y);
  double left = std::min(leftTopConner_.x, leftBottomConner_.x);
  left = std::min(left, rightBottomConner_.x);
  left = std::min(left, rightTopConner_.x);
  double bottom = std::min(leftTopConner_.y, leftBottomConner_.y);
  bottom = std::min(bottom, rightBottomConner_.y);
  bottom = std::min(bottom, rightTopConner_.y);

  double width = right - left;
  double height = top - bottom;
  point_t center{(right + left) / 2, (top + bottom) / 2};

  return rectangle_t{width, height, center};
}

void dergunov::Rectangle::move(const point_t& toPoint)
{
  move(toPoint.x - center_.x, toPoint.y - center_.y);
}

void dergunov::Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;

  rightBottomConner_.x += dx;
  rightBottomConner_.y += dy;

  rightTopConner_.x += dx;
  rightTopConner_.y += dy;

  leftTopConner_.x += dx;
  leftTopConner_.y += dy;

  leftBottomConner_.x += dx;
  leftBottomConner_.y += dy;
}

void dergunov::Rectangle::scale(double scaleFactor)
{
  if (scaleFactor < 0)
  {
    throw std::invalid_argument("Invalid scale factor, it less than 0");
  }
  height_ *= scaleFactor;
  width_ *= scaleFactor;

  double factor = scaleFactor - 1;

  double differenceCoordinateX = leftBottomConner_.x - center_.x;
  double differenceCoordinateY = leftBottomConner_.y - center_.y;
  double movingCoordinateX = differenceCoordinateX * factor;
  double movingCoordinateY = differenceCoordinateY * factor;
  leftBottomConner_ = {leftBottomConner_.x + movingCoordinateX, leftBottomConner_.y + movingCoordinateY};

  differenceCoordinateX = leftTopConner_.x - center_.x;
  differenceCoordinateY = leftTopConner_.y - center_.y;
  movingCoordinateX = differenceCoordinateX * factor;
  movingCoordinateY = differenceCoordinateY * factor;
  leftTopConner_ = {leftTopConner_.x + movingCoordinateX, leftTopConner_.y + movingCoordinateY};

  differenceCoordinateX = rightTopConner_.x - center_.x;
  differenceCoordinateY = rightTopConner_.y - center_.y;
  movingCoordinateX = differenceCoordinateX * factor;
  movingCoordinateY = differenceCoordinateY * factor;
  rightTopConner_ = {rightTopConner_.x + movingCoordinateX, rightTopConner_.y + movingCoordinateY};

  differenceCoordinateX = rightBottomConner_.x - center_.x;
  differenceCoordinateY = rightBottomConner_.y - center_.y;
  movingCoordinateX = differenceCoordinateX * factor;
  movingCoordinateY = differenceCoordinateY * factor;
  rightBottomConner_ = {rightBottomConner_.x + movingCoordinateX, rightBottomConner_.y + movingCoordinateY};
}

void dergunov::Rectangle::rotate(double degree)
{
  degree = fmod(degree, 360);
  if (degree < 0)
  {
    degree += 360;
  }

  double radians = degree * M_PI / 180;
  double sin = std::sin(radians);
  double cos = std::cos(radians);

  double nowDX = width_ / 2;
  double nowDY = height_ / 2;

  leftTopConner_ = {center_.x - nowDX * cos - nowDY * sin, center_.y + nowDY * cos - nowDX * sin};
  rightTopConner_ = {center_.x + nowDX * cos- nowDY * sin, center_.y + nowDY * cos + nowDX * sin};
  leftBottomConner_ = {center_.x + nowDX * cos + nowDY * sin, center_.y - nowDY * cos + nowDX * sin};
  rightBottomConner_ = {center_.x - nowDX * cos + nowDY * sin, center_.y - nowDY * cos - nowDX * sin};
}

void dergunov::Rectangle::showInformation(std::ostream& out) const
{
  rectangle_t frameRect {getFrameRect()};
  out << "Information about rectangle:\nWidth: " << getWidth()
      << "\nHeight: " << getHeight() << "\nCenter x, y: " << getCenter().x
      << " " << getCenter().y << "\nArea: " << getArea()
      << "\nRectangle described:\nCenter: " << frameRect.pos.x << " " << frameRect.pos.y
      << "\nWidth: " << frameRect.width << "\nHeight: " << frameRect.height << "\n";
}
