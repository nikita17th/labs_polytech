#ifndef A4_POLYGON_HPP
#define A4_POLYGON_HPP

#include <initializer_list>
#include <iosfwd>

#include "shape.hpp"
#include "base-types.hpp"

namespace dergunov
{
  class Polygon : public Shape
  {
  public:
    Polygon(const std::initializer_list<point_t> &listPoint);
    Polygon(const Polygon &copyPolygon);
    Polygon(Polygon && movePolygon) noexcept;
    ~Polygon() = default;

    Polygon &operator =(const Polygon &polygon);
    Polygon &operator =(Polygon &&polygon) noexcept ;

    point_t getCenter() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &toPoint) override;
    void move(double dx, double  dy) override;
    void scale(double scaleFactor) override;
    void rotate(double degree) override;
    void showInformation(std::ostream &out) const override;
  private:
    size_t size_;
    point_t center_;
    point_t::ArrayPoint vertexes_;
    bool checkConvex(double product, int &route, size_t countPoints);
  };
}

#endif
