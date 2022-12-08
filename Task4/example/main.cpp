#include <fstream>
#include <iostream>
#include <tuple>
#include "CSV_parser.h"

int main()
{
    std::ifstream file("test.csv");

    try
    {
        CSVParser<std::string, int> parser(file, ",", "\n", 1);
        for (const auto & rs: parser)
            std::cout << rs << std::endl;
    }
    catch (const std::exception & ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}