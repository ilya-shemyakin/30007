#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <cmath>

#include "polygon.h"


using namespace std::placeholders;

skor::Triangle::Triangle(const Point& a, const Point& b, const Point& c)
{
  this->a = a;
  this->b = b;
  this->c = c;
}

skor::Frame skor::getFrame(const std::vector<Polygon>& data)
{
  if (data.empty())
    throw std::runtime_error("Error: no one Polygon");

  skor::Point lowerLeft = data[0].points[0];
  skor::Point upperRight = data[0].points[0];
  for (const skor::Polygon& poly : data)
  {
    for (const skor::Point& p : poly.points)
    {
      if (p.x < lowerLeft.x)
        lowerLeft.x = p.x;
      if (p.x > upperRight.x)
        upperRight.x = p.x;
      if (p.y < lowerLeft.y)
        lowerLeft.y = p.y;
      if (p.y > upperRight.y)
        upperRight.y = p.y;
    }
  }
  return skor::Frame(lowerLeft, upperRight);
}

double skor::getDistance(const skor::Point& p1, const skor::Point& p2)
{
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

double skor::Triangle::getArea() const
{
  double x = getDistance(a, b);
  double y = getDistance(a, c);
  double z = getDistance(b, c);
  double p = (x + y + z) / 2;
  return std::sqrt(p * (p - x) * (p - y) * (p - z));
}

double skor::Polygon::getArea() const
{
  skor::Point fixed = points[0], first = points[1];

  double square = std::accumulate(
    points.begin() + 2,
    points.end(),
    0.0,
    [fixed, &first](double accumulator, skor::Point second)
    {
      accumulator += Triangle(fixed, first, second).getArea();
      first = second;
      return accumulator;
    }
  );
  return square;
}

bool skor::Polygon::operator<(const Polygon& other) const
{
  return getArea() < other.getArea();
}

bool skor::Polygon::operator==(const Polygon& other) const
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

bool skor::Polygon::operator!=(const Polygon& other) const
{
  return !(*this == other);
}

bool skor::Point::operator==(const skor::Point& other) const
{
  return this->x == other.x && this->y == other.y;
}

bool skor::Point::operator!=(const Point& other) const
{
  return (this->x != other.x) || (this->y != other.y);
}

std::ostream& skor::operator<<(std::ostream& out, const skor::Point& point)
{
  return (out << '(' << point.x << ';' << point.y << ')');
}

std::ostream& skor::operator<<(std::ostream& out, const skor::Polygon& polygon)
{
  out << polygon.points.size();
  for (auto& p : polygon.points)
    out << ' ' << p;
  return (out << '\n');
}

std::istream& skor::operator>>(std::istream& in, skor::DelimiterIO&& dest)
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

std::istream& skor::operator>>(std::istream& in, skor::Point& dest)  // (1;1)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >> dest.y >> DelimiterIO{ ')' };
  return in;
}

std::istream& skor::operator>>(std::istream& in, skor::Polygon& polygon)  // 3 (1;2) (0;0) (0;3)
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

skor::Frame::Frame(const Point& lowerLeft, const Point& upperRight)
{
  if (lowerLeft.x > upperRight.x || lowerLeft.y > upperRight.y)
    throw std::invalid_argument("Invalid frame");

  this->lowerLeft = lowerLeft;
  this->upperRight = upperRight;
}

bool skor::Frame::containsPoint(const Point& p) const
{
  return p.x >= lowerLeft.x && p.x <= upperRight.x && p.y >= lowerLeft.y && p.y <= upperRight.y;
}

bool skor::Frame::containsPolygon(const Polygon& poly) const
{
  return std::all_of(poly.points.begin(), poly.points.end(),
    [this](const Point& p) { return containsPoint(p); });
}
