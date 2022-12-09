#include <gtest/gtest.h>
#include <sstream>
#include "tuple_utility.h"

TEST(test_tuple_utility, print_tuple)
{
    std::stringstream tuple_out;
    auto tuple = std::make_tuple(1, "dog", 3.14);

    tuple_out << tuple;
    EXPECT_EQ(tuple_out.str(), "1, dog, 3.14");
}

TEST(test_tuple_utility, print_empty_tuple)
{
    std::stringstream tuple_out;
    std::tuple<> tuple;

    tuple_out << tuple;
    EXPECT_TRUE(tuple_out.str().empty());
}

TEST(tests_tuple, make_tuple)
{
    auto tuple = MakeTuple<int, std::string, double>({"1", "dog", "3.14"});
    auto check = std::make_tuple(1, "dog", 3.14);
    EXPECT_EQ(tuple, check);
}

TEST(tests_tuple, make_empty_tuple)
{
    auto tuple = MakeTuple<>({});
    auto check = std::tuple<>();
    EXPECT_EQ(tuple, check);
}

TEST(tests_tuple, make_tuple_exception)
{
    try
    {
        auto tuple = MakeTuple<int, std::string, double>({"1", "dog", "3.14a"});
        FAIL();
    }
    catch (size_t idx)
    {
        EXPECT_EQ(idx, 2);
    }
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}