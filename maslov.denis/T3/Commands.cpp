#include <iostream>
#include <numeric>
#include <algorithm>
#include <functional>
#include "Commands.h"
using namespace std::placeholders;
namespace dnlx
{
  int isArgANumber(const std::string& str)
  {
    char* end;
    int num = strtol(str.c_str(), &end, 10);
    if (*end != 0)
    {
      return -1;
    }
    return num;
  }
  double area(std::vector<Polygon>& figures, const std::string& arg)
  {
    int num = isArgANumber(arg);
    if (num == -1)
    {
      if (arg == "EVEN")
      {
        return std::accumulate(figures.begin(), figures.end(), 0.0, std::bind(areaAccumulator, _1, _2, 2, 0));
      }
      else if (arg == "ODD")
      {
        return std::accumulate(figures.begin(), figures.end(), 0.0, std::bind(areaAccumulator, _1, _2, 2, 1));
      }
      else if (arg == "MEAN" && figures.size() >= 1)
      {
        return std::accumulate(figures.begin(), figures.end(), 0.0, std::bind(areaAccumulator, _1, _2, 2, -1)) / figures.size();
      }
      else
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    else if (num > 2)
    {
      return std::accumulate(figures.begin(), figures.end(), 0.0, std::bind(areaAccumulatorVertexes, _1, _2, num));
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  double maxArea(std::vector<Polygon>& figures)
  {
    return calculatePolygonArea(*std::max_element(figures.begin(), figures.end(), areaComporator));
  }
  int maxVertexes(std::vector<Polygon>& figures)
  {
    return (*std::max_element(figures.begin(), figures.end(), vertexesComporator)).points.size();
  }
  double minArea(std::vector<Polygon>& figures)
  {
    return calculatePolygonArea(*std::min_element(figures.begin(), figures.end(), areaComporator));
  }
  int minVertexes(std::vector<Polygon>& figures)
  {
    return (*std::min_element(figures.begin(), figures.end(), vertexesComporator)).points.size();
  }
  int count(std::vector<Polygon>& figures, const std::string& arg)
  {
    int num = isArgANumber(arg);
    if (num == -1)
    {
      if (arg == "EVEN")
      {
        return std::count_if(figures.begin(), figures.end(), std::bind(countCondition, _1, 2, 0));
      }
      else if (arg == "ODD")
      {
        return std::count_if(figures.begin(), figures.end(), std::bind(countCondition, _1, 2, 1));
      }
      else
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    else if (num > 2)
    {
      return std::count_if(figures.begin(), figures.end(), std::bind(countConditionVertexes, _1, num));
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  std::string inframe(std::vector<Polygon>& figures, Polygon& input)
  {
    if ((getLeftB(input) >= getLeftFiguresB(figures) && getDownB(input) >= getDownFiguresB(figures))
      && (getRightB(input) <= getRightFiguresB(figures) && getUpB(input) <= getUpFiguresB(figures)))
    {
      return "<TRUE>";
    }
    else
    {
      return "<FALSE>";
    }
  }
  bool doIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    auto orientation = [](const Point& p, const Point& q, const Point& r) -> int {
      int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
      if (val == 0) return 0;
      return (val > 0) ? 1 : 2;
      };
    auto onSegment = [](const Point& p, const Point& q, const Point& r) -> bool {
      return (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y));
      };
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;
  }
  bool hasIntersection(const Polygon& lhs, const Polygon& rhs)
  {
    const auto minMaxLhs = std::minmax_element(lhs.points.cbegin(), lhs.points.cend());
    const auto minMaxRhs = std::minmax_element(rhs.points.cbegin(), rhs.points.cend());
    const auto& maxLhs = *(minMaxLhs.second);
    const auto& minLhs = *(minMaxLhs.first);
    const auto& maxRhs = *(minMaxRhs.second);
    const auto& minRhs = *(minMaxRhs.first);
    return !((maxRhs < minLhs) || (maxLhs < minRhs));
  }
  void intersections(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
  {
    if (data.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    Polygon polygon;
    in >> polygon;
    if (!in || in.peek() != '\n')
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    auto intersectPredicate = std::bind(hasIntersection, std::cref(polygon), _1);
    out << std::count_if(data.cbegin(), data.cend(), intersectPredicate) <<std::endl;
  }
}
