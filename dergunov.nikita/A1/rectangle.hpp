#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP
#include <iosfwd>
#include "base-types.hpp"
#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const double width, const double height, const point_t& pos);
  Rectangle(const rectangle_t& rectangle);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& toPoint) override;
  void move(const double dx, const double dy) override;
  void showInformation(std::ostream& out) const override;
private:
  rectangle_t rectangle_;
};

#endif
