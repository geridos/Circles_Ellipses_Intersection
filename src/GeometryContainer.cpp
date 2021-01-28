#include <fstream>
#include <iostream>
#include <sstream> 
#include <iterator>

#include "GeometryContainer.h"

unsigned GeometryContainer::numberOfGeometries()
{
    return m_circles.size() + m_ellipses.size();
}

bool GeometryContainer::readFile(const std::string& file, GeometricType type)
{
    if (file == "")
    {
        return false;
    }
    unsigned numberData = 5;
    if (type == GeometricType::Circle)
        numberData = 3;

    std::ifstream input(file);
    if (not input.is_open())
    {
        return false;
    }
    std::string line;
    std::stringstream ss;

    //Skip first line
    getline(input, line);

    try
    {
        while (getline(input, line))
        {
            ss.clear();
            ss << line;
            std::vector<std::string> data((std::istream_iterator<std::string>(ss)),
                    std::istream_iterator<std::string>());

            if (data.size() != numberData)
                std::cerr << "Invalid number of data in " << file << std::endl;

            if (type == GeometricType::Circle)
            {
                m_circles.emplace_back(std::stod(data.at(0)),
                        std::stod(data.at(1)),
                        std::stod(data.at(2))
                        );

                //Debug
                //m_circles[m_circles.size() - 1].printData();
            }
            else
            {
                m_ellipses.emplace_back(std::stod(data.at(0)),
                        std::stod(data.at(1)),
                        std::stod(data.at(2)),
                        std::stod(data.at(3)),
                        std::stod(data.at(4))
                        );
                //Debug
                //m_ellipses[m_ellipses.size() - 1].printData();
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Unable to parse data in " << file << std::endl;
        return false;
    }
    return true;
}

bool GeometryContainer::readEllipsesData(const std::string& file)
{
    return readFile(file, GeometricType::Ellipse);
}

bool GeometryContainer::readCirclesData(const std::string& file)
{
    return readFile(file, GeometricType::Circle);
}

const Shape& GeometryContainer::getShapeAt(int i) const
{
    if (i >= (int)m_circles.size())
    {
        return m_ellipses.at(i - m_circles.size());
    }
    return m_circles.at(i);
}
