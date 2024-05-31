#include <iostream>
#include <numeric>
#include <algorithm>
#include <functional>
#include "Commands.h"

using namespace std::placeholders;

namespace mrkv
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

  int echo(std::vector<Polygon>& figures, Polygon& forAdd)
  {
    int numOfInsertions = std::count(figures.begin(), figures.end(), forAdd);
    if (numOfInsertions == 0)
    {
      return 0;
    }

    std::vector<Polygon> tmp = figures;
    bool flag = false;
    int offset = -1, counter = 0;
    auto lambda = [&forAdd, &tmp, &flag, &offset, &counter](Polygon& poly)
      {
        if (flag == true)
        {
          auto it = std::find(tmp.begin() + offset, tmp.end(), forAdd);
          if (it != tmp.end())
          {
            tmp.insert(it, forAdd);
          }
          ++offset;
          ++counter;
          flag = false;
        }
        flag = (poly == forAdd) ? true : false;
        ++offset;
        return false;
      };

    std::copy_if(figures.begin(), figures.end(), tmp.begin(), lambda);

    if (*(tmp.end() - 1) == forAdd)
    {
      tmp.push_back(forAdd);
      ++counter;
    }

    figures = tmp;
    return counter;
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
}
