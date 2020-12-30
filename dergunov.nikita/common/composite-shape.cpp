#include "composite-shape.hpp"

#include <ostream>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <initializer_list>

#include "shape.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

dergunov::CompositeShape::CompositeShape(const std::initializer_list<ShapePtr> &listShapes)
{
  if (listShapes.size() == 0)
  {
    throw std::invalid_argument("Composite shape must have figure!");
  }
  for (const ShapePtr &element: listShapes)
  {
    if (element == nullptr)
    {
      throw std::invalid_argument("Pointer must indicate on object!");
    }
  }

  size_t size = listShapes.size() * MAGNIFICATION_RATIO;
  ShapePtr *newBuffer = allocator_.allocate(size);

  size_t i = 0;
  for (const ShapePtr &element : listShapes)
  {
    allocator_.construct(&newBuffer[i++], element);
  }

  countOfShapes_ = listShapes.size();
  capacity_ = size;
  buffer_ = std::move(newBuffer);
}

dergunov::CompositeShape::CompositeShape(const CompositeShape &compositeShape)
{
  ShapePtr *newBuffer = allocator_.allocate(compositeShape.capacity_);

  for (size_t i = 0; i < compositeShape.countOfShapes_; i++)
  {
    allocator_.construct(&newBuffer[i], compositeShape[i]);
  }

  capacity_ = compositeShape.capacity_;
  countOfShapes_ = compositeShape.countOfShapes_;
  buffer_ = std::move(newBuffer);
}

dergunov::CompositeShape::CompositeShape(CompositeShape &&compositeShape) noexcept:
  countOfShapes_(compositeShape.countOfShapes_),
  capacity_(compositeShape.capacity_),
  buffer_(std::move(compositeShape.buffer_))
{
  compositeShape.countOfShapes_ = 0;
  compositeShape.capacity_ = 0;
  compositeShape.buffer_ = nullptr;
}

dergunov::CompositeShape::~CompositeShape()
{
  for (size_t i = 0; i < countOfShapes_; i++)
  {
    allocator_.destroy(&buffer_[i]);
  }
  allocator_.deallocate(buffer_, capacity_);
}

dergunov::CompositeShape &dergunov::CompositeShape::operator =(const CompositeShape &compositeShape)
{
  if (&compositeShape == this)
  {
    return *this;
  }

  ShapePtr* newBuffer = allocator_.allocate(compositeShape.capacity_);
  for (size_t i = 0; i < compositeShape.countOfShapes_; i++)
  {
    allocator_.construct(&newBuffer[i], compositeShape.buffer_[i]);
  }

  for (size_t i = 0; i < countOfShapes_; i++)
  {
    allocator_.destroy(&buffer_[i]);
  }
  allocator_.deallocate(buffer_, capacity_);

  countOfShapes_ = compositeShape.countOfShapes_;
  capacity_ = compositeShape.capacity_;
  buffer_ = std::move(newBuffer);
  return *this;
}

dergunov::CompositeShape &dergunov::CompositeShape::operator =(dergunov::CompositeShape &&compositeShape) noexcept
{
  if (&compositeShape == this)
  {
    return *this;
  }
  countOfShapes_ = compositeShape.countOfShapes_;
  capacity_ = compositeShape.capacity_;
  buffer_ = compositeShape.buffer_;
  compositeShape.countOfShapes_ = 0;
  compositeShape.capacity_ = 0;
  compositeShape.buffer_ = nullptr;
  return *this;
}

std::shared_ptr<dergunov::Shape> dergunov::CompositeShape::operator[](size_t index) const
{
  if (index >= countOfShapes_)
  {
    throw std::out_of_range("Invalid index, it must be < countOfShapes and >= zero!");
  }
  return buffer_[index];
}

void dergunov::CompositeShape::expand()
{
  size_t newCapacity_ = capacity_ * MAGNIFICATION_RATIO;
  ShapePtr *newBuffer = allocator_.allocate(newCapacity_);

  for (size_t i = 0; i < countOfShapes_; i++)
  {
    allocator_.construct(&newBuffer[i], buffer_[i]);
  }

  for (size_t i = 0; i < countOfShapes_; i++)
  {
    allocator_.destroy(&buffer_[i]);
  }
  allocator_.deallocate(buffer_, capacity_);

  capacity_ = newCapacity_;
  buffer_ = std::move(newBuffer);
}

void dergunov::CompositeShape::squeeze()
{
  if (capacity_ <= START_CAPACITY)
  {
    return;
  }
  size_t newCapacity = capacity_ / MAGNIFICATION_RATIO;
  ShapePtr *newBuffer = allocator_.allocate(newCapacity);
  size_t oldCountOfShapes = std::min(countOfShapes_, capacity_);

  for (size_t i = 0; i < oldCountOfShapes; i++)
  {
    allocator_.construct(&newBuffer[i], buffer_[i]);

  }
  for (size_t i = 0; i < countOfShapes_; i++)
  {
    allocator_.destroy(&buffer_[i]);
  }
  allocator_.deallocate(buffer_, capacity_);

  countOfShapes_ = oldCountOfShapes;
  capacity_ = newCapacity;
  buffer_ = std::move(newBuffer);
}

void dergunov::CompositeShape::pushBackShape(const ShapePtr &addShape)
{
  if(addShape == nullptr)
  {
    throw std::invalid_argument("Pointer must indicate on object!");
  }

  allocator_.construct(&buffer_[countOfShapes_++], addShape);

  if (countOfShapes_ == capacity_){
    expand();
  }
}

