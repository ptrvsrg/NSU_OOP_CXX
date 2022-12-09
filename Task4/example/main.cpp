#include <fstream>
#include <iostream>
#include "CSV_parser.h"

int main()
{
    std::ifstream file("default.csv");

    try
    {
        CSVParser<std::string, int> parser(file, 1);
        for (const auto & line: parser)
            std::cout << line << std::endl;
    }
    catch (const std::exception & ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}