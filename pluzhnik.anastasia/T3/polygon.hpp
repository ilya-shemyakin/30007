#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

namespace pluzhnik
{
  struct Point
  {
    int x_;
    int y_;
  };

  struct DelimiterIO
  {
    char exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

  struct Polygon
  {
    std::vector< Point > points_;
  };

  bool operator==(const Point& lhs, const Point& rhs);
  bool operator==(const Polygon& lhs, const Polygon& rhs);

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);

  int getVertexes (const Polygon& polygon);
  double calcTriangleArea(const Point& p1, const Point& p2, const Point& p3);
  double getArea(const Polygon& polygon);
  bool areaComparator(const Polygon& lhs, const Polygon& rhs);
  bool vertexesComparator(const Polygon& lhs, const Polygon& rhs);
  bool pointsComparator(const Point& p1, const Point& p2);
}

#endif
