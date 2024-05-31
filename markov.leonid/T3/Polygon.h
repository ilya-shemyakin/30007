#ifndef POLYGON_H
#define POLYGON_H
#include <iostream>
#include <vector>

namespace mrkv
{
  struct Point
  {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Point& other);
    bool operator!=(const Point& other);
  };
  struct Polygon
  {
    std::vector<Point> points;

    bool operator==(const Polygon& other);
  };
  struct DelimiterIO
  {
    char exp;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::vector<Polygon> readPolygons(std::istream& in);

  double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3);
  double calculatePolygonArea(const Polygon& polygon);

  double areaAccumulator(double acc, const Polygon& poly, int div, int rem);
  double areaAccumulatorVertexes(double acc, const Polygon& poly, int numOfVertexes);
  bool areaComporator(const Polygon& a, const Polygon& b);
  bool vertexesComporator(const Polygon& a, const Polygon& b);
  bool countCondition(const Polygon& poly, int div, int rem);
  bool countConditionVertexes(const Polygon& poly, int numOfVertexes);

  int getLeftB(Polygon& poly);
  int getRightB(Polygon& poly);
  int getDownB(Polygon& poly);
  int getUpB(Polygon& poly);

  int getLeftFiguresB(std::vector<Polygon>& figures);
  int getRightFiguresB(std::vector<Polygon>& figures);
  int getDownFiguresB(std::vector<Polygon>& figures);
  int getUpFiguresB(std::vector<Polygon>& figures);
}
#endif
