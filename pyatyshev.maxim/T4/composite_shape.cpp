#include "composite_shape.h"
#include <algorithm>
#include <limits>

CompositeShape::CompositeShape() : shapes_()
{
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
  shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
  double area = 0;
  for (const auto& shape : shapes_)
  {
    area += shape->getArea();
  }
  return area;
}

Point CompositeShape::getCenter() const
{
  if (shapes_.empty())
  {
    return Point();
  }

  double minX = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double minY = std::numeric_limits<double>::max();
  double maxY = std::numeric_limits<double>::lowest();

  for (const auto& shape : shapes_)
  {
    Point center = shape->getCenter();
    double area = shape->getArea();
    double size = std::sqrt(area);

    minX = std::min(minX, center.x - size);
    maxX = std::max(maxX, center.x + size);
    minY = std::min(minY, center.y - size);
    maxY = std::max(maxY, center.y + size);
  }

  return Point((minX + maxX) / 2, (minY + maxY) / 2);
}

void CompositeShape::move(double dx, double dy)
{
  for (auto& shape : shapes_)
  {
    shape->move(dx, dy);
  }
}

void CompositeShape::scale(double factor)
{
  Point center = getCenter();
  for (auto& shape : shapes_)
  {
    Point shapeCenter = shape->getCenter();
    double dx = (shapeCenter.x - center.x) * factor - (shapeCenter.x - center.x);
    double dy = (shapeCenter.y - center.y) * factor - (shapeCenter.y - center.y);
    shape->move(dx, dy);
    shape->scale(factor);
  }
}

std::string CompositeShape::getName() const
{
  return "COMPOSITE";
}

size_t CompositeShape::getSize() const
{
  return shapes_.size();
}

const std::unique_ptr<Shape>& CompositeShape::getShape(size_t index) const
{
  return shapes_[index];
}