#include <gtest/gtest.h>
#include "CSV_parser.h"

TEST(test_CSV_parser, file_not_open)
{
    std::ifstream ifs("files/non_exist.csv");
    EXPECT_THROW
    (
        {
            CSVParser<int> csv_parser(ifs);
        },
        std::ifstream::failure
    );
}

TEST(test_CSV_parser, escape_characters)
{
    // File content: "!\a\n\r!\t\v\\!'?,1;!\a\n\r!\t!\t\v\\!'?,2;"
    std::ifstream ifs("files/escape.txt");
    CSVParser<std::string, int> csv_parser(ifs, 1, ',', ';', '!');
    for (const auto & tuple : csv_parser)
        std::cout << tuple << std::endl;
}

TEST(test_CSV_parser, escape_characters_exception)
{
    std::ifstream ifs("files/escape.txt");
    CSVParser<std::string, int> csv_parser(ifs, 0, ';', ':', '!');
    EXPECT_THROW
    (
    {
            for (const auto & tuple : csv_parser)
                std::cout << tuple << std::endl;
        },
    EscapeSymbolsCountException
    );
}

TEST(test_CSV_parser, few_columns)
{
    std::ifstream ifs("files/correct.csv");
    CSVParser<int, std::string, double> csv_parser(ifs);
    EXPECT_THROW
    (
        {
            for (const auto & tuple : csv_parser)
                std::cout << tuple << std::endl;
        },
        ManyColumnsException
    );
}

TEST(test_CSV_parser, many_columns)
{
    std::ifstream ifs("files/correct.csv");
    CSVParser<int, std::string, double, char, size_t> csv_parser(ifs);
    EXPECT_THROW
    (
        {
            for (const auto & tuple : csv_parser)
                std::cout << tuple << std::endl;
        },
        FewColumnsException
    );
}

TEST(test_CSV_parser, type_mismatch)
{
    std::ifstream ifs("files/correct.csv");
    CSVParser<int, size_t, double, char> csv_parser(ifs);
    EXPECT_THROW
    (
        {
            for (const auto & tuple : csv_parser)
                std::cout << tuple << std::endl;
        },
        TypeMismatchException
    );
}

TEST(test_CSV_parser, correct_print)
{
    std::ifstream ifs("files/correct.csv");
    using Type = CSVParser<int, std::string, double, char>;
    EXPECT_NO_THROW
    (
        {
            Type csv_parser(ifs, 1);
            for (const auto &tuple: csv_parser)
                std::cout << tuple << std::endl;
        }
    );
}

TEST(test_CSV_parser, print_again)
{
    std::ifstream ifs("files/correct.csv");
    CSVParser<int, std::string, double, char> csv_parser(ifs, 1);

    std::ostringstream print;
    for (const auto &tuple: csv_parser)
        print << tuple << std::endl;

    std::ostringstream print_again;
    for (const auto &tuple: csv_parser)
        print_again << tuple << std::endl;

    EXPECT_EQ(print.str(), print_again.str());
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}