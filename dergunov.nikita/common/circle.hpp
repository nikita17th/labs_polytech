#ifndef A2_CIRCLE_HPP
#define A2_CIRCLE_HPP

#include <iosfwd>

#include "base-types.hpp"
#include "shape.hpp"

namespace dergunov
{
  class Circle: public Shape {
  public:
    Circle(double radius, const point_t &center);
    double getRadius() const;
    point_t getCenter() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &toPoint) override;
    void move(double dx, double dy) override;
    void scale(double scaleFactor) override;
    void rotate(double degree) override;
    void showInformation(std::ostream &out) const override;
  private:
    double radius_;
    point_t center_;
  };

}

#endif
