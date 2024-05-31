#include <numeric>
#include <algorithm>
#include <cmath>
#include <iterator>
#include "Polygon.h"

namespace mrkv
{
  bool Point::operator==(const Point& other)
  {
    return this->x == other.x && this->y == other.y;
  }

  bool Point::operator!=(const Point& other)
  {
    return (this->x != other.x) || (this->y != other.y);
  }

  bool Polygon::operator==(const Polygon& other)
  {
    if (this->points.size() != other.points.size())
    {
      return false;
    }

    for (size_t i = 0; i < this->points.size(); ++i)
    {
      if (this->points[i] != other.points[i])
      {
        return false;
      }
    }
    return true;
  }

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char symbol = '0';
    in >> symbol;
    if (in && (symbol != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Point& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    Polygon input;
    {
      int size = 0;
      in >> size;
      if (!in || size < 3)
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      int readPointsCount = 0;
      while (readPointsCount < size)
      {
        if (!in)
        {
          in.setstate(std::ios::failbit);
        }
        if (in.peek() == '\n')
        {
          break;
        }
        Point point;
        in >> point;
        input.points.push_back(point);
        ++readPointsCount;
      }
      if (readPointsCount != size || (in.peek() != '\n' && !in.eof()))
      {
        in.setstate(std::ios::failbit);
      }
    }
    if (in)
    {
      polygon = input;
    }
    return in;
  }

  std::vector<Polygon> readPolygons(std::istream& in)
  {
    std::vector<Polygon> polygons;
    while (!in.eof())
    {
      if (!in)
      {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      std::copy(
        std::istream_iterator<Polygon>(in),
        std::istream_iterator<Polygon>(),
        std::back_inserter(polygons)
      );
    }
    return polygons;
  }

  double calculateTriangleArea(const Point& p1, const Point& p2, const Point& p3)
  {
    double a = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    double b = sqrt((p2.x - p3.x) * (p2.x - p3.x) + (p2.y - p3.y) * (p2.y - p3.y));
    double c = sqrt((p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y));

    double p = (a + b + c) / 2;

    return sqrt(p * (p - a) * (p - b) * (p - c));
  }

  double calculatePolygonArea(const Polygon& polygon)
  {
    const Point p0 = polygon.points[0];
    Point prev = polygon.points[1];

    auto lambda = [&p0, &prev](double acc, const Point& cur)
      {
        acc += calculateTriangleArea(p0, prev, cur);
        prev = cur;
        return acc;
      };
    return std::accumulate(polygon.points.begin() + 2, polygon.points.end(), 0.0, lambda);
  }

  double areaAccumulator(double acc, const Polygon& poly, int div, int rem)
  {
    double res = acc;
    if (int(poly.points.size()) % div == rem || rem == -1)
    {
      res += calculatePolygonArea(poly);
    }
    return res;
  }

  double areaAccumulatorVertexes(double acc, const Polygon& poly, int numOfVertexes)
  {
    double res = acc;
    if (int(poly.points.size()) == numOfVertexes)
    {
      res += calculatePolygonArea(poly);
    }
    return res;
  }

  bool areaComporator(const Polygon& a, const Polygon& b)
  {
    return calculatePolygonArea(a) < calculatePolygonArea(b);
  }

  bool vertexesComporator(const Polygon& a, const Polygon& b)
  {
    return a.points.size() < b.points.size();
  }

  bool countCondition(const Polygon& poly, int div, int rem)
  {
    return (int(poly.points.size()) % div == rem) ? true : false;
  }

  bool countConditionVertexes(const Polygon& poly, int numOfVertexes)
  {
    return (int(poly.points.size()) == numOfVertexes) ? true : false;
  }

  int getLeftB(Polygon& poly)
  {
    return std::min_element(poly.points.begin(), poly.points.end(),
      [](Point& a, Point& b) { return a.x < b.x; })->x;
  }

  int getRightB(Polygon& poly)
  {
    return std::max_element(poly.points.begin(), poly.points.end(),
      [](Point& a, Point& b) { return a.x < b.x; })->x;
  }

  int getDownB(Polygon& poly)
  {
    return std::min_element(poly.points.begin(), poly.points.end(),
      [](Point& a, Point& b) { return a.y < b.y; })->y;
  }

  int getUpB(Polygon& poly)
  {
    return std::max_element(poly.points.begin(), poly.points.end(),
      [](Point& a, Point& b) { return a.y < b.y; })->y;
  }

  int getLeftFiguresB(std::vector<Polygon>& figures)
  {
    return getLeftB(*std::min_element(figures.begin(), figures.end(),
      [](Polygon& a, Polygon& b) { return getLeftB(a) < getLeftB(b); })
    );
  }

  int getRightFiguresB(std::vector<Polygon>& figures)
  {
    return getRightB(*std::max_element(figures.begin(), figures.end(),
      [](Polygon& a, Polygon& b) { return getRightB(a) < getRightB(b); })
    );
  }

  int getDownFiguresB(std::vector<Polygon>& figures)
  {
    return getDownB(*std::min_element(figures.begin(), figures.end(),
      [](Polygon& a, Polygon& b) { return getDownB(a) < getDownB(b); })
    );
  }

  int getUpFiguresB(std::vector<Polygon>& figures)
  {
    return getUpB(*std::max_element(figures.begin(), figures.end(),
      [](Polygon& a, Polygon& b) { return getUpB(a) < getUpB(b); })
    );
  }
}
