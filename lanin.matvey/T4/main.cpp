#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "ring.h"
#include "composite_shape.h"

void printShape(const Shape& shape)
{
    Point c = shape.getCenter();
    std::cout << "[" << shape.getName() << ", ("
              << std::fixed << std::setprecision(2) << c.x << ", "
              << std::setprecision(2) << c.y << "), "
              << std::setprecision(2) << shape.getArea() << "]";
}

void printComposite(const CompositeShape& comp)
{
    Point c = comp.getCenter();
    std::cout << "[" << comp.getName() << ", ("
              << std::fixed << std::setprecision(2) << c.x << ", "
              << std::setprecision(2) << c.y << "), "
              << std::setprecision(2) << comp.getArea() << ":\n";

    const auto& shapes = comp.getShapes();
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        std::cout << "  ";
        printShape(*shapes[i]);
        if (i != shapes.size() - 1)
            std::cout << ",";
        std::cout << "\n";
    }

    std::cout << "]";
}

int main()
{
    try
    {
        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
        shapes.push_back(std::make_unique<Ring>(Point(2, 2), 5.0, 2.0));
        shapes.push_back(std::make_unique<Ring>(Point(-3, -1), 3.0, 1.0));

        auto comp1 = std::make_unique<CompositeShape>();
        comp1->addShape(std::make_unique<Rectangle>(Point(5, 5), Point(7, 8)));
        comp1->addShape(std::make_unique<Ring>(Point(6, 6), 2.0, 0.5));
        shapes.push_back(std::move(comp1));

        auto comp2 = std::make_unique<CompositeShape>();
        comp2->addShape(std::make_unique<Ring>(Point(-5, -2), 4.0, 1.5));
        shapes.push_back(std::move(comp2));

        std::cout << "BEFORE SCALE:\n";
        for (const auto& s : shapes)
        {
            if (auto c = dynamic_cast<const CompositeShape*>(s.get()))
                printComposite(*c);
            else
                printShape(*s);
            std::cout << "\n";
        }

        for (auto& s : shapes)
            s->scale(2.0);

        std::cout << "==========================================\n";
        std::cout << "AFTER SCALE:\n";
        for (const auto& s : shapes)
        {
            if (auto c = dynamic_cast<const CompositeShape*>(s.get()))
                printComposite(*c);
            else
                printShape(*s);
            std::cout << "\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
