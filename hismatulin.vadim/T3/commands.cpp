#include "commands.h"
#include <numeric>
#include <functional>
#include <algorithm>

using namespace std::placeholders;

int isString_num(std::string& data)
{
  int x;
  x = strtol(data.c_str(), 0, 10);
  if (x > 0) { return x; }
  return 0;
}

double T3_hism::area(std::vector<Polygon>& data, std::string& arg)
{
  int N = isString_num(arg);
  if (N == 0) {
    if (arg == "EVEN")
    {
      return std::accumulate(data.begin(), data.end(), 0.0, std::bind(getSumArea_Param, _1, _2, 0, 0));
    }
    else if (arg == "ODD")
    {
      return std::accumulate(data.begin(), data.end(), 0.0, std::bind(getSumArea_Param, _1, _2, 1, 0));
    }
    else if (arg == "MEAN")
    {
      if (data.size() == 0)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
      return std::accumulate(data.begin(), data.end(), 0.0, std::bind(getSumArea_Param, _1, _2, -10, 0))/data.size();
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  else if (N >= 3)
  {
    return std::accumulate(data.begin(), data.end(), 0.0, std::bind(getSumArea_Param, _1, _2, -20, N));
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

double T3_hism::maxArea(std::vector<Polygon>& data)
{
  if (data.size() == 0) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  return getPolygonArea(*std::max_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b)
    {
    return getPolygonArea(a) < getPolygonArea(b);
    }));
}

int T3_hism::maxVertexes(std::vector<Polygon>& data)
{
  if (data.size() == 0) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  return (std::max_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b)
    {
    return a.points.size() < b.points.size();
    })->points.size());
}

double T3_hism::minArea(std::vector<Polygon>& data)
{
  return getPolygonArea(*std::min_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b)
    {
    return getPolygonArea(a) < getPolygonArea(b);
    }));
}

int T3_hism::minVertexes(std::vector<Polygon>& data)
{
  return (std::min_element(data.begin(), data.end(), [](const Polygon& a, const Polygon& b)
    {
    return a.points.size() < b.points.size();
    })->points.size());
}

int T3_hism::count(std::vector<Polygon>& data, std::string& arg)
{
  int N = isString_num(arg);
  if (N == 0)
  {
    if (arg == "EVEN")
    {
      return std::count_if(data.begin(), data.end(), [](const Polygon& a) {return a.points.size() % 2 == 0;});
    }
    else if (arg == "ODD")
    {
      return std::count_if(data.begin(), data.end(), [](const Polygon& a) {return a.points.size() % 2 == 1;});
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  else if (N >= 3)
  {
    return std::count_if(data.begin(), data.end(), std::bind([](const Polygon& a, int vertex_count)
      {
      return static_cast<int>(a.points.size()) == vertex_count;
      }, _1, N));
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

int T3_hism::perms(std::vector<Polygon>& data, Polygon& polygon)
{
  return std::count_if(data.begin(), data.end(), [&polygon](const Polygon& p)
    {
    if (p.points.size() != polygon.points.size())
    {
      return false;
    }
    return std::is_permutation(p.points.begin(), p.points.end(), polygon.points.begin());
    });
}

std::string T3_hism::inframe(std::vector<Polygon>& data, Polygon& polygon)
{
  if (getLeftX(polygon) >= getLeftX_data(data)
    &&getLeftY(polygon) >= getLeftY_data(data)
    && getRightX(polygon) <= getRightX_data(data) && getRightY(polygon) <= getRightY_data(data))
  {
    return "<TRUE>";
  }
  else {
    return "<FALSE>";
  }
}
