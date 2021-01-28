#include <math.h>

//Install gsl and compile with -lgslcblas -lgsl if needed
#define COMPILE_WITHOUT_GSL 0

#if COMPILE_WITHOUT_GSL
#include <gsl/gsl_poly.h>
#endif

#include "GeometryUtility.h"

#define p2(x) pow(x, 2)

//describe polynom ax^2 + bx + c = 0
struct polynom
{
    double a;
    double b;
    double c;
};

bool GeometryUtility::computeIntersectionPoints(const GeometryContainer& container,
        int i, int j, std::vector<std::pair<double,double>>& intersections)
{
    intersections.clear();

    const Shape& s1 = container.getShapeAt(i);
    const Shape& s2 = container.getShapeAt(j);

    if (s1.getType() == GeometricType::Circle and
            s2.getType() == GeometricType::Circle)
    {
        intersection2Circles(dynamic_cast<const Circle&>(s1), dynamic_cast<const Circle&>(s2), intersections);
    }
    else if (s1.getType() == GeometricType::Ellipse and
            s2.getType() == GeometricType::Circle)
    {
    }
    else if (s2.getType() == GeometricType::Ellipse and
            s1.getType() == GeometricType::Circle)
    {
    }
    else if (s2.getType() == GeometricType::Ellipse and
            s1.getType() == GeometricType::Ellipse)
    {
        //intersection2Ellipses(dynamic_cast<const Ellipse&>(s1), dynamic_cast<const Ellipse&>(s2), intersections);
    }
    return true;
}


//if b^2 - 4ac if inf 0 -> no intersection 
//if b^2 - 4ac if eq 0 -> 1 intersection 
//if b^2 - 4ac if sup 0 -> 2 intersection 
std::vector<double> solveEquation(const polynom& p)
{
    std::vector<double> res;
    //Solve x = (-b {+-} sqrt(b^2 - 4ac)) / 2a
    double exp = p2(p.b) - 4 * p.a * p.c;
    if (exp == 0)
    {
        double x = - p.b / (2 * p.a);
        res.push_back(x);
    }
    else if (exp > 0)
    {
        double x1 = (- p.b + sqrt(exp)) / (2 * p.a);
        double x2 = (- p.b - sqrt(exp)) / (2 * p.a);
        res.push_back(x1);
        res.push_back(x2);
    }
    return res;
}

void GeometryUtility::intersection2Circles(const Circle& c1, const Circle& c2, std::vector<std::pair<double, double>>& inter)
{
    //General equation
    //1. (x−x1)^2+(y−y1)^2=r1^2
    //2. (x−x2)^2+(y−y2)^2=r2^2
    if (c1.x == c2.x and c1.y == c2.y)
    {
        return;
    }

    //y = Ax + B
    double B = 0;
    double A = 0;

    //ax^2 + bx + c = 0
    double a = 0;
    double b = 0;
    double c = 0;

    double x = 0;
    double y = 0;

    if (c1.x == c2.x)
    {
        //Sub (1) from (2)
        B = (-1 / (2 * (c1.y - c2.y))) * ( (p2(c1.r) - p2(c2.r)) - (p2(c1.x) - p2(c2.x)) - (p2(c1.y) - p2(c2.y)) ); 
        y = B;

        //We need to solve the polynom : ax^2 + bx + c = 0 with:
        a = 1;
        b = -2 * c1.x;
        c = p2(c1.x) + p2((B - c1.y)) - p2(c1.r);
        polynom p {a, b, c};

        auto res = solveEquation(p);

        if (res.empty())
            return;

        else if (res.size() == 1)
        {
            inter.emplace_back(res[0], y);
            return;
        }
        else if (res.size() == 2)
        {
            inter.emplace_back(res[0], y);
            inter.emplace_back(res[1], y);
            return;
        }
    }
    //Find x = B
    else if (c1.y == c2.y)
    {
        //Sub (2) from (1)
        B = (-1 / (2 * (c1.x - c2.x))) * ( (p2(c1.r) - p2(c2.r)) - (p2(c1.y) - p2(c2.y)) - (p2(c1.x) - p2(c2.x)) ); 
        x = B;

        //We Need to solve ay^2 + by + c = 0 with:
        a = 1;
        b = -2 * c1.y;
        c = p2(c1.y) + p2((B - c1.x)) - p2(c1.r);
        polynom p {a, b, c};

        auto res = solveEquation(p);

        if (res.empty())
            return;
        else if (res.size() == 1)
        {
            inter.emplace_back(x, res[0]);
            return;
        }
        else if (res.size() == 2)
        {
            inter.emplace_back(x, res[0]);
            inter.emplace_back(x, res[1]);
            return;
        }
    }
    else
    {
        //Sub (2) from (1)
        B = (-1 / (2 * (c1.y - c2.y))) * ( (p2(c1.r) - p2(c2.r)) - (p2(c1.x) - p2(c2.x)) - (p2(c1.y) - p2(c2.y)) ); 
        A = - ((c1.x - c2.x) / (c1.y - c2.y));

        //replace y in (1)
        //(x - c1.x)^2 + (Ax + B - c1.y)^2 = c1.r^2
        a = (p2(A)) + 1;
        b = (-2 * c1.x + 2 * A * (B - c1.y));
        c = p2((B - c1.y)) - p2(c1.r) + p2(c1.x);
        polynom p {a, b, c};

        auto res_x = solveEquation(p);
        if (res_x.empty())
            return;
    
        //Find x = Ay + B
        B = (-1 / (2 * (c1.x - c2.x))) * ( (p2(c1.r) - p2(c2.r)) - (p2(c1.y) - p2(c2.y)) - (p2(c1.x) - p2(c2.x)) ); 
        A = - ((c1.y - c2.y) / (c1.x - c2.x));
        //replace x in (1)
        a = (p2(A)) + 1;
        b = (-2 * c1.y + 2 * (B - c1.x) * A);
        c = p2((B - c1.x)) - p2(c1.r) + p2(c1.y);
        polynom p1 {a, b, c};

        auto res_y = solveEquation(p1);

        if (res_x.size() != res_y.size())
        {
            std::cerr << "Error in while solving circle equation" << std::endl;
            return;
        }

        if (res_x.size() == 1)
        {
            inter.emplace_back(res_x[0], res_y[0]);
        }
        else if (res_x.size() == 2)
        {
            inter.emplace_back(res_x[1], res_y[0]);
            inter.emplace_back(res_x[0], res_y[1]);
        }
    }
}

