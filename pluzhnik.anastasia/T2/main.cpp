#include "dataStruct.h"
#include <algorithm>

using pluzhnik::DataStruct;

int main()
{
    std::string input = "";
    std::vector< DataStruct > data;

    while (!std::cin.eof())
    {
      if (!std::cin)
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
      );
    }

    std::sort(std::begin(data), std::end(data), pluzhnik::compareDataStruct);

    std::copy
    (
      std::begin(data),
      std::end(data),
      std::ostream_iterator< DataStruct >(std::cout, "\n")
    );

  return EXIT_SUCCESS;
}