void dergunov::CompositeShape::deleteShape(size_t index)
{
  if (countOfShapes_ == 1)
  {
    throw std::logic_error("Composite shape can not be empty");
  }
  if (index >= countOfShapes_)
  {
    throw std::out_of_range("Invalid index, it must be < countOfShapes and >= zero!");
  }
  if ((countOfShapes_ - 1) < (capacity_ / 2))
  {
    squeeze();
  }
  for (size_t i = index; i < countOfShapes_ - 1; i++){
    buffer_[i] = buffer_[i + 1];
  }
  allocator_.destroy(&buffer_[countOfShapes_ - 1]);
  countOfShapes_--;
}

size_t dergunov::CompositeShape::getCountOfShapes() const
{
  return countOfShapes_;
}

size_t dergunov::CompositeShape::getSize() const
{
  return capacity_;
}

dergunov::point_t dergunov::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

double dergunov::CompositeShape::getArea() const
{
  double sumAreaOfShapes = 0;
  for (size_t i = 0; i < countOfShapes_; i++)
  {
    sumAreaOfShapes += buffer_[i]->getArea();
  }
  return sumAreaOfShapes;
}

dergunov::rectangle_t dergunov::CompositeShape::getFrameRect() const
{
  dergunov::Rectangle firstShape{buffer_[0]->getFrameRect()};
  dergunov::point_t nowCenter {firstShape.getCenter()};
  double nowDX = firstShape.getWidth() / 2;
  double nowDY = firstShape.getHeight() / 2;
  double left = nowCenter.x - nowDX;
  double right = nowCenter.x + nowDX;
  double top = nowCenter.y + nowDY;
  double bottom = nowCenter.y - nowDY;

  double nowLeft = 0;
  double nowRight = 0;
  double nowTop = 0;
  double nowBottom = 0;
  for (size_t i = 1; i < countOfShapes_; i++)
  {
    dergunov::Rectangle nowShape{buffer_[i]->getFrameRect()};
    nowCenter = nowShape.getCenter();
    nowDX = nowShape.getWidth() / 2;
    nowDY = nowShape.getHeight() / 2;
    nowLeft = nowCenter.x - nowDX;
    nowRight = nowCenter.x + nowDX;
    nowTop = nowCenter.y + nowDY;
    nowBottom = nowCenter.y - nowDY;
    left = std::min(left, nowLeft);
    right = std::max(right, nowRight);
    top = std::max(top, nowTop);
    bottom = std::min(bottom, nowBottom);
  }
  double width = right - left;
  double height = top - bottom;
  dergunov::point_t center{(right + left) / 2, (top + bottom) / 2};
  return dergunov::rectangle_t{width, height, center};
}

void dergunov::CompositeShape::move(const dergunov::point_t &toPoint)
{
  dergunov::point_t centerOfCompositeShape = getCenter();
  double dx = toPoint.x - centerOfCompositeShape.x;
  double dy = toPoint.y - centerOfCompositeShape.y;
  move(dx, dy);
}

void dergunov::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < countOfShapes_; i++)
  {
    buffer_[i]->move(dx, dy);
  }
}

void dergunov::CompositeShape::scale(double scaleFactor)
{
  if (scaleFactor < 0)
  {
    throw std::invalid_argument("Scale ratio must not be negative!");
  }
  dergunov::point_t centerOfCompositeShape = getCenter();
  for (size_t i = 0; i < countOfShapes_; i++)
  {
    point_t centerOfNowShape = buffer_[i]->getCenter();
    double differenceCoordinateX = centerOfNowShape.x - centerOfCompositeShape.x;
    double differenceCoordinateY = centerOfNowShape.y - centerOfCompositeShape.y;
    double factor = scaleFactor - 1;

    double movingCoordinateX = differenceCoordinateX * factor;
    double movingCoordinateY = differenceCoordinateY * factor;

    buffer_[i]->move(movingCoordinateX, movingCoordinateY);
    buffer_[i]->scale(scaleFactor);
  }
}

void dergunov::CompositeShape::rotate(double degree)
{
  degree = fmod(degree, 360);
  if (degree < 0)
  {
    degree += 360;
  }

  point_t center = getCenter();
  double radians = degree * M_PI / 180;
  double sinForMove = std::sin(radians);
  double cosForMove = std::cos(radians);
  for (size_t i = 0; i < countOfShapes_; i++)
  {
    std::shared_ptr<Shape> nowShape = buffer_[i];
    point_t centerNowShape = buffer_[i]->getCenter();
    double dx = centerNowShape.x - center.x;
    double dy = centerNowShape.y - center.y;
    double moveX = center.x + dx * cosForMove - dy * sinForMove;
    double moveY = center.y + dy * cosForMove + dx * sinForMove;
    point_t movePoint {moveX, moveY};
    nowShape->move(movePoint);
    nowShape->rotate(degree);
  }
}

void dergunov::CompositeShape::showInformation(std::ostream &out) const
{
  rectangle_t frameRect {getFrameRect()};
  point_t center {frameRect.pos};
  out << "CompositeShape, consists of " << countOfShapes_ << " shapes\nArea: "
      << getArea() << "\nCoordinate center: " << center.x << " " << center.y
      << "\nArea:" << getArea() << "\nRectangle described:\nWidth: " << frameRect.width
      << "\nHeight: " << frameRect.height;
}
