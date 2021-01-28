// Instructions:
//
// Aim of the test:
//
// 1) Demonstrate your programming skills
// 2) Produce a good quality robust working code which reads the
//    geometries specified in provided files Circles.txt and Ellipses.txt.
// 3) Build any class considered necessary
//    Note: 
//    - the code will be tested on more geometries than those
//      provided in Circles.txt and Ellipses.txt
//    - reuse this main function with NO MODIFICATIONS

#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "GeometryContainer.h"
#include "GeometryUtility.h"

int main(int argc, char* argv[])
{
	GeometryContainer geometryContainer;
	if (!geometryContainer.readCirclesData( std::string(argv[1])) ) {
		std::cout << "Could not read circles file " << argv[1] << std::endl;
		return 0;
	}
	if (!geometryContainer.readEllipsesData( std::string(argv[2])) ) {
		std::cout << "Could not read ellipses file " << argv[2] << std::endl;
		return 0;
	}

	GeometryUtility geomeryUtility;
	std::vector<std::pair<double,double> > intersectionPoints;
	std::ofstream outfile(argv[3]);
	if (!outfile.is_open()) {
		std::cout << "Could not open output file " << argv[3] << std::endl;
		return 0;
	}
	for (int i=0; i<int(geometryContainer.numberOfGeometries()); ++i) {
		for (int j=i+1; j<int(geometryContainer.numberOfGeometries()); ++j) {
			outfile << "Results for geometry " << i << " vs geometry " << j << std::endl;
			if (geomeryUtility.computeIntersectionPoints(
				geometryContainer, i, j, intersectionPoints))
			{
				if (int(intersectionPoints.size()==0)) {
					outfile << "No intersection points found!" << std::endl;
				} else {
					for (int i=0; i<int(intersectionPoints.size()); ++i) {
						outfile << "Intersection point " << i << std::endl;
						outfile << intersectionPoints[i].first << " "
							<< intersectionPoints[i].second << std::endl;
					}
				}
			} else {
				outfile << "Error determining intersection points!" << std::endl;
			}
		}
	}
	outfile.close();

	return 0;
}
