#include <iostream>
#include "CSV_parser.h"

int main(int argc, char ** argv)
{
    try
    {
        if (argc == 2)
        {
            std::ifstream file(argv[1]);
            CSVParser<std::string, int> parser(file);
            for (const auto & line: parser)
                std::cout << line << std::endl;
        }
        else if (argc == 3)
        {
            std::ifstream file(argv[1]);
            CSVParser<std::string, int> parser(file, std::stoi(argv[2]));
            for (const auto & line: parser)
                std::cout << line << std::endl;
        }
        else if (argc == 4)
        {
            std::ifstream file(argv[1]);
            CSVParser<std::string, int> parser(file, std::stoi(argv[2]), *argv[3]);
            for (const auto & line: parser)
                std::cout << line << std::endl;
        }
        else if (argc == 5)
        {
            std::ifstream file(argv[1]);
            CSVParser<std::string, int> parser(file, std::stoi(argv[2]), *argv[3], *argv[4]);
            for (const auto & line: parser)
                std::cout << line << std::endl;
        }
        else if (argc == 6)
        {
            std::ifstream file(argv[1]);
            CSVParser<std::string, int> parser(file, std::stoi(argv[2]), *argv[3], *argv[4], *argv[5]);
            for (const auto & line: parser)
                std::cout << line << std::endl;
        }
    }
    catch (const std::exception & ex)
    {
        std::cerr << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}