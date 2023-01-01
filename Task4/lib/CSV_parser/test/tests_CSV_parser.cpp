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

template<typename T>
struct CSVParserTest : public ::testing::Test {};
TYPED_TEST_SUITE_P(CSVParserTest);

TYPED_TEST_P(CSVParserTest, check_exception)
{
    using CSVParserType = std::tuple_element_t<0, TypeParam>;

    std::ifstream ifs("files/correct.csv");

    if (std::tuple_size_v<TypeParam> == 2)
    {
        using ExceptionType = std::tuple_element_t<1, TypeParam>;
        CSVParserType csv_parser(ifs);
        EXPECT_THROW
        (
            {
                for (const auto & tuple: csv_parser)
                    std::cout << tuple << std::endl;
            },
            ExceptionType
        );
    }
    else
    {
        EXPECT_NO_THROW
        (
            {
                CSVParserType csv_parser(ifs, 1);

                std::ostringstream print;
                for (const auto & tuple: csv_parser)
                    print << tuple << std::endl;

                std::ostringstream print_again;
                for (const auto & tuple: csv_parser)
                    print_again << tuple << std::endl;

                EXPECT_EQ(print.str(), print_again.str());
            }
        );
    }
}

REGISTER_TYPED_TEST_SUITE_P(CSVParserTest, check_exception);
using Types = testing::Types<std::tuple<CSVParser<int, std::string, double>, ManyColumnsException>,
                             std::tuple<CSVParser<int, std::string, double, char, size_t>, FewColumnsException>,
                             std::tuple<CSVParser<int, size_t, double, char>, TypeMismatchException>>;
INSTANTIATE_TYPED_TEST_SUITE_P(TestPrefix, CSVParserTest, Types);

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