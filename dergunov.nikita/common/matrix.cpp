#include "matrix.hpp"

#include <cmath>
#include <stdexcept>

#include "shape.hpp"
#include "base-types.hpp"

dergunov::Matrix::Matrix():
  rows_(0),
  lines_(0),
  matrix_(nullptr)
{}

dergunov::Matrix::Matrix(const std::initializer_list<Shape::ShapePtr> &listShapes)
{
  lines_ = 0;
  rows_ = 0;
  size_t size = listShapes.size();
  if (size == 0)
  {
    matrix_ = nullptr;
    return;
  }
  unsigned int countNoShapes = 0;
  for (const Shape::ShapePtr &element: listShapes)
  {
    if (element == nullptr)
    {
      countNoShapes++;
    }
  }
  if ((size - countNoShapes) == 0)
  {
    matrix_ = nullptr;
    return;
  }
  for (const Shape::ShapePtr &element : listShapes)
  {
    if (element == nullptr)
    {
      continue;
    }
    add(element);
  }
}

dergunov::Matrix::Matrix(const dergunov::Matrix &matrix)
{
  Shape::ArrayShapePtr copyMatrix = std::make_unique<Shape::ShapePtr[]>(matrix.rows_ * matrix.lines_);
  for (size_t i = 0; i < matrix.lines_; i++)
  {
    for (size_t j = 0; j < matrix.rows_; j++)
    {
      size_t nowIndex = i * matrix.lines_ + j;
      copyMatrix[nowIndex] = matrix.matrix_[nowIndex];
    }
  }

  rows_ = matrix.rows_;
  lines_ = matrix.lines_;
  matrix_.swap(copyMatrix);
}

dergunov::Matrix::Matrix(dergunov::Matrix &&matrix) noexcept:
  rows_(matrix.rows_),
  lines_(matrix.lines_),
  matrix_(std::move(matrix.matrix_))
{
  matrix.rows_ = 0;
  matrix.lines_ = 0;
  matrix_ = nullptr;
}

dergunov::Matrix &dergunov::Matrix::operator=(const dergunov::Matrix &matrix)
{
  if (this == &matrix)
  {
    return *this;
  }

  Shape::ArrayShapePtr copyMatrix = std::make_unique<Shape::ShapePtr[]>(matrix.rows_ * matrix.lines_);
  for (size_t i = 0; i < matrix.lines_; i++)
  {
    for (size_t j = 0; j < matrix.rows_; j++)
    {
      size_t nowIndex = i * matrix.lines_ + j;
      copyMatrix[nowIndex] = matrix.matrix_[nowIndex];
    }
  }

  rows_ = matrix.rows_;
  lines_ = matrix.lines_;
  matrix_ = std::move(copyMatrix);
  return *this;
}

dergunov::Matrix &dergunov::Matrix::operator=(dergunov::Matrix &&matrix) noexcept
{
  if (this == &matrix)
  {
    return *this;
  }
  rows_ = matrix.rows_;
  lines_ = matrix.lines_;
  matrix_ = move(matrix.matrix_);

  matrix.rows_ = 0;
  matrix.lines_ = 0;
  matrix.matrix_ = nullptr;
  return *this;
}

void dergunov::Matrix::addShape(const dergunov::Shape::ShapePtr &newShape)
{
  if (newShape == nullptr)
  {
    return;
  }
  add(newShape);
}

dergunov::Matrix::Layer dergunov::Matrix::operator[](size_t index) const
{
  if (index >= lines_)
  {
    throw std::out_of_range("Index can not be more than lines and less zero");
  }
  size_t countShapes = 0;
  size_t start = rows_ * index;
  size_t finish = start + rows_;
  for (size_t i = start; i < finish; i++)
  {
    if (matrix_[i] == nullptr)
    {
      break;
    }
    countShapes++;
  }
  finish = start + countShapes;
  return Layer(*this, start, finish);
}

size_t dergunov::Matrix::getRows() const
{
  return rows_;
}

size_t dergunov::Matrix::getLines() const
{
  return lines_;
}

void dergunov::Matrix::add(const Shape::ShapePtr &newShape)
{
  if (newShape == nullptr)
  {
    return;
  }
  size_t indexLayer = findLayerInsert(newShape);
  if (indexLayer == lines_)
  {
    expandLines();
  }
  size_t indexInsert = findPlaceInLayer(indexLayer);
  if (indexInsert == (rows_ * indexLayer + rows_))
  {
    expandRows();
  }
  matrix_[indexInsert] = newShape;
}

size_t dergunov::Matrix::findLayerInsert(const Shape::ShapePtr &newShape) const
{
  size_t iInsert = 0;
  unsigned int countCross = 0;
  for (size_t i = 0; i < lines_; i++)
  {
    countCross = 0;
    for (size_t j = 0; j < rows_; j++)
    {
      size_t nowIndex = i * rows_ + j;
      if ((matrix_[nowIndex] != newShape) && (matrix_[nowIndex] != nullptr))
      {
        rectangle_t frameRectFirstShape = matrix_[nowIndex]->getFrameRect();
        rectangle_t frameRectSecondShape = newShape->getFrameRect();
        if (checkIntersection(frameRectFirstShape, frameRectSecondShape))
        {
          iInsert = i;
          countCross++;
          break;
        }
      }
    }
  }
  return (countCross > 0) ? (iInsert + 1) : iInsert;
}

size_t dergunov::Matrix::findPlaceInLayer(size_t indexLayer) const
{
  size_t nowIndex = indexLayer * rows_;
  size_t finish = nowIndex + rows_;
  while ((nowIndex < finish) && (matrix_[nowIndex] != nullptr))
  {
    nowIndex++;
  }
  return nowIndex;
}

void dergunov::Matrix::expandLines()
{
  size_t tempRows = (rows_ == 0) ? 1 : rows_;
  size_t newLines = lines_ + 1;
  Shape::ArrayShapePtr newMatrix = std::make_unique<Shape::ShapePtr[]>(tempRows * newLines);

  for (size_t i = 0; i < lines_; i++)
  {
    for (size_t j = 0; j < rows_; j++)
    {
      size_t nowIndex = i * rows_ + j;
      newMatrix[nowIndex] = matrix_[nowIndex];
    }
  }

  rows_ = tempRows;
  lines_ = newLines;
  matrix_ = std::move(newMatrix);
}

void dergunov::Matrix::expandRows()
{
  size_t tempLines = (lines_ == 0) ? 1 : lines_;
  size_t newRows = rows_ + 1;
  Shape::ArrayShapePtr newMatrix = std::make_unique<Shape::ShapePtr[]>(newRows * tempLines);

  for (size_t i = 0; i < lines_; i++)
  {
    for (size_t j = 0; j < rows_; j++)
    {
      newMatrix[i * newRows + j] = matrix_[i * rows_ + j];
    }
  }

  rows_ = newRows;
  lines_ = tempLines;
  matrix_ = std::move(newMatrix);
}

dergunov::Shape::ShapePtr dergunov::Matrix::Layer::operator[](size_t index) const
{
  size_t indexInMatrix = start_ + index;
  if ((indexInMatrix  < start_) || (indexInMatrix  >= finish_))
  {
    throw std::out_of_range("Incorrect index for layer, it must < size of layer and >= 0");
  }
  return matrixPtr_.matrix_[indexInMatrix];
}

dergunov::Matrix::Layer::Layer(const Matrix &matrix, size_t start, size_t finish):
  matrixPtr_(matrix),
  start_(start),
  finish_(finish)
{}

size_t dergunov::Matrix::Layer::getSize() const
{
  return finish_ - start_;
}
