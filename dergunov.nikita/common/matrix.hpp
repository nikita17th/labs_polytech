#ifndef A4_MATRIX_HPP
#define A4_MATRIX_HPP

#include <memory>
#include <initializer_list>

#include "shape.hpp"

namespace dergunov
{
  class Matrix
  {
  public:
    class Layer;
    Matrix();
    Matrix(const std::initializer_list<Shape::ShapePtr> &listShapes);
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix) noexcept;
    ~Matrix() = default;

    Matrix &operator=(const Matrix & matrix);
    Matrix &operator=(Matrix && matrix) noexcept;
    Layer operator[](size_t index) const;

    void addShape(const Shape::ShapePtr &newShape);
    size_t getRows() const;
    size_t getLines() const;
    class Layer
    {
    public:
      Shape::ShapePtr operator[](size_t index) const;
      size_t getSize() const;
    private:
      const Matrix &matrixPtr_;
      size_t start_;
      size_t finish_;
      friend class Matrix;
      Layer(const Matrix &matrix, size_t start, size_t finish);
    };
  private:
    size_t rows_;
    size_t lines_;
    Shape::ArrayShapePtr matrix_;
    void add(const Shape::ShapePtr &newShape);
    size_t findLayerInsert(const Shape::ShapePtr &newShape) const;
    size_t findPlaceInLayer(size_t indexLayer) const;
    void expandLines();
    void expandRows();
  };
}

#endif
