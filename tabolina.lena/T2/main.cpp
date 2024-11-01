#include "Tabolina_datastruct.h"

using tabolina::DataStruct;

int main()
{
    try
    {
        std::vector<DataStruct> data;

        while (!std::cin.eof())
        {
            std::copy(
                std::istream_iterator<DataStruct>(std::cin),
                std::istream_iterator<DataStruct>(),
                std::back_inserter(data)
            );
            if (std::cin.fail() && !std::cin.eof())
            {
                std::cin.clear();
            }
        }
        std::sort(std::begin(data), std::end(data), tabolina::compareDataStruct);
        std::copy(
            std::begin(data),
            std::end(data),
            std::ostream_iterator<DataStruct>(std::cout, "\n")
        );
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