//Not working.
void GeometryUtility::intersection2Ellipses(Ellipse e1, Ellipse e2, std::vector<std::pair<double, double>>& inter)
{
    //1. ((x−x1)^2) / a^2 + ((y−y1)^2) / b2 = r1^2
    //e = c / a
    //e = sqrt(1 - (a / b)^2)
    
    //center e1
    double cx1 = (e1.f1x + e1.f2x) / 2;
    double cy1 = (e1.f2y + e1.f2y) / 2;

    double cx2 = (e2.f1x + e2.f2x) / 2;
    double cy2 = (e2.f2y + e2.f2y) / 2;

    //c is the lenght of the segment between the center and a foci
    //c^2 = (e1.f2x - cx1 )^2  + (e1.f2y - cy1)^2
    double c1 = sqrt(p2(e1.f2x - cx1 ) + p2(e1.f2y - cy1));
    double a1 = c1 / e1.e;
    double b1 = a1 / (1 - sqrt(e1.e));

    double c2 = sqrt(p2(e2.f2x - cx2 ) + p2(e2.f2y - cy2));
    double a2 = c2 / e2.e;
    double b2 = a2 / (1 - sqrt(e2.e));

    double d = -2 * cx1 + 2 * cx2;
    double ab1 = (p2(a1) / p2(b1));
    double ab2 = (p2(a2) / p2(b2));
    double a = (ab1 - ab2);
    double b = -2 * ab1 * cy1 + 2 * ab2 + cy2;
    double c = p2(cx1) - p2(cx2) + ab1 * p2(cy1) - ab2 * p2(cy2) - p2(a1) + p2(a2);
    double f = p2(a1);
    double g = cy1;
    double e = cx1;
    double h = p2(b1);

    double f4 = p2(a)/(p2(d) * p2(f));
    double f3 = 2 * a * b / (p2(d) * p2(f));
    double f2 =
        (-2 * a * c / (p2(d) * p2(f)))
        + (p2(b) / (p2(d) * p2(f)))
        + (2 * e * a / (d * p2(f)))
        + 1 / p2(h);
    double f1 =
        (2 * b * c / (p2(d) * p2(f)))
        + (2 * e * b / (d * p2(f)))
        + (- 2 * g / p2(h));
    double f0 = 
        (p2(c)/ (p2(d) * p2(f)))
        + (2 * e * c / (d * p2(f)))
        + (p2(e) / p2(f))
        + (p2(g) / p2(h));


    int i;
    /* coefficients of P(x) =  -1 + x^5  */
    double input[5] = {f0, f1, f2, f3, f4};
    double output[5];

#if COMPILE_WITHOUT_GSL
    gsl_poly_complex_workspace * w
        = gsl_poly_complex_workspace_alloc (5);

    gsl_poly_complex_solve (input, 5, w, output);

    gsl_poly_complex_workspace_free (w);

    for (i = 0; i < 4; i++)
    {
        printf ("z%d = %+.18f %+.18f\n",
                i, output[2*i], output[2*i+1]);

    }
#endif
}

void GeometryUtility::intersectionEllipseCircle(Ellipse e, Circle c, std::vector<std::pair<double, double>>& inter)
{
}
