#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP
#include <iosfwd>
#include "base-types.hpp"
#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const double radius, const point_t& center);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& toPoint) override;
  void move(const double dx, const double dy) override;
  void showInformation(std::ostream& out) const override;
private:
  double radius_;
  point_t center_;
};

#endif
