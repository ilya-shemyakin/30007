#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <limits>

#include "polygon.h"
#include "commands.h"

const std::string INCORRECT_USAGE = "Incorrect usage!";
const std::string NO_SUCH_FILE = "File not found!";
const std::string ERROR = "Something went wrong";

int main(int argC, char* argV[])
{
  if (argC != 2)
  {
    std::cerr << INCORRECT_USAGE << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argV[1];

  std::ifstream file(fileName);

  if (!file)
  {
    std::cerr << NO_SUCH_FILE << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<skor::Polygon> data;

  while (!file.eof())
  {
    std::copy(std::istream_iterator<skor::Polygon>(file),
      std::istream_iterator<skor::Polygon>(),
      std::back_inserter(data));
    if (!file.eof() && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  try
  {
    while (!std::cin.eof())
    {
      std::string cmd;
      std::cin >> cmd;
      try
      {
        if (cmd == "AREA")
        {
          command::area(data);
        }
        else if (cmd == "MIN")
        {
          command::min(data);
        }
        else if (cmd == "MAX")
        {
          command::max(data);
        }
        else if (cmd == "COUNT")
        {
          command::count(data);
        }
        else if (cmd == "RMECHO")
        {
          command::rmecho(data);
        }
        else if (cmd == "INFRAME")
        {
          command::inframe(data);
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

    return EXIT_SUCCESS;
  }
  catch (...)
  {
    std::cerr << ERROR << std::endl;
    return EXIT_FAILURE;
  }
}
