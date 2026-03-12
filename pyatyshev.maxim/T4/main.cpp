#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "isosceles_trapezoid.h"
#include "composite_shape.h"

void printShape(const Shape& shape)
{
  Point center = shape.getCenter();
  std::cout << "[" << shape.getName() << ",("
            << std::fixed << std::setprecision(2)
            << center.x << ", " << center.y << "), "
            << shape.getArea() << "]";
}

void printCompositeShape(const CompositeShape& composite)
{
  Point center = composite.getCenter();
  std::cout << "[" << composite.getName() << ",("
            << std::fixed << std::setprecision(2)
            << center.x << ", " << center.y << "), "
            << composite.getArea() << ": ";

  for (size_t i = 0; i < composite.getSize(); ++i)
  {
    if (i > 0)
    {
      std::cout << ", ";
    }
    printShape(*composite.getShape(i));
  }
  std::cout << "]";
}

int main()
{
  std::vector<std::unique_ptr<Shape>> shapes;

  shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
  shapes.push_back(std::make_unique<IsoscelesTrapezoid>(Point(5, 0), 6, 4, 3));
  shapes.push_back(std::make_unique<Rectangle>(Point(10, 5), Point(15, 9)));

  auto composite = std::make_unique<CompositeShape>();
  composite->addShape(std::make_unique<Rectangle>(Point(0, 0), Point(2, 2)));
  composite->addShape(std::make_unique<IsoscelesTrapezoid>(Point(3, 0), 3, 2, 2));
  shapes.push_back(std::move(composite));

  shapes.push_back(std::make_unique<IsoscelesTrapezoid>(Point(20, 10), 8, 5, 4));

  std::cout << "Before scaling:\n";
  for (const auto& shape : shapes)
  {
    if (shape->getName() == "COMPOSITE")
    {
      printCompositeShape(dynamic_cast<const CompositeShape&>(*shape));
    }
    else
    {
      printShape(*shape);
    }
    std::cout << "\n";
  }

  std::cout << "\nAfter scaling by factor 2:\n";
  for (auto& shape : shapes)
  {
    shape->scale(2);
    if (shape->getName() == "COMPOSITE")
    {
      printCompositeShape(dynamic_cast<const CompositeShape&>(*shape));
    }
    else
    {
      printShape(*shape);
    }
    std::cout << "\n";
  }

  return 0;
}