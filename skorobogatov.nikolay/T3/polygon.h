#ifndef __POLYGON_H_
#define __POLYGON_H_

#include <iostream>
#include <vector>

namespace skor
{
  struct Point
  {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
  };

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool operator<(const Polygon& other) const;
    bool operator==(const Polygon& other) const;
    bool operator!=(const Polygon& other) const;
  };

  struct Frame
  {
    Point lowerLeft;
    Point upperRight;
    Frame(const Point& lowerLeft, const Point& upperRight);
    bool containsPoint(const Point& p) const;
    bool containsPolygon(const Polygon& poly) const;
  };

  struct Triangle
  {
    Point a, b, c;
    Triangle(const Point& a, const Point& b, const Point& c);
    double getArea() const;
  };

  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);

  double getDistance(const Point& p1, const Point& p2);
  Frame getFrame(const std::vector<Polygon>& data);
}

#endif
