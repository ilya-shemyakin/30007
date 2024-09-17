#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <iostream>

namespace T3_hism
{
  struct Point
  {
    int x,y;
    bool operator==(const Point& other) const
    {
      return x == other.x && y == other.y;
    }
  };
  struct Polygon
  {
    std::vector<Point> points;
  };
  struct DelimiterIO
  {
    char exp;
  };
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::vector<Polygon> readStream(std::istream& in);
  double getTriangleArea(const Point& a, const Point& b, const Point& c);
  double getPolygonArea(const Polygon& dest);
  double getSumArea_Param(double summary, const Polygon& dest, int param, int vertex_count);
  int getLeftX(Polygon& dest);
  int getLeftY(Polygon& dest);
  int getRightX(Polygon& dest);
  int getRightY(Polygon& dest);
  int getLeftX_data(std::vector<Polygon>& data);
  int getLeftY_data(std::vector<Polygon>& data);
  int getRightX_data(std::vector<Polygon>& data);
  int getRightY_data(std::vector<Polygon>& data);
}
#endif
