#pragma once

#include "GeometryContainer.h" 

class GeometryUtility
{
public:
    bool computeIntersectionPoints(const GeometryContainer& container, int i,
            int j, std::vector<std::pair<double,double>>& intersections);
private:
    void intersection2Circles(const Circle& c1, const Circle& c2, std::vector<std::pair<double, double>>& inter);
    void intersection2Ellipses(Ellipse e1, Ellipse e2, std::vector<std::pair<double, double>>& inter );
    void intersectionEllipseCircle(Ellipse e, Circle c, std::vector<std::pair<double, double>>& inter);
};
