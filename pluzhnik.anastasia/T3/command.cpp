#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iomanip>
#include "command.hpp"
#include "polygon.hpp"

using namespace std::placeholders;

void pluzhnik::getAreaEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  auto lambda = [](double acc, const Polygon& polygon)
    {
      if (polygon.points_.size() % 2 == 0)
      {
        acc += getArea(polygon);
      }
      return acc;
    };
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, lambda) << '\n';
}

void pluzhnik::getAreaOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  auto lambda = [](double acc, const Polygon& polygon)
    {
      if (polygon.points_.size() % 2 == 1)
      {
        acc += getArea(polygon);
      }
      return acc;
    };
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, lambda) << '\n';
}
void pluzhnik::getAreaMean(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
    [](double acc, const Polygon& polygon) { return acc += getArea(polygon); }) / polygons.size() << '\n';
}

void pluzhnik::getAreaVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
{
  if (count < 3)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  auto lambda = [&count](double acc, const Polygon& polygon)
    {
      if (polygon.points_.size() == count)
      {
        acc += getArea(polygon);
      }
      return acc;
    };
  out << std::accumulate(polygons.begin(), polygons.end(), 0.0, lambda) << "\n";
}

void pluzhnik::getMaxArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << getArea(*std::max_element(polygons.begin(), polygons.end(), areaComparator)) << '\n';
}

void pluzhnik::getMaxVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << getVertexes(*std::max_element(polygons.begin(), polygons.end(), vertexesComparator)) << "\n";
}

void pluzhnik::getMinArea(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << getArea(*std::min_element(polygons.begin(), polygons.end(), areaComparator)) << '\n';
}

void pluzhnik::getMinVertexes(const std::vector< Polygon >& polygons, std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  out << getVertexes(*std::min_element(polygons.begin(), polygons.end(), vertexesComparator)) << "\n";
}

void pluzhnik::getCountEven(const std::vector< Polygon >& polygons, std::ostream& out)
{
  out << std::count_if(polygons.begin(), polygons.end(),
    [](const Polygon& polygon) { return polygon.points_.size() % 2 == 0; }) << "\n";
}

void pluzhnik::getCountOdd(const std::vector< Polygon >& polygons, std::ostream& out)
{
  out << std::count_if(polygons.begin(), polygons.end(),
    [](const Polygon& polygon) { return polygon.points_.size() % 2 == 1; }) << "\n";
}

void pluzhnik::getCountVertexes(const std::vector< Polygon >& polygons, size_t count, std::ostream& out)
{
  out << std::count_if(polygons.begin(), polygons.end(),
    [&count](const Polygon& polygon) { return polygon.points_.size() == count; }) << "\n";
}

void pluzhnik::rmEcho(std::vector<Polygon>& data, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  auto isEcho = [&polygon](const Polygon& lhs, const Polygon& rhs) { return lhs == polygon && rhs == polygon; };
  auto toRemoveIt = std::unique(data.begin(), data.end(), isEcho);
  std::size_t removedCount = std::distance(toRemoveIt, data.end());
  data.erase(toRemoveIt, data.end());
  out << removedCount << '\n';
}

void pluzhnik::getSame(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::sort(polygon.points_.begin(), polygon.points_.end(), pointsComparator);

  out << std::count_if(polygons.begin(), polygons.end(), std::bind(isSame, _1, polygon)) << '\n';
}

bool pluzhnik::isSame(Polygon lhs, Polygon rhs)
{
  if (lhs.points_.size() != rhs.points_.size())
  {
    return false;
  }

  std::sort(lhs.points_.begin(), lhs.points_.end(), pointsComparator);

  int diffX = lhs.points_[0].x_ - rhs.points_[0].x_;
  int diffY = lhs.points_[0].y_ - rhs.points_[0].y_;
  std::transform(rhs.points_.begin(), rhs.points_.end(), rhs.points_.begin(), [&diffX, &diffY](Point& point)
    {
      point.x_ += diffX;
      point.y_ += diffY;
      return point;
    });

  int offSet = -1;
  auto lambda = [&rhs, &offSet](Point& point)
    {
      ++offSet;
      return !(point.x_ == rhs.points_[offSet].x_ && point.y_ == rhs.points_[offSet].y_);
    };
  // Cчитаем количество несовпадающих точек
  return std::count_if(lhs.points_.begin(), lhs.points_.end(), lambda) == 0;
}
