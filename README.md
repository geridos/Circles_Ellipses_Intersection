AUTHORS
Bertrand de Montety     bertrand2mo@gmail.com

DATE: 27/01/2021

This tarball contains 2 technical tests asked by ADT (https://www.adt.co.uk/).

The second exercise detects intersections between circles and ellipses.
Only intersetions with circles are calculated.

TODO:
- Implement the solution for circles and ellipses and ellipses between themselves.
- Use gsl lib to solve polynom equation (link with -lgslcblas -lgsl)

LIB:
No libs are required to compiled as it is now.

NOTE:
quick exec : 
g++ --std=c++11 TestProject2.cpp Geometry*.cpp -lgslcblas -lgsl  -g3  && ./a.out Circles.txt Ellipses.txt output && cat output
