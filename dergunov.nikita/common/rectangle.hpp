#ifndef A2_RECTANGLE_HPP
#define A2_RECTANGLE_HPP

#include <iosfwd>

#include "base-types.hpp"
#include "shape.hpp"

namespace dergunov
{
  class Rectangle: public Shape {
  public:
    Rectangle(double width, double height, const point_t &pos, double angle = 0);
    Rectangle(const rectangle_t &rectangle, double angle = 0);
    double getHeight() const;
    double getWidth() const;
    point_t getCenter() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &toPoint) override;
    void move(double dx, double dy) override;
    void scale(double scaleFactor) override;
    void rotate(double degree) override;
    void showInformation(std::ostream &out) const override;
  private:
    double height_;
    double width_;
    point_t center_;
    point_t leftBottomConner_;
    point_t leftTopConner_;
    point_t rightTopConner_;
    point_t rightBottomConner_;
  };
}

#endif
