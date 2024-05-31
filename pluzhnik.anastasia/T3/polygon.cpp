#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "polygon.hpp"

std::istream& pluzhnik::operator>>(std::istream& in, DelimiterIO&& dest)
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

bool pluzhnik::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x_ == rhs.x_) && (lhs.y_ == rhs.y_);
}

bool pluzhnik::operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points_ == rhs.points_;
}

std::istream& pluzhnik::operator>>(std::istream& in, Point& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' };
  in >> dest.x_;
  in >> DelimiterIO{ ';' };
  in >> dest.y_;
  in >> DelimiterIO{ ')' };
  return in;
}

std::istream& pluzhnik::operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t count = 0;
  in >> count;
  if (count < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  using iter = std::istream_iterator< Point >;
  dest.points_.clear();
  std::copy_n(iter(in), count, std::back_inserter(dest.points_));
  if (dest.points_.size() != count)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

double pluzhnik::calcTriangleArea(const Point& p1, const Point& p2, const Point& p3)
{
  double a = sqrt((p1.x_ - p2.x_) * (p1.x_ - p2.x_) + (p1.y_ - p2.y_) * (p1.y_ - p2.y_));
  double b = sqrt((p2.x_ - p3.x_) * (p2.x_ - p3.x_) + (p2.y_ - p3.y_) * (p2.y_ - p3.y_));
  double c = sqrt((p3.x_ - p1.x_) * (p3.x_ - p1.x_) + (p3.y_ - p1.y_) * (p3.y_ - p1.y_));

  double p = (a + b + c) / 2;

  return sqrt(p * (p - a) * (p - b) * (p - c));
}

int pluzhnik::getVertexes(const Polygon& polygon)
{
  return polygon.points_.size();
}

double pluzhnik::getArea(const Polygon& polygon)
{
  const Point p0 = polygon.points_[0];
  Point prev = polygon.points_[1];

  auto lambda = [&p0, &prev](double acc, const Point& cur)
    {
      acc += calcTriangleArea(p0, prev, cur);
      prev = cur;
      return acc;
    };
  return std::accumulate(polygon.points_.begin() + 2, polygon.points_.end(), 0.0, lambda);
}

bool pluzhnik::areaComparator(const Polygon& lhs, const Polygon& rhs)
{
  return getArea(lhs) < getArea(rhs);
}

bool pluzhnik::vertexesComparator(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points_.size() < rhs.points_.size();
}

bool pluzhnik::pointsComparator(const Point& p1, const Point& p2)
{
  if (p1.x_ == p2.x_)
  {
    return p1.y_ < p2.y_;
  }
  return p1.x_ < p2.x_;
}
