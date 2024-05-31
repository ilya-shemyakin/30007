#include <functional>
#include <algorithm>
#include <numeric>
#include <limits>
#include <string>

#include "commands.h"

using namespace std::placeholders;

int command::convertToNumber(const std::string& str)
{
  try
  {
    return std::stoi(str);
  }
  catch (std::invalid_argument const& ex)
  {
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
}

void command::area(const std::vector<skor::Polygon>& data)
{
  auto accumulateArea = [](double ac, const skor::Polygon& poly, std::size_t mod2, std::size_t vertices)
    {
      if ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices) || (mod2 == 3))
      {
        ac += poly.getArea();
      }
      return ac;
    };

  std::string arg;
  std::cin >> arg;
  if (arg == "EVEN")
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumulateArea, _1, _2, 0, 0)) << '\n';
  }
  else if (arg == "ODD")
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumulateArea, _1, _2, 1, 0)) << '\n';
  }
  else if (arg == "MEAN" && data.size() != 0)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumulateArea, _1, _2, 3, 0)) / data.size() << std::endl;
  }
  else if (std::all_of(arg.begin(), arg.end(), isdigit) && stoi(arg) > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumulateArea, _1, _2, 2, stoi(arg))) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void command::max(const std::vector<skor::Polygon>& data)
{
  if (data.empty())
    throw std::runtime_error("<INVALID COMMAND>");

  std::string arg;
  std::cin >> arg;

  if (arg == "AREA")
  {
    std::cout << std::max_element(data.begin(), data.end())->getArea() << '\n';
  }
  else if (arg == "VERTEXES")
  {
    std::vector<std::size_t> sizes(data.size());

    std::cout << std::accumulate(
      data.begin() + 1,
      data.end(),
      data[0].points.size(),
      [](std::size_t max, const skor::Polygon& poly)
      {
        return (poly.points.size() > max ? poly.points.size() : max);
      }
    ) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void command::min(const std::vector<skor::Polygon>& data)
{
  if (data.empty())
    throw std::runtime_error("<INVALID COMMAND>");

  std::string arg;
  std::cin >> arg;

  if (arg == "AREA")
  {
    std::cout << std::min_element(data.begin(), data.end())->getArea() << '\n';
  }
  else if (arg == "VERTEXES")
  {
    std::vector<std::size_t> sizes(data.size());

    std::cout << std::accumulate(
      data.begin() + 1,
      data.end(),
      data[0].points.size(),
      [](std::size_t min, const skor::Polygon& polygon)
      {
        return (polygon.points.size() < min ? polygon.points.size() : min);
      }
    ) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void command::count(const std::vector<skor::Polygon>& data)
{
  auto countPolygons = [](const skor::Polygon& poly, std::size_t mod2, std::size_t vertices)
    {
      return ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices));
    };

  std::string arg;
  std::cin >> arg;
  if (arg == "EVEN")
  {
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(countPolygons, _1, 0, 0)) << '\n';
  }
  else if (arg == "ODD")
  {
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(countPolygons, _1, 1, 0)) << '\n';
  }
  else if (std::all_of(arg.begin(), arg.end(), isdigit) && stoi(arg) > 2)
  {
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(countPolygons, _1, 2, stoi(arg))) << '\n';
  }
  else
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
}

void command::rmecho(std::vector<skor::Polygon>& data)
{
  skor::Polygon target, prev;
  std::cin >> target;
  prev = data[0];
  int count = 0;
  auto removeFunc = [&target, &prev, &count](const skor::Polygon& polygon) {
    bool result = polygon == prev && polygon == target;
    prev = polygon;
    if (result)
    {
      count++;
    }
    return result;
    };
  auto removeCond = std::remove_if(data.begin() + 1, data.end(), removeFunc);
  data.erase(removeCond, data.end());
  std::cout << count << std::endl;
}

void command::inframe(const std::vector<skor::Polygon>& data)
{
  skor::Polygon target;
  std::cin >> target;

  if (std::cin.fail() || std::cin.get() != '\n')
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  skor::Frame frame = skor::getFrame(data);
  std::cout << (frame.containsPolygon(target) ? "<TRUE>" : "<FALSE>") << '\n';
}
