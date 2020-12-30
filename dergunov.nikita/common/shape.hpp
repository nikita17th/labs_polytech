#ifndef A2_SHAPE_HPP
#define A2_SHAPE_HPP

#include <iosfwd>
#include <memory>

namespace dergunov
{
  struct point_t;
  struct rectangle_t;

  class Shape {
  public:
    using ShapePtr = std::shared_ptr<dergunov::Shape>;
    using ArrayShapePtr = std::unique_ptr<dergunov::Shape::ShapePtr[]>;
    virtual ~Shape() = default;
    virtual point_t getCenter() const = 0;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &toPoint) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double scaleFactor) = 0;
    virtual void rotate(double degree) = 0;
    virtual void showInformation(std::ostream &out) const = 0;
  };
}

#endif
