#include "dataStruct.h"
#include <algorithm>

using skor::DataStruct;

int main()
{
  try
  {
    std::string input = "";
    std::vector< DataStruct > data;

    while (!std::cin.eof())
    {
      if (!std::cin)
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(), '\n');
      }
      std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
      );
    }

    std::sort(std::begin(data), std::end(data), skor::compareDataStruct);

    std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
  }
  catch (std::exception& er)
  {
    std::cerr << er.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
