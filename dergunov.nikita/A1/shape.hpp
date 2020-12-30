#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP
#include <iosfwd>

struct point_t;
struct rectangle_t;

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t& toPoint) = 0;
  virtual void move(const double dx, const double dy) = 0;
  virtual void showInformation(std::ostream& out) const = 0;
};

#endif
