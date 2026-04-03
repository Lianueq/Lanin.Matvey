#include "rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Point& bottomLeft_, const Point& topRight_)
    : bottomLeft(bottomLeft_), topRight(topRight_)
{
    if (bottomLeft.x >= topRight.x || bottomLeft.y >= topRight.y)
        throw std::invalid_argument("Invalid rectangle coordinates");
}

double Rectangle::getArea() const
{
    return (topRight.x - bottomLeft.x) * (topRight.y - bottomLeft.y);
}

Point Rectangle::getCenter() const
{
    return Point((bottomLeft.x + topRight.x) / 2.0,
                 (bottomLeft.y + topRight.y) / 2.0);
}

void Rectangle::move(double dx, double dy)
{
    bottomLeft.x += dx;
    bottomLeft.y += dy;
    topRight.x += dx;
    topRight.y += dy;
}

void Rectangle::scale(double factor)
{
    if (factor <= 0)
        throw std::invalid_argument("Scale factor must be positive");
    Point center = getCenter();
    bottomLeft.x = center.x + (bottomLeft.x - center.x) * factor;
    bottomLeft.y = center.y + (bottomLeft.y - center.y) * factor;
    topRight.x = center.x + (topRight.x - center.x) * factor;
    topRight.y = center.y + (topRight.y - center.y) * factor;
}

std::string Rectangle::getName() const
{
    return "RECTANGLE";
}
