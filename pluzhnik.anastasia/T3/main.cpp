#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "polygon.hpp"
#include "command.hpp"


int isNum(const std::string& str);


int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error arg\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input.is_open())
  {
    std::cerr << "Error file\n";
    return 1;
  }

  std::vector< pluzhnik::Polygon > data;
  while (!input.eof())
  {
    if (!input)
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    using iter = std::istream_iterator< pluzhnik::Polygon >;
    std::copy(iter(input), iter(), std::back_inserter(data));
  }

  std::cout << std::setprecision(1) << std::fixed;


  while (!std::cin.eof())
  {
    std::string cmd = "";
    std::cin >> cmd;
    try
    {
      if (cmd == "AREA")
      {
        std::string arg = "";
        std::cin >> arg;
        int num = isNum(arg);
        if (num == -1)
        {
          if (arg == "EVEN")
          {
            getAreaEven(data, std::cout);
          }
          else if (arg == "ODD")
          {
            getAreaOdd(data, std::cout);
          }
          else if (arg == "MEAN")
          {
            getAreaMean(data, std::cout);
          }
          else
          {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
        }
        else if (num > 2)
        {
          getAreaVertexes(data, num, std::cout);
        }
        else
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      }
      else if (cmd == "MAX")
      {
        std::string arg = "";
        std::cin >> arg;
        if (arg == "AREA")
        {
          getMaxArea(data, std::cout);
        }
        else if (arg == "VERTEXES")
        {
          getMaxVertexes(data, std::cout);
        }
        else
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      }
      else if (cmd == "MIN")
      {
        std::string arg = "";
        std::cin >> arg;
        if (arg == "AREA")
        {
          getMinArea(data, std::cout);
        }
        else if (arg == "VERTEXES")
        {
          getMinVertexes(data, std::cout);
        }
        else
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      }
      else if (cmd == "COUNT")
      {
        std::string arg = "";
        std::cin >> arg;
        int num = isNum(arg);

        if (num == -1)
        {
          if (arg == "EVEN")
          {
            getCountEven(data, std::cout);
          }
          else if (arg == "ODD")
          {
            getCountOdd(data, std::cout);
          }
          else
          {
            throw std::invalid_argument("<INVALID COMMAND>");
          }
        }
        else if (num > 2)
        {
          getCountVertexes(data, num, std::cout);
        }
        else
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }

      }
      else if (cmd == "RMECHO")
      {
        rmEcho(data, std::cin, std::cout);
      }
      else if (cmd == "SAME")
      {
        getSame(data, std::cin, std::cout);
      }
      else if (cmd != "")
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    catch (const std::invalid_argument& e)
    {
      std::cout << e.what() << std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}

int isNum(const std::string& str)
{
  char* end;
  int num = strtol(str.c_str(), &end, 10);
  if (*end != 0)
  {
    return -1;
  }
  return num;
}
