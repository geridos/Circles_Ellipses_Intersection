#pragma once

#include <string>
#include <vector>
#include <iostream>

enum class GeometricType {Circle, Ellipse, Shape};

class Shape
{
public:
    virtual GeometricType getType() const
    {
        return GeometricType::Shape;
    }
};

class Circle : public Shape
{
public:
    Circle(double x, double y, double radius) :
        x(x),
        y(y),
        r(radius)
    {}

    virtual GeometricType getType() const override
    {
        return GeometricType::Circle;
    }

   const double x;
   const double y;
   const double r;

    void printData() const
    {
        std::cout << x
            << " " << y
            << " " << r
            << std::endl;
    }
};

class Ellipse : public Shape
{
public:
    Ellipse(double focus1X,
            double focus1Y,
            double focus2X,
            double focus2Y,
            double eccentricity) :
        f1x(focus1X),
        f1y(focus1Y),
        f2x(focus2X),
        f2y(focus2Y),
        e(eccentricity)
    {}

    virtual GeometricType getType() const override
    {
        return GeometricType::Ellipse;
    }

    const double f1x;
    const double f1y;
    const double f2x;
    const double f2y;
    const double e;

    void printData() const
    {
        std::cout << f1x
            << " " << f1y
            << " " << f2x
            << " " << f2y
            << " " << e 
            << std::endl;
    }
};


class GeometryContainer
{
public:
    bool readCirclesData(const std::string& file);
    bool readEllipsesData(const std::string& file);
    unsigned numberOfGeometries();
    const Shape& getShapeAt(int i) const;

private:
    bool readFile(const std::string& file, GeometricType type);
    std::vector<Circle> m_circles;
    std::vector<Ellipse> m_ellipses;
};
