#include "Polygon.h"
#include <numeric>
#include <iterator>
#include <algorithm>
#include <functional>
#include <cmath>

namespace T3_hism {
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    Polygon polyInput;
    int vertex_count = 0;
    in >> vertex_count;
    if (!in || vertex_count < 3) {
      in.setstate(std::ios::failbit);
      return in;
    }
    int count_points = 0;
    while (count_points < vertex_count) {
      if (!in) {
        in.setstate(std::ios::failbit);
      }
      else if (in.peek() == '\n') {
        break;
      }
      Point point;
      in >> point;
      polyInput.points.push_back(point);
      count_points++;
    }
    if ((in.peek() != '\n' && !in.eof()) || count_points != vertex_count) {
      in.setstate(std::ios::failbit);
    }
    if (in) {
      dest = polyInput;
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

  std::vector<Polygon> readStream(std::istream& in)
  {
    std::vector<Polygon> data;
    while (!in.eof()) {
      if (!in) {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      std::copy(
        std::istream_iterator<Polygon>(in),
        std::istream_iterator<Polygon>(),
        std::back_inserter(data)
      );
    }
    return data;
  }

  double getTriangleArea(const Point& a, const Point& b, const Point& c)
  {
    double x1 = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
    double x2 = sqrt(pow((b.x - c.x), 2) + pow((b.y - c.y), 2));
    double x3 = sqrt(pow((c.x - a.x), 2) + pow((c.y - a.y), 2));
    double perim = (x1 + x2 + x3) / 2;
    return sqrt(perim * (perim - x1) * (perim - x2) * (perim - x3));
  }

  double getPolygonArea(const Polygon& dest)
  {
    const Point fixedpoint = dest.points[0];
    Point previouspoint = dest.points[1];

    auto lambda = [&fixedpoint, &previouspoint](double summary, const Point& cur)
      {
        summary += getTriangleArea(fixedpoint, previouspoint, cur);
        previouspoint = cur;
        return summary;
      };
    return std::accumulate(dest.points.begin() + 2, dest.points.end(), 0.0, lambda);
  }

  double getSumArea_Param(double summary, const Polygon& dest, int param, int vertex_count)
  {
    double func_summary_result = summary;
    if ((static_cast<int>(dest.points.size()) % 2 == param || param == -10) && vertex_count == 0)
    {
      func_summary_result += getPolygonArea(dest);
    }
    else if (param == -20 && static_cast<int>(dest.points.size()) == vertex_count) {
      func_summary_result += getPolygonArea(dest);
    }
    return func_summary_result;
  }

  int getLeftX(Polygon& dest)
  {
    return std::min_element(dest.points.begin(), dest.points.end(), [](const Point& a, const Point& b)
      {
      return a.x < b.x;
      })->x;
  }

  int getLeftY(Polygon& dest)
  {
    return std::min_element(dest.points.begin(), dest.points.end(), [](const Point& a, const Point& b)
      {
      return a.y < b.y;
      })->y;
  }

  int getRightX(Polygon& dest)
  {
    return std::max_element(dest.points.begin(), dest.points.end(), [](const Point& a, const Point& b)
      {
      return a.x < b.x;
      })->x;
  }

  int getRightY(Polygon& dest)
  {
    return std::max_element(dest.points.begin(), dest.points.end(), [](const Point& a, const Point& b)
      {
      return a.y < b.y;
      })->y;
  }

  int getLeftX_data(std::vector<Polygon>& data)
  {
    return getLeftX(*std::min_element(data.begin(), data.end(), [](Polygon& poly1, Polygon& poly2)
      {
      return getLeftX(poly1) < getLeftX(poly2);
      }));
  }

  int getLeftY_data(std::vector<Polygon>& data)
  {
    return getLeftY(*std::min_element(data.begin(), data.end(), [](Polygon& poly1, Polygon& poly2)
      {
      return getLeftY(poly1) < getLeftY(poly2);
      }));
  }

  int getRightX_data(std::vector<Polygon>& data)
  {
    return getRightX(*std::max_element(data.begin(), data.end(), [](Polygon& poly1, Polygon& poly2)
      {
      return getRightX(poly1) < getRightX(poly2);
      }));
  }

  int getRightY_data(std::vector<Polygon>& data)
  {
    return getRightX(*std::max_element(data.begin(), data.end(), [](Polygon& poly1, Polygon& poly2)
      {
      return getRightY(poly1) < getRightY(poly2);
      }));
  }
  }
