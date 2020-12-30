#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include <initializer_list>
#include <iosfwd>

#include "shape.hpp"
#include "base-types.hpp"

namespace dergunov
{
  class CompositeShape: public Shape {
  public:
    CompositeShape(const std::initializer_list<ShapePtr> &listShapes);
    CompositeShape(const CompositeShape &compositeShape);
    CompositeShape(CompositeShape &&compositeShape) noexcept;
    ~CompositeShape() override;

    CompositeShape &operator =(const CompositeShape &compositeShape);
    CompositeShape &operator =(CompositeShape &&compositeShape) noexcept;
    ShapePtr operator[](size_t index) const;

    void pushBackShape(const ShapePtr &addShape);
    void deleteShape(size_t index);
    size_t getCountOfShapes() const;
    size_t getSize() const;
    point_t getCenter() const override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &toPoint) override;
    void move(double dx, double dy) override;
    void scale(double scaleFactor) override;
    void rotate(double degree) override;
    void showInformation(std::ostream &out) const override;
  private:
    size_t countOfShapes_;
    size_t capacity_;
    const int MAGNIFICATION_RATIO = 2;
    size_t START_CAPACITY = 8;
    std::allocator<ShapePtr> allocator_;
    ShapePtr *buffer_;
    void expand();
    void squeeze();
  };
}

#endif
