#include <gtest/gtest.h>
#include <sstream>
#include "tuple_utility.h"

TEST(test_tuple_utility,
     check_print_tuple)
{
    std::stringstream tuple_out;
    std::tuple<> tuple_1;
    auto tuple_2 = std::make_tuple(1, "dog", 3.14);

    tuple_out << tuple_1;
    EXPECT_TRUE(tuple_out.str().empty());

    tuple_out << tuple_2;
    EXPECT_EQ(tuple_out.str(), "1, dog, 3.14");
}

TEST(tests_tuple,
     check_make_tuple)
{
    auto tuple_1 = MakeTuple<int, std::string, double>({"1", "dog", "3.14"});
    auto check_1 = std::make_tuple(1, "dog", 3.14);
    EXPECT_EQ(tuple_1, check_1);

    auto tuple = MakeTuple<>({});
    auto check = std::tuple<>();
    EXPECT_EQ(tuple, check);

    try
    {
        auto tuple_3 = MakeTuple<int, std::string, double>({"1", "dog", "3.14a"});
    }
    catch (size_t idx)
    {
        EXPECT_EQ(idx, 2);
    }
}

int main(int argc,
         char ** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}