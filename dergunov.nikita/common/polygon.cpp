#include "polygon.hpp"

#include <ostream>
#include <cmath>
#include <memory>

#include "base-types.hpp"


dergunov::Polygon::Polygon(const std::initializer_list<point_t> &listPoint)
{
  size_t size = listPoint.size();
  if (size < 3)
  {
    throw std::invalid_argument("It is not a polygon!");
  }
  point_t::ArrayPoint vertexes = std::make_unique<point_t[]>(size);
  size_t countPoints = 0;
  int route = 0;
  bool checkAdd = true;
  for (const point_t &element: listPoint)
  {
    if (countPoints > 1)
    {
      point_t nowVertex {element};
      point_t lastVertex {vertexes[countPoints - 1]};
      point_t prevLastVertex {vertexes[countPoints - 2]};

      point_t lastEdge {lastVertex.x - prevLastVertex.x, lastVertex.y - prevLastVertex.y};
      point_t nowEdge{nowVertex.x - lastVertex.x, nowVertex.y - lastVertex.y};

      double product = lastEdge.x * nowEdge.y - lastEdge.y * nowEdge.x;
      checkAdd = checkConvex(product, route, countPoints);
    }
    if (checkAdd)
    {
      vertexes[countPoints++] = element;
    }
  }
  if (countPoints < 3)
  {
    throw std::invalid_argument("It is not a polygon!");
  }
  size_ = countPoints;
  vertexes_ = std::make_unique<point_t[]>(size_);
  double sumX = 0;
  double  sumY = 0;
  for (size_t i = 0; i < size_; i++)
  {
    sumX += vertexes[i].x;
    sumY += vertexes[i].y;
    vertexes_[i] = vertexes[i];
  }
  center_ = {sumX / size_, sumY / size_};
}

dergunov::Polygon::Polygon(const dergunov::Polygon &copyPolygon):
  size_(copyPolygon.size_),
  center_(copyPolygon.center_)
{
  vertexes_ = std::make_unique<point_t[]>(size_);
  for (size_t i = 0; i < size_; i++)
  {
    vertexes_[i] = copyPolygon.vertexes_[i];
  }
}

dergunov::Polygon::Polygon(dergunov::Polygon &&movePolygon) noexcept:
  size_(movePolygon.size_),
  center_(movePolygon.center_),
  vertexes_(std::move(movePolygon.vertexes_))
{}

dergunov::Polygon &dergunov::Polygon::operator=(const dergunov::Polygon &polygon)
{
  if (this == &polygon)
  {
    return *this;
  }
  size_ = polygon.size_;
  center_ = polygon.center_;
  vertexes_ = std::make_unique<point_t[]>(size_);
  for (size_t i = 0; i < size_; i++)
  {
    vertexes_[i] = polygon.vertexes_[i];
  }
  return *this;
}

dergunov::Polygon &dergunov::Polygon::operator=(dergunov::Polygon &&polygon) noexcept
{
  if (this == &polygon)
  {
    return *this;
  }
  size_ = polygon.size_;
  center_ = polygon.center_;
  vertexes_ = std::move(polygon.vertexes_);
  polygon.size_ = 0;
  return *this;
}

dergunov::point_t dergunov::Polygon::getCenter() const
{
  return center_;
}

double dergunov::Polygon::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_ - 1; i++)
  {
    area += vertexes_[i].x * vertexes_[i + 1].y - vertexes_[i + 1].x * vertexes_[i].y;
  }
  area += vertexes_[size_ - 1].x * vertexes_[0].y - vertexes_[0].x * vertexes_[size_ - 1].y;
  return std::abs(area / 2);
}

dergunov::rectangle_t dergunov::Polygon::getFrameRect() const
{
  double left = vertexes_[0].x;
  double right =vertexes_[0].x;
  double top = vertexes_[0].y;
  double bottom = vertexes_[0].y;

  double nowX = 0;
  double nowY = 0;
  for (size_t i = 1; i < size_; i++)
  {
    nowX = vertexes_[i].x;
    nowY = vertexes_[i].y;

    left = std::min(left, nowX);
    right = std::max(right, nowX);
    top = std::max(top, nowY);
    bottom = std::min(bottom, nowY);
  }
  double width = right - left;
  double height = top - bottom;
  dergunov::point_t center{(right + left) / 2, (top + bottom) / 2};
  return dergunov::rectangle_t{width, height, center};
}

void dergunov::Polygon::move(const dergunov::point_t &toPoint)
{
  double dx = toPoint.x - center_.x;
  double dy = toPoint.y - center_.y;
  move(dx, dy);
}

void dergunov::Polygon::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; i++)
  {
    vertexes_[i].x += dx;
    vertexes_[i].y += dy;
  }
  center_.x += dx;
  center_.y += dy;
}

void dergunov::Polygon::scale(double scaleFactor)
{
  if (scaleFactor <= 0)
  {
    throw std::invalid_argument("Scale ratio must be positive!");
  }
  for (size_t i = 0; i < size_; i++)
  {
    double differenceCoordinateX = vertexes_[i].x - center_.x;
    double differenceCoordinateY = vertexes_[i].y - center_.y;
    double factor = scaleFactor - 1;

    double movingCoordinateX = differenceCoordinateX * factor;
    double movingCoordinateY = differenceCoordinateY * factor;

    vertexes_[i].x += movingCoordinateX;
    vertexes_[i].y += movingCoordinateY;
  }
}

void dergunov::Polygon::rotate(double degree)
{
  degree = fmod(degree, 360);
  if (degree < 0)
  {
    degree += 360;
  }
  double radians = degree * M_PI / 180;
  double sinForMove = std::sin(radians);
  double cosForMove = std::cos(radians);
  for (size_t i = 0; i < size_; i++)
  {
    double dx = vertexes_[i].x - center_.x;
    double dy = vertexes_[i].y - center_.y;
    double moveX = center_.x + dx * cosForMove - dy * sinForMove;
    double moveY = center_.y + dy * cosForMove + dx * sinForMove;

    vertexes_[i].x = moveX;
    vertexes_[i].y = moveY;
  }
}

void dergunov::Polygon::showInformation(std::ostream &out) const
{
  rectangle_t frameRect {getFrameRect()};
  out << "Information about polygon\nCoordinates of center: " << getCenter().x
      << " " << getCenter().y << "\nArea: " << getArea()
      << "\nRectangle described:\nCenter: " << frameRect.pos.x << " " << frameRect.pos.y
      << "\nWidth: " << frameRect.width << "\nHeight: " << frameRect.height << "\n";
}

bool dergunov::Polygon::checkConvex(double product, int &route, size_t countPoints)
{
  int nowRoute = 0;
  if (product == 0)
  {
    nowRoute = 0;
  }
  if (product > 0)
  {
    nowRoute = 1;
  }
  if (product < 0)
  {
    nowRoute = -1;
  }
  if (countPoints == 2)
  {
    if (nowRoute == 0)
    {
      return false;
    }
    else
    {
      route = nowRoute;
      return true;
    }
  }
  return (nowRoute == route) || (nowRoute == 0);
}
