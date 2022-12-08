#include <gtest/gtest.h>
#include "CSV_parser.h"

template<typename Type>
class CSVParserTests : public ::testing::Test {};
TYPED_TEST_SUITE_P(CSVParserTests);
TYPED_TEST_P(CSVParserTests, check_exception)
{
    std::ifstream ifs("files/correct.csv");
    TypeParam csv_parser(ifs);
    EXPECT_THROW
    (
        {
            for (const auto & tuple : csv_parser)
                std::cout << tuple << std::endl;
        },
        CSVException
    );
}
REGISTER_TYPED_TEST_SUITE_P(CSVParserTests, check_exception);
using Types = testing::Types<CSVParser<int, std::string, double>,
                             CSVParser<int, std::string, double, char, size_t>,
                             CSVParser<>,
                             CSVParser<int, size_t, double, char>>;
INSTANTIATE_TYPED_TEST_SUITE_P(test_CSV_parser, CSVParserTests, Types);

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

TEST(test_CSV_parser, correct_print)
{
    std::ifstream ifs("files/correct.csv");
    CSVParser<int, std::string, double, char> csv_parser(ifs, 1, ",", "\n");
    for (const auto & tuple : csv_parser)
        std::cout << tuple << std::endl;
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}